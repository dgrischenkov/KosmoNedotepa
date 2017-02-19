
#include "CSoftPos.h"

CSoftPos::CSoftPos(double _speed, double _soft,
        double _x1, double _y1, double _z1,
        double _x2, double _y2, double _z2,
        double _x3, double _y3, double _z3)
{
    speed=_speed;
    soft=_soft;
    x1=_x1; y1=_y1; z1=_z1;
    x2=_x2; y2=_y2; z2=_z2;
    x3=_x3; y3=_y3; z3=_z3;
    persent=0;
}


void CSoftPos::Update(double misc)
{
    double delta=misc*speed;
    delta*=1-persent;

    if (persent<1) persent+=delta;

    x=x1+(x2-x1)*persent+(x3-x2)*pow(persent, soft);
    y=y1+(y2-y1)*persent+(y3-y2)*pow(persent, soft);
    z=z1+(z2-z1)*persent+(z3-z2)*pow(persent, soft);

}


void CSoftPos::SetXYZ1(double _x1, double _y1, double _z1)
{
    x1=_x1;
    y1=_y1;
    z1=_z1;
}


void CSoftPos::SetXYZ2(double _x2, double _y2, double _z2)
{
    x2=_x2;
    y2=_y2;
    z2=_z2;
}


void CSoftPos::SetXYZ3(double _x3, double _y3, double _z3)
{
    x3=_x3;
    y3=_y3;
    z3=_z3;
}
