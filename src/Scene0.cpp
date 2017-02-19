
#include "Scene0.h"

Scene0::Scene0()
{
    m_regular_alpha=0;

    obj_nebo=gluNewQuadric();
    tex_nebo=new CTexture("cosmo.tga");
    tex_klain=new CTexture("korabl.tga");

    klain=new CMeshKlain(30, 7, KLAIN_LISTOK, 1.3f);
    klain->SetColorCos();
    klain->SetTexture(tex_klain->GetTexID());

    spos_camera=new CSoftPos(0.0003, 10,
        -4, -20, 8,
        4, -20, 0,
        0, -20, 0);

    spos_klain_t=new CSoftPos(0.0001, 10,
        3, -30, 2,
        2, 10, -4,
        -4, 200, 5);

    spos_klain_r=new CSoftPos(0.0003, 10,
        0.4, -0.2, 1,
        -0.4, -0.2, 1,
        0.4, -0.2, 1);

    font_piter=new CFontTGA("Font.tga");
    font_piter->SetText("открытый космос, двадцать парсек от евразии");
    font_piter->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_piter->SetSpeedGliph(100.0f);

    r_eff=new CRenderErr();
    r_eff2=new CRenderErr();
    r_eff2->SetRGBA(1,1,1,0.2f);
    r_eff3=new CRenderErr();

    part_stars=new CParticles(750);
    part_stars->SetGravity(0,0,0);
    part_stars->SetFade(0.003f);
    part_stars->SetSpeed(0.075f);
    part_stars->SetRGB(1.0f, 1.0f, 1.0f);
    part_stars->SetRazbros(0.75f);

    for (int i=0; i<50; i++)
        part_stars->Update(100);

    part_klain=new CParticles(100);
    part_klain->SetRGB(1.0f, 0.2f, 0.3f);
    part_klain->SetDirection(-1, 0, 0);
}


Scene0::~Scene0()
{
//    delete obj_nebo;
    delete tex_nebo;
    delete tex_klain;
    delete klain;
    delete spos_camera;
    delete spos_klain_t;
    delete spos_klain_r;
    delete font_piter;
    delete r_eff;
    delete r_eff2;
    delete r_eff3;
    delete part_stars;
    delete part_klain;
}


void Scene0::Draw()
{
    gluLookAt(spos_camera->x, spos_camera->y, spos_camera->z, 0, 0, 0, 0, 0, 1);


    r_eff3->Begin();
        glPushMatrix();
        glTranslatef(spos_klain_t->x, spos_klain_t->y, spos_klain_t->z);
        glRotatef(90, spos_klain_r->x, spos_klain_r->y, spos_klain_r->z);
        klain->Draw();
        glPopMatrix();
    r_eff3->End();


    r_eff2->Begin();
        glPushMatrix();
        glTranslatef(spos_klain_t->x, spos_klain_t->y, spos_klain_t->z);
        glRotatef(90, spos_klain_r->x, spos_klain_r->y, spos_klain_r->z);
        glTranslatef(-2,0,0);
        part_klain->Draw();
        glPopMatrix();
    r_eff2->End();


    r_eff->Begin();
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_nebo->GetTexID());
        gluQuadricTexture(obj_nebo, GL_TRUE);
        glColor4f(1, 1, 1, 1);
        gluSphere(obj_nebo, 1000, 10, 10);
        glDisable(GL_TEXTURE_2D);

        glPushMatrix();
        glTranslated(0,200,0);
        part_stars->Draw();
        glPopMatrix();

        font_piter->Draw();
    r_eff->End();

    if (m_regular_alpha>1) m_regular_alpha=1;

    r_eff->SetRGBA(1, 1, 1, m_regular_alpha);
    r_eff->Draw();
    r_eff->Draw();

    r_eff3->SetRGBA(1, 1, 1, m_regular_alpha);
    r_eff3->Draw();
    r_eff3->Draw();

    r_eff2->SetRGBA(1, 1, 1, m_regular_alpha/9);
    for (double i=0.95f; i<1.0f; i+=0.005)
    {
        r_eff2->SetZoom(i);
        r_eff2->Draw();
    }
}


void Scene0::Update(double misc)
{
    if (time_line>9000 && time_line<11000) m_regular_alpha+=0.0005*misc;
    if (time_line>23000 && time_line<25000) m_regular_alpha-=0.0005*misc;

    if (time_line>9000+7000) font_piter->Update(misc);

    spos_camera->Update(misc);
    spos_klain_t->Update(misc);
    spos_klain_r->Update(misc);
    r_eff->Update(misc);
    part_stars->Update(misc);
    klain->Update(misc);
    part_klain->Update(misc);
}
