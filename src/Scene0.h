#ifndef SCENE0_H_INCLUDED
#define SCENE0_H_INCLUDED

#include "main.h"
#include "CSoftPos.h"
#include "CTexture.h"
#include "CParticles.h"
#include "CFontTGA.h"
#include "CRenderErr.h"
#include "CMeshKlain.h"
#include "GL/glu.h"


class Scene0
{
    GLUquadricObj *obj_nebo;
    CTexture *tex_nebo, *tex_klain;
    CMeshKlain *klain;
    CSoftPos *spos_camera, *spos_klain_t, *spos_klain_r;
    CFontTGA *font_piter;
    CRenderErr *r_eff, *r_eff2, *r_eff3;
    CParticles *part_stars, *part_klain;

    double m_regular_alpha;

public:
    Scene0();
    ~Scene0();

    void Draw();
    void Update(double misc);

};


#endif // SCENE0_H_INCLUDED
