#ifndef SCENE_1_H_INCLUDED
#define SCENE_1_H_INCLUDED

#include "main.h"
#include "CSoftPosArr.h"
#include "CTexture.h"
#include "CParticles.h"
#include "CFontTGA.h"
#include "CRenderErr.h"
#include "CMeshKlain.h"
#include "GL/glu.h"


class Scene_1
{
    GLUquadricObj *obj_nebo;
    CTexture *tex_nebo, *tex_far;
    CMeshKlain *klain, *klain2, *klain3;
    CFontTGA *font_1, *font_2, *font_3, *font_4, *font_5, *font_6;
    CRenderErr *r_eff, *r_eff2;
    CParticles *part_stars;

    double m_regular_alpha, m_klain_angle;

public:
    Scene_1();
    ~Scene_1();

    void Draw();
    void Update(double misc);

};


#endif // SCENE_1_H_INCLUDED
