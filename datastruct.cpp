#include "datastruct.h"

RoadPoint::RoadPoint()
{
    valid = false;
    Lat     = 0;
    Lon     = 0;
    Azimuth = 0;
    Speed   = 0;
    type    = 0;
    Index   = 0;
}


RoadPoint::RoadPoint(double _x, double _y, double _Azimuth , double _type)
{
    x = _x;
    y = _y;
    Azimuth = _Azimuth;
    type    = _type;
}


