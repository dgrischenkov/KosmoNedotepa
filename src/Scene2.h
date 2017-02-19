#ifndef SCENE2_H_INCLUDED
#define SCENE2_H_INCLUDED

#include "main.h"
#include "CSoftPosArr.h"
#include "CTexture.h"
#include "CParticles.h"
#include "CFontTGA.h"
#include "CRenderErr.h"
#include "CMeshKlain.h"
#include "CHeightMap.h"
#include "GL/glu.h"


class Scene2
{
    GLUquadricObj *obj_nebo, *obj_planet;
    CTexture *tex_hmap, *tex_klain, *tex_nebo;
    CHeightMap *hmap;
    CSoftPosArr *spos_camera, *spos_direction, *spos_direction2, *srotate_klain;
    CMeshKlain *klain;
    CParticles *part_stars, *part_klain;
    CRenderErr *r_eff, *r_eff2, *r_eff3;
    CFontTGA *font_1, *font_2;

    double m_regular_alpha, m_planet_angle;

public:
    Scene2();
    ~Scene2();

    void Draw();
    void Update(double misc);

};


#endif // SCENE2_H_INCLUDED
