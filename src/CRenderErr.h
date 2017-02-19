#ifndef CRENDERERR_H_INCLUDED
#define CRENDERERR_H_INCLUDED

#include "main.h"
#include "GL/gl.h"
#include "math.h"


class CRenderErr
{
    GLuint m_tex;

    double m_frustum;
    double m_r, m_g, m_b, m_a;
    double m_zoom;

public:
    CRenderErr();
    ~CRenderErr();

    void Begin();
    void End();

    void SetFrustum(double frustum);
    void SetRGBA(double r, double g, double b, double a);
    void SetZoom(double zoom);

    void Draw();
    void Update(double misc);
};


#endif // CRENDERERR_H_INCLUDED
