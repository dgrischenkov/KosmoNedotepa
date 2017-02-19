#ifndef CSOFTPOSARR_H_INCLUDED
#define CSOFTPOSARR_H_INCLUDED

#include "CSoftPos.h"


class CSoftPosArr
{
    struct m_Point{
        double x, y, z;
    } *m_points;

    CSoftPos *m_sp;
    int curent_sp;
    int curent_point;
    int end_point;


public:
    CSoftPosArr(double speed, double soft);
    ~CSoftPosArr();

    void Update(double misc);

    void AddPoint(double x, double y, double z);
    double getX();
    double getY();
    double getZ();
};



#endif // CSOFTPOSARR_H_INCLUDED
