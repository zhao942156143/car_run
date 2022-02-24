#ifndef DATACONVERT_H
#define DATACONVERT_H
#include "datastruct.h"
#include <QVector>

class DataConvert
{
public:
    // 球体坐标
    static double angToRad(double angle_d);

    static void BlhToXyz(double B, double L, double H,double &x,double &y);

    static void XyzToVehicle(struct RoadPoint carPos ,double x_path, double y_path, double &x_vehicle , double &y_vehicle);

    // 根据经度求中央子午线经度
    static double GetL0InDegree(double dLIn);

    // 计算两点之间距离
    static double GetDistance(double x1, double y1, double x2, double y2);
    //计算向量最值
    static void GetQVMaxMin(QVector<double>theV , double &theMin ,double &theMax);

};

#endif // DATACONVERT_H
