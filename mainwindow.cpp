#include "mainwindow.h"
#include "ui_mainwindow.h"

const int TS_MS      =   50;    // 通信间隔 xx ms 标准状态传50
const int INIT_MODEL =    1;    // 1:自己模拟车体数据   2:使用GPS数据, const代表常量不可改变，优化可以直接在ui里面改
const int INIT_SPEED =    1;    // 1:手动给油门        2:自动给油门
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)//开机自动运行的部分
{
    ui->setupUi(this);

    //初始化画图需要的东西
    QPen drawPen1;//设置画笔1的颜色 蓝色,宽度为5
    drawPen1.setColor(Qt::blue);
    drawPen1.setWidth(5);
    QPen drawPen2;//设置画笔2的颜色 红色,宽度为5
    drawPen2.setColor(Qt::red);
    drawPen2.setWidth(5);
    QPen drawPen3;//设置画笔3的颜色 绿色,宽度为2
    drawPen3.setColor(Qt::green);
    drawPen3.setWidth(2);
    QPen drawPen4;//设置画笔4的颜色 黄色,宽度为3
    drawPen4.setColor(Qt::magenta);
    drawPen4.setWidth(2);
    QPen drawPen5;//设置画笔5的颜色 黄色,宽度为3
    drawPen5.setColor(Qt::cyan);
    drawPen5.setWidth(2);

    //绘制UTM大地坐标系的图
    ui->plot_UTM->addGraph();//增加原来轨迹点图层
    ui->plot_UTM->graph(0)->setName("map1");
    ui->plot_UTM->graph(0)->setLineStyle(QCPGraph::lsNone); //QCPGraph::lsNone lsLine
    ui->plot_UTM->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->plot_UTM->graph(0)->setPen(drawPen3);

    ui->plot_UTM->addGraph();//增加预瞄点图层
    ui->plot_UTM->graph(1)->setName("yumiao");
    ui->plot_UTM->graph(1)->setLineStyle(QCPGraph::lsNone); //QCPGraph::lsNone lsLine
    ui->plot_UTM->graph(1)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
    ui->plot_UTM->graph(1)->setPen(drawPen2);
    ui->plot_UTM->addGraph();//增加实际车子点图层
    ui->plot_UTM->graph(2)->setName("Car");
    ui->plot_UTM->graph(2)->setLineStyle(QCPGraph::lsNone); //QCPGraph::lsNone lsLine
    ui->plot_UTM->graph(2)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 3));
    ui->plot_UTM->graph(2)->setPen(drawPen1);
    QVector<double> picX2, picY2;//在循环读文件前面提前声明；

    ui->plot_UTM->addGraph();//增加曲线轨迹点图层
    ui->plot_UTM->graph(3)->setName("map2");
    ui->plot_UTM->graph(3)->setLineStyle(QCPGraph::lsNone); //QCPGraph::lsNone lsLine
    ui->plot_UTM->graph(3)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->plot_UTM->graph(3)->setPen(drawPen4);
    ui->plot_UTM->addGraph();//增加曲线轨迹点图层
    ui->plot_UTM->graph(4)->setName("map3");
    ui->plot_UTM->graph(4)->setLineStyle(QCPGraph::lsNone); //QCPGraph::lsNone lsLine
    ui->plot_UTM->graph(4)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->plot_UTM->graph(4)->setPen(drawPen5);


    //绘制自己车体坐标系图下的预瞄点
    ui->plot_che->addGraph();//增加预瞄点图层
    ui->plot_che->graph(0)->setName("yumiao");
    ui->plot_che->graph(0)->setLineStyle(QCPGraph::lsNone); //QCPGraph::lsNone lsLine
    ui->plot_che->graph(0)->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 2));
    ui->plot_che->graph(0)->setPen(drawPen2);
    ui->plot_che->xAxis->setRange(-100, 100);          //3图x轴范围
    ui->plot_che->yAxis->setRange(-100, 100);          //3图y轴范围
    ui->plot_che->xAxis->setLabel("Cheti X");     //设置x轴名称
    ui->plot_che->yAxis->setLabel("Chrti Y");     //设置y轴名称
    ui->plot_che->legend->setVisible(true);        //设置每条曲线的说明可见,默认为不可见

    //开始关闭自动驾驶信号槽申明
    connect(ui->push_start, SIGNAL(clicked()), this, SLOT(StartAD()));
    connect(ui->push_stop, SIGNAL(clicked()), this, SLOT(CloseAD()));

    //输入车体坐标仿真 信号槽
    //connect(ui->push_che,SIGNAL(clicked()),this,SLOT(CarPosIn()));

    // 打开COM控制器，读取车子实际位置的GPS信息
    // ComConnect *m_comConnect; 这个定义移到.h文件里 公共使用
    m_comConnect = new COMConnect();
    m_comConnect->COMOpen();
    connect(&m_comConnect->com_serial,SIGNAL(readyRead()),this,SLOT(GPSRead()));

    //打开CAN控制器
    m_canConnect = new CANConnect();
    m_canConnect->Init();

    //打开Qtimer定时器，最核心Timeoutmain,计算steer转角
    m_timerMain = new QTimer(this);
    m_timerMain->setInterval(TS_MS);	//设置一个时间 单位毫秒
    connect(m_timerMain, SIGNAL(timeout()), this, SLOT(TimeOutMain()));

    //读取轨迹的GPS信息
    //首先读取一下地图
    QFile file("data/map.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) //以只读的方式 打开文件且文本格式为text
    {
        qDebug() << "file is not open!";
        return;
    }
    QTextStream mapSteam(&file);
    QString  lineStr = mapSteam.readLine();//逐行读入，定义数据为字符串形式

    //设置循环直至读不到数据
    double tmpV1, tmpV2, tmpVR, UTMX, UTMY, UTMXMIN, UTMXMAX, UTMYMIN, UTMYMAX;
    while (!lineStr.isNull())
    {
        QStringList lineStrList = lineStr.split(",");
        RoadPoint mapDotTemp;//mapDOtemp为结构体，临时变量存放实际轨迹GPS坐标

        //     0    1                  2      3      4          5
        //$GPHPD,2058,119096.800,271.417,-1.615,12.266,31.1295245,120.6623331,12.89,0.008,0.002,-0.022,-1.000,16,20,0B*22

        mapDotTemp.Lat = lineStrList[6].toDouble();
        mapDotTemp.Lon = lineStrList[7].toDouble();
        mapDotTemp.Azimuth = lineStrList[3].toDouble();
        tmpV1 = lineStrList[9].toDouble();
        tmpV2 = lineStrList[10].toDouble();
        tmpVR = sqrt((tmpV1*tmpV1) + (tmpV2*tmpV2));
        mapDotTemp.Speed = tmpVR;
        DataConvert::BlhToXyz(mapDotTemp.Lat, mapDotTemp.Lon,0,UTMX,UTMY);//使用转换函数，将轨迹点GPS坐标转换为UTMXY坐标
        mapDotTemp.x = UTMX;
        mapDotTemp.y = UTMY;
        //mapList.append(mapDotTemp);
        //mapList[0].Lat,mapList[0].x, mapList[0].y, mapList[2]关于向量中[]和.的说明
        //mapList为向量，向量里每一个项目为一个结构体
        mapList << mapDotTemp;

        //顺便把图画了 xyz坐标
        picX2 << UTMX ;
        picY2 << UTMY ;
        DataConvert::GetQVMaxMin(picX2 ,UTMXMIN, UTMXMAX);//求UTMX最值
        DataConvert::GetQVMaxMin(picY2 ,UTMYMIN, UTMYMAX); //求UTMY最值

        lineStr = mapSteam.readLine();//写到最后边再检查
    }
    //绘制已经录好轨迹点的坐标
    //设置绘第二张图需要的数据

    ui->plot_UTM->xAxis->setRange(UTMXMIN - 3, UTMXMAX + 3);          //2图x轴范围
    ui->plot_UTM->yAxis->setRange(UTMYMIN - 1, UTMYMAX + 1);          //2图y轴范围
    ui->plot_UTM->xAxis->setLabel("Dd X");     //设置x轴名称
    ui->plot_UTM->yAxis->setLabel("Dd Y");     //设置y轴名称
    ui->plot_UTM->legend->setVisible(false);        //设置每条曲线的说明可见,默认为不可见
    ui->plot_UTM->graph(0)->setData(picX2, picY2);
    ui->plot_UTM->replot();
    picX2.clear();
    picY2.clear();

    //设置直线路段和曲线路段的坐标系，以便在一张图中绘制出两段轨迹；
    QVector<double> strX, strY;
    double zhixian_x, zhixian_y;
    QVector<double> crvX, crvY;
    double quxian_x, quxian_y;

    //给原有轨迹按照航向角的不同进行分组，分为直线路段和曲线路段；
    for(int k=0;k<=mapList.size()-1;k++){
        if( ((mapList[k].Azimuth < 272) & (mapList[k].Azimuth > 268)) | ((mapList[k].Azimuth < 92) & (mapList[k].Azimuth > 88))){
            zhixian_x = mapList[k].x;
            zhixian_y = mapList[k].y;
            strX << zhixian_x;
            strY << zhixian_y;
            mapList[k].expspeed = 5;
        }

        else{
            quxian_x = mapList[k].x;
            quxian_y = mapList[k].y;
            crvX << quxian_x;
            crvY << quxian_y;
            mapList[k].expspeed = 2;
        }
    }


    //画直线轨迹
    ui->plot_UTM->graph(3)->setData(strX, strY);
    ui->plot_UTM->replot();
    strX.clear();
    strY.clear();
    //画弯道
    ui->plot_UTM->graph(4)->setData(crvX, crvY);
    ui->plot_UTM->replot();
    crvX.clear();
    crvY.clear();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::StartAD(){
     m_timerMain->start();
}

void MainWindow::CloseAD(){
     m_timerMain->stop();
}

void MainWindow::GPSRead()
{
    double tmpV11;
    double tmpV22;
    double tmpVRR;
    QByteArray qa = m_comConnect->com_serial.readAll();//通过serial函数读取串口信息
    GPS_rawdata.append(qa);//给GPS_rawdata赋初值

    //ui->textlog1->append(qa);
    ui->text_GPSIMU->append(GPS_rawdata);//让GPSIMU框显示自己车的GPS信息
    if  (!GPS_rawdata.startsWith("$GPHPD"))
    {
        GPS_rawdata.clear();
        return;
    }
    //      0    1          2       3     4       5          6           7     8     9     10     11     12 13 14    15
    // $GPHPD,2056,115180.800,180.117,0.043,276.901,31.1305924,120.6625159,13.00,0.001,-0.006,-0.031,-1.000,17,21,0B*11
    // $GPHPD,2056,115180.800,180.117,0.043,276.901,31.1305924,120.6625159,13.00,0.001,-0.006,-0.031,-1.000,17,21,0B*11
    if  (GPS_rawdata.startsWith("$GPHPD") && GPS_rawdata.endsWith("\n"))
    {
        QString teststr;
        QStringList testStrlist;
        teststr = GPS_rawdata;
        GPS_rawdata.clear();
        testStrlist = teststr.split(",");
        carNow.Lat = testStrlist[6].toDouble();
        carNow.Lon = testStrlist[7].toDouble();
        carNow.Azimuth = testStrlist[3].toDouble();
        tmpV11 = testStrlist[9].toDouble();
        tmpV22 = testStrlist[10].toDouble();
        tmpVRR = sqrt((tmpV11*tmpV11) + (tmpV22*tmpV22));
        carNow.Speed = tmpVRR;
    }


}

/*
 *  核心函数：每隔指定毫秒执行的函数 这个比较关键 用来计算 发送信号
 *  Added By ZhuCJ
 */
void MainWindow::TimeOutMain(){
    qDebug()<<"TimeOutMain";
    //再次理解这句话；
    if(INIT_MODEL == 1){
        QString tmpSetCarString;//临时变量用完就扔
        tmpSetCarString = ui->setCar_lat->text();
        carNow.Lat = tmpSetCarString.toDouble();

        tmpSetCarString = ui->setCar_lon->text();
        carNow.Lon = tmpSetCarString.toDouble();

        tmpSetCarString = ui->setCar_h->text();
        carNow.Azimuth = tmpSetCarString.toDouble();

        carNow.Speed = 3;
    }

    //将自己车GPS坐标转换为UTMXY坐标并绘图
    DataConvert::BlhToXyz(carNow.Lat, carNow.Lon,0,carNow.x,carNow.y);
    QVector<double> carX2, carY2;
    carX2 << carNow.x ;
    carY2 << carNow.y ;
    ui->plot_UTM->graph(2)->setData(carX2, carY2);
    ui->plot_UTM->replot();
    carX2.clear();
    carY2.clear();

    //显示车体位姿信息
    QTime currentTM0 = QTime::currentTime();
    QString tmpMsg0 = QString("%1\ncarX:%2\ncarY:%3\ncarAzimuth:%4\ncarspeed:%5\n")
            .arg(currentTM0.toString("hh:mm:ss:zzz"))
            .arg(carNow.x)
            .arg(carNow.y)
            .arg(carNow.Azimuth)
            .arg(carNow.Speed);
    ui->text_cheti->append(tmpMsg0);

    //遍历，找与实际点距离最近的点,坐标为大地坐标系UTM的XY
    double zuijin_x_path, zuijin_y_path, yumiao_x_path, yumiao_y_path;
    double tmp_distance;
    double min_distance = 0;
    int min_distance_index;
    int j;//j--预瞄点为第j个，i--最近点为第i个；
    for(int i=0;i<=mapList.size()-1;i++){
        DataConvert::BlhToXyz(mapList[i].Lat, mapList[i].Lon,0,mapList[i].x,mapList[i].y);
        //DataConvert::BlhToXyz(mapList[j].Lat, mapList[j].Lon,0,mapList[j].x,mapList[j].y);
        tmp_distance = sqrt((carNow.x-mapList[i].x)*(carNow.x-mapList[i].x)+(carNow.y-mapList[i].y)*(carNow.y-mapList[i].y));
        if(min_distance == 0){
            min_distance = tmp_distance;
            min_distance_index = i;
        }//给最小距离赋初值，当前点与预瞄点的最小值,等价于下面
//         double min_distance = 99999999999999;
//         if(min_distance == 0){
//             min_distance = tmp_distance;
//             min_distance_index = i;
//         }
        if(tmp_distance <= min_distance){
            min_distance = tmp_distance;
            min_distance_index = i;
            j = i+10;//可以进一步优化，设置成j=i+k*v;
            zuijin_x_path = mapList[i].x;
            zuijin_y_path = mapList[i].y;
        }
    }

    //找大地坐标系下的预瞄点坐标并绘图，预瞄点为距离最近点向前推10个
    yumiao_x_path = mapList[j].x;
    yumiao_y_path = mapList[j].y;
    QVector<double> picXYZ_x, picXYZ_y; //画图使用的临时向量 用完即删
    picXYZ_x << yumiao_x_path;
    picXYZ_y << yumiao_y_path;
    ui->plot_UTM->graph(1)->setData(picXYZ_x, picXYZ_y);
    ui->plot_UTM->replot();
    picXYZ_x.clear();
    picXYZ_y.clear();

    //在自己车坐标系下绘制预瞄点的图形
    double yumiao_x_ve, yumiao_y_ve;
    DataConvert::XyzToVehicle(carNow ,yumiao_x_path, yumiao_y_path, yumiao_x_ve , yumiao_y_ve);

    QVector<double> yumiaoX3, yumiaoY3;//设置要绘制图形的向量
    yumiaoX3 << yumiao_x_ve;
    yumiaoY3 << yumiao_y_ve;
    ui->plot_che->graph(0)->setData(yumiaoX3, yumiaoY3);
    ui->plot_che->replot();
    yumiaoX3.clear();
    yumiaoY3.clear();

    //求侧向偏差ey 和航向角偏差efai
    double ey, efai, steery, steerfai, steer;
    double kp1, kd1, kp2;

     //从kp1文本框中读取数据赋值给kp1；
    QString tmpPID;//临时变量，用完就扔；
    tmpPID = ui->kp1->text();
    kp1 = tmpPID.toDouble();
     //从kp2文本框中读取数据赋值给kp2；
    tmpPID = ui->kp2->text();
    kp2 = tmpPID.toDouble();
    kd1 = 0;


    ey = yumiao_x_ve;
    //QString tempey;
    //tempey = QString::number(ey);
    //ui -> ey -> setText(tempey); 在ey框内输入ey信息
    //ey = -(mapList[j].x - carNow.x)*cos(carNow.Azimuth)+(mapList[j].y - carNow.y)*sin(carNow.Azimuth);
    efai = mapList[j].Azimuth - carNow.Azimuth;
    //tempey = QString::number(efai);



    if(efai > 180){
       efai = efai - 360;
    }
    if(efai <-180){
       efai = efai +360;
    }
    //计算steery和steerfai，steer
    steery   = kp1*ey + kd1*0;
    steerfai = kp2*efai;
    steer    = steery + steerfai;  // 31.1293645 120.66194331

    //根据steer给can发信号,限制steer的范围是-500至500；
    if(steer >= 500){
        steer = 500;
    }
    if (steer <= -500){
        steer = -500;
    }

    //CAN控制器和计算出来的steer相反所以取负；
   // m_canConnect->SendSteerCommend(-steer);
    qDebug() << "steer";

    QTime currentTM1 = QTime::currentTime();
    QString tmpMsg1 = QString("%1\ney:%2\nefai:%3\n")
            .arg(currentTM1.toString("hh:mm:ss:zzz"))
            .arg(ey)
            .arg(efai);
    ui->text_CLOG->append(tmpMsg1);

    double kpt, kpb, throttle, brake;

    //从kpt文本框中读取数据赋值给kpt；
    tmpPID = ui->kpt->text();
    kpt = tmpPID.toDouble();

    //从kpb文本框中读取数据赋值给kpb；
    tmpPID = ui->kpb->text();
    kpb = tmpPID.toDouble();

    double ev = mapList[j].expspeed - carNow.Speed;
    if(ev>0){
        if(ev <= 0.1){
            throttle = 0;
        }
        if(ev > 0.1)
            throttle = kpt * ev;
            brake = 0;
    }
    if(ev < 0){
        brake = kpb *ev;
        throttle = 0;
    }




    //显示转角速度制动信息
    QTime currentTM2 = QTime::currentTime();
    QString tmpMsg2 = QString("%1\nSteer:%2\nThrottle:%3\nBrake:%4\n")
            .arg(currentTM2.toString("hh:mm:ss:zzz"))
            .arg(steer)
            .arg(throttle)
            .arg(brake);
    ui -> text_steertho -> append(tmpMsg2);


    //根据throttle和brake发给Can控制器
    // m_canConnect->SendThottleCommend(throttle);
    // m_canConnect->SendBrakeCommend(brake);
     m_canConnect->SendControlCommend(-steer ,throttle ,brake);
}


//画自己车子点

// 找预瞄点

// 画出预瞄点

// 车子知道了 预瞄点知道 车体坐标系可以弄出来 车体坐标系数据补上

// 转向值算出来 怎么算？？？？ 侧方位偏差 + 航向角偏差(预瞄点航向角，当前车子)

//找出直线路段和曲线路段

//设定直线路段和曲线路段的速度

//计算直线路段和曲线路段的油门开度和刹车

//传递给CAN控制器(转角，油门，刹车同时传递）
