#ifndef SCENE3_H_INCLUDED
#define SCENE3_H_INCLUDED

#include "main.h"
#include "CSoftPosArr.h"
#include "CTexture.h"
#include "CParticles.h"
#include "CFontTGA.h"
#include "CRenderErr.h"
#include "CMeshKlain.h"
#include "CHeightMap.h"
#include "GL/glu.h"


class Scene3
{
    GLUquadricObj *obj_nebo, *obj_planet;
    CTexture *tex_hmap, *tex_klain, *tex_nebo;
    CHeightMap *hmap;
    CSoftPosArr *spos_camera, *spos_direction,
        *spos_direction2, *spos_direction3,
        *spos_direction4, *srotate_klain;
    CMeshKlain *klain;
    CParticles *part_stars, *part_klain;
    CRenderErr *r_eff, *r_eff2, *r_eff3;
    CFontTGA *font_2, *font_3, *font_4, *font_5, *font_6, *font_7;

    double m_regular_alpha, m_planet_angle;

public:
    Scene3();
    ~Scene3();

    void Draw();
    void Update(double misc);

};


#endif // SCENE3_H_INCLUDED
