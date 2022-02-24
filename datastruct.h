#ifndef DATASTRUCT_H
#define DATASTRUCT_H

#define maxd(a,b) ((a)>(b)?(a):(b))
#define mind(a,b) ((a)<(b)?(a):(b))


// 导航数据点

struct RoadPoint
{

    RoadPoint();
    RoadPoint(double _x, double _y, double _Azimuth ,double _type);
    //RoadPoint(struct RoadPoint _s);

    bool valid;                         //  是否有效 预留使用
    int type;                           //  地图点的类型 用来分组使用
    int Index;                          //  索引 预留使用
    double x, y;                        //  大地x 大地y
    double Lat,Lon,Azimuth,Speed;       //  球体坐标精度 球体坐标纬度 行向角 车速(m/s)
    double expspeed;
};


#endif // DATASTRUCT_H
