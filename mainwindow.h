#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>           //Qdebug
#include <QPainter>         //QPainter
#include <QTime>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QtCore/QByteArray>
#include <QVector>

#include "comconnect.h"
#include "canconnect.h"
#include "control.h"
#include "datastruct.h"
#include "dataconvert.h"
#include "qcustomplot.h"

struct carInfo{
    double Lon;
    double Lat;
    double Azimuth;
    double SpeedKM;
};




namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private:
    Ui::MainWindow *ui;


    QString steer;
    CANConnect *m_canConnect;           //can控制器的指针
    COMConnect *m_comConnect;          //com控制器的指针
    QByteArray GPS_rawdata;            //临时存放GPS数据 用于组装
    QTimer     *m_timerMain;            //time控制器的指针

    double Lat;
    double Lon;
    RoadPoint carNow;
    QVector<RoadPoint> mapList;       //记录地图数据结构


private slots:
   void StartAD();         //开始自动驾驶
   void CloseAD();         //关闭自动驾驶
    void TimeOutMain();     //每帧执行的主函数
    void GPSRead();         //GPS有信号就发生的动作
//    void CarPosIn();        //设置自己车的位置使其发生改变--模拟


//    void btn01click();
//    void btn02click();
//    void btn03click();
//    void btn04click();
//    void btn05click();
//    void btn06click();

};

#endif // MAINWINDOW_H
