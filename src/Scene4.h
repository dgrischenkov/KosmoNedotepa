#ifndef SCENE4_H_INCLUDED
#define SCENE4_H_INCLUDED

#include "main.h"
#include "CSoftPosArr.h"
#include "CTexture.h"
#include "CParticles.h"
#include "CFontTGA.h"
#include "CRenderErr.h"
#include "CMeshKlain.h"
#include "CHeightMap.h"
#include "GL/glu.h"


class Scene4
{
    GLUquadricObj *obj_nebo, *obj_planet;
    CTexture *tex_hmap, *tex_klain, *tex_nebo;
    CHeightMap *hmap;
    CSoftPosArr *spos_camera, *spos_direction3;
    CMeshKlain *klain0, *klain, *klain2, *klain3, *klain4, *klain5;
    CParticles *part_stars, *part_klain, *part_klain2;
    CRenderErr *r_eff, *r_eff2, *r_eff3, *r_eff4, *r_eff5;
    CFontTGA *font_1, *font_2, *font_3, *font_4, *font_5, *font_6;

    double m_regular_alpha, m_planet_angle;

public:
    Scene4();
    ~Scene4();

    void Draw();
    void Update(double misc);

};


#endif // SCENE4_H_INCLUDED
