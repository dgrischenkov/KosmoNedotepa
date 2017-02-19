#ifndef SCENE5_H_INCLUDED
#define SCENE5_H_INCLUDED

#include "main.h"
#include "CSoftPosArr.h"
#include "CTexture.h"
#include "CParticles.h"
#include "CFontTGA.h"
#include "CRenderErr.h"
#include "CMeshKlain.h"
#include "CHeightMap.h"
#include "GL/glu.h"


class Scene5
{
    CTexture *tex_klain;
    CSoftPosArr *spos_camera, *sdir_camera;
    CMeshKlain *klain, *klain2, *klain3;
    CRenderErr *r_eff, *r_eff2;
    CFontTGA *font_1, *font_2, *font_3, *font_4;

    double m_regular_alpha;

public:
    Scene5();
    ~Scene5();

    void Draw();
    void Update(double misc);

};


#endif // SCENE5_H_INCLUDED
