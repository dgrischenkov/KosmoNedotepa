#ifndef CHEIGHTMAP_H_INCLUDED
#define CHEIGHTMAP_H_INCLUDED

#include <stdio.h>
#include <windows.h>
#include <math.h>
#include "GL/gl.h"


class CHeightMap
{
    unsigned char *m_map_data;
    int m_map_size;
    GLuint m_texture;
    double m_scale_x, m_scale_y, m_scale_z;

public:
    CHeightMap(const char *filename);
    ~CHeightMap();

    void SetTexture(GLuint texture);
    void SetScale(double x, double y, double z);

    void Draw();
    void Update(double misc);

};


#endif // CHEIGHTMAP_H_INCLUDED
