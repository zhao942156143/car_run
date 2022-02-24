#include "dataconvert.h"
#include "math.h"

#include <QDebug>

#define M_PI 3.14159265358979323846

//DataConvert::BlhToXyz(Lat, Lon,0,x,y);
void DataConvert::BlhToXyz(double B, double L, double H,double &x,double &y)
{
    H = 0;  //暂时不使用H
    double N, E;
    double L0 = GetL0InDegree(L);    //根据经度求中央子午线经度

    double a = 6378245.0;            //地球半径  北京6378245
    double F = 298.257223563;        //地球扁率
    double iPI = 0.0174532925199433; //2pi除以360，用于角度转换

    double f = 1 / F;
    double b = a * (1 - f);
    double ee = (a * a - b * b) / (a * a);
    double e2 = (a * a - b * b) / (b * b);
    double n = (a - b) / (a + b), n2 = (n * n), n3 = (n2 * n), n4 = (n2 * n2), n5 = (n4 * n);
    double al = (a + b) * (1 + n2 / 4 + n4 / 64) / 2;
    double bt = -3 * n / 2 + 9 * n3 / 16 - 3 * n5 / 32;
    double gm = 15 * n2 / 16 - 15 * n4 / 32;
    double dt = -35 * n3 / 48 + 105 * n5 / 256;
    double ep = 315 * n4 / 512;

    B = B * iPI;
    L = L * iPI;
    L0 = L0 * iPI;

    double l = L - L0, cl = (cos(B) * l), cl2 = (cl * cl), cl3 = (cl2 * cl), cl4 = (cl2 * cl2), cl5 = (cl4 * cl), cl6 = (cl5 * cl), cl7 = (cl6 * cl), cl8 = (cl4 * cl4);
    double lB = al * (B + bt * sin(2 * B) + gm * sin(4 * B) + dt * sin(6 * B) + ep * sin(8 * B));
    double t = tan(B), t2 = (t * t), t4 = (t2 * t2), t6 = (t4 * t2);
    double Nn = a / sqrt(1 - ee * sin(B) * sin(B));
    double yt = e2 * cos(B) * cos(B);
    N = lB;
    N += t * Nn * cl2 / 2;
    N += t * Nn * cl4 * (5 - t2 + 9 * yt + 4 * yt * yt) / 24;
    N += t * Nn * cl6 * (61 - 58 * t2 + t4 + 270 * yt - 330 * t2 * yt) / 720;
    N += t * Nn * cl8 * (1385 - 3111 * t2 + 543 * t4 - t6) / 40320;

    E = Nn * cl;
    E += Nn * cl3 * (1 - t2 + yt) / 6;
    E += Nn * cl5 * (5 - 18 * t2 + t4 + 14 * yt - 58 * t2 * yt) / 120;
    E += Nn * cl7 * (61 - 479 * t2 + 179 * t4 - t6) / 5040;

    E += 500000;

    //UTM投影
    N = 0.9996 * N;
    E = 0.9996 * (E - 500000.0) + 250000.0;//Get y

    x = E , y = N;
}

//大地平面坐标 转化为车体坐标
// carPos 当前你车子的状态 xy和航向角 x_path:目标点X y_path:目标点Y
void DataConvert::XyzToVehicle(struct RoadPoint carPos ,double x_path, double y_path, double &x_vehicle , double &y_vehicle)
{
    double theta = atan2(x_path - carPos.x , y_path - carPos.y);
    double distance = sqrt((x_path - carPos.x) * (x_path - carPos.x) + (y_path - carPos.y) * (y_path - carPos.y));
    double angle = theta - (-90 + carPos.Azimuth) / 180 * M_PI;

    x_vehicle =  - cos(angle) * distance;
    y_vehicle =    sin(angle) * distance;
}

double DataConvert::GetL0InDegree(double dLIn)
{
    double L = dLIn;//d.d
    double L_ddd_Style = L;
    double ZoneNumber = (int)((L_ddd_Style - 1.5) / 3.0) + 1;
    double L0 = ZoneNumber * 3.0;//degree
    return L0;
}

//下面方法让学员自己完成
double DataConvert::GetDistance(double x1, double y1, double x2, double y2)
{
    return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}


void DataConvert::GetQVMaxMin(QVector<double> theV , double &theMin ,double &theMax)
{
    theMin = 9999999999;
    theMax = 0;
    for(int i=0;i<theV.size();i++){
        //qDebug()<< theV[i];
        if(theV[i] < theMin){theMin = theV[i];}
        if(theV[i] > theMax){theMax = theV[i];}
    }

}

