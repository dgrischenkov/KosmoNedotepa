#ifndef SCENE7_H_INCLUDED
#define SCENE7_H_INCLUDED

#include "main.h"
#include "CSoftPosArr.h"
#include "CTexture.h"
#include "CParticles.h"
#include "CFontTGA.h"
#include "CRenderErr.h"
#include "CMeshKlain.h"
#include "GL/glu.h"


class Scene7
{
    GLUquadricObj *obj_nebo, *obj_planet;
    CTexture *tex_nebo, *tex_klain;
    CMeshKlain *klain;
    CSoftPosArr *spos_camera, *spos_direction;
    CFontTGA *font_piter, *font_piter2;
    CRenderErr *r_eff, *r_eff2, *r_eff3, *r_eff4;
    CParticles *part_stars, *part_klain, *part_bang, *part_bang2;

    double m_regular_alpha, m_planet_angle, m_alfa_bang;

public:
    Scene7();
    ~Scene7();

    void Draw();
    void Update(double misc);

};


#endif // SCENE7_H_INCLUDED
