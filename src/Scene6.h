#ifndef SCENE6_H_INCLUDED
#define SCENE6_H_INCLUDED

#include "main.h"
#include "CSoftPosArr.h"
#include "CTexture.h"
#include "CParticles.h"
#include "CFontTGA.h"
#include "CRenderErr.h"
#include "CMeshKlain.h"
#include "CHeightMap.h"
#include "GL/glu.h"


class Scene6
{
    GLUquadricObj *obj_nebo, *obj_planet, *obj_sf;
    CTexture *tex_hmap, *tex_klain, *tex_nebo;
    CHeightMap *hmap;
    CSoftPosArr *spos_camera, *sdir_camera, *spos_klain, *srot_klain, *sdir_partklain;
    CMeshKlain *klain0, *klain, *klain2, *klain3, *klain4, *klain5;
    CParticles *part_stars, *part_klain;
    CRenderErr *r_eff, *r_eff2, *r_eff3, *r_eff4;
    CFontTGA *font_1, *font_2;

    double m_regular_alpha, m_planet_angle;

public:
    Scene6();
    ~Scene6();

    void Draw();
    void Update(double misc);

};


#endif // SCENE6_H_INCLUDED
