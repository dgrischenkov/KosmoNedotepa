#ifndef CSOFTPOS_H_INCLUDED
#define CSOFTPOS_H_INCLUDED

#include <math.h>

class CSoftPos
{
    double speed, soft,
        x1, y1, z1,
        x2, y2, z2,
        x3, y3, z3;


public:
    double x, y, z;
    double persent;

    CSoftPos(double speed, double soft,
        double x1=0, double y1=0, double z1=0,
        double x2=0, double y2=0, double z2=0,
        double x3=0, double y3=0, double z3=0);

    void Update(double misc);
    void SetXYZ1(double x1, double y1, double z1);
    void SetXYZ2(double x2, double y2, double z2);
    void SetXYZ3(double x3, double y3, double z3);

};


#endif // CSOFTPOS_H_INCLUDED
