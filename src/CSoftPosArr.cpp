
#include "CSoftPosArr.h"

CSoftPosArr::CSoftPosArr(double speed, double soft)
{
    m_points=new m_Point[80];
    m_sp=new CSoftPos(speed, soft);

    curent_sp=0;
    curent_point=0;
    end_point=0;
}


CSoftPosArr::~CSoftPosArr()
{
    delete [] m_points;
    delete m_sp;
}


void CSoftPosArr::Update(double misc)
{
    if (curent_point==0)
    {
        m_sp->SetXYZ1(m_points[0].x, m_points[0].y, m_points[0].z);
        m_sp->SetXYZ2(m_points[1].x, m_points[1].y, m_points[1].z);
        m_sp->SetXYZ3(m_points[2].x, m_points[2].y, m_points[2].z);
        curent_point=2;
    }

    m_sp->Update(misc);

    if (m_sp->persent > 0.95 && curent_point<end_point-1)
    {
        m_sp->persent=0;
        m_sp->SetXYZ1(m_sp->x, m_sp->y, m_sp->z);
        m_sp->SetXYZ2(m_points[curent_point].x, m_points[curent_point].y, m_points[curent_point].z);
        curent_point++;
        m_sp->SetXYZ3(m_points[curent_point].x, m_points[curent_point].y, m_points[curent_point].z);
    }
}


void CSoftPosArr::AddPoint(double x, double y, double z)
{
    m_points[end_point].x=x;
    m_points[end_point].y=y;
    m_points[end_point].z=z;
    end_point++;
}


double CSoftPosArr::getX()
{
    return m_sp->x;
}


double CSoftPosArr::getY()
{
    return m_sp->y;
}


double CSoftPosArr::getZ()
{
    return m_sp->z;
}
