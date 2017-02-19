
#include "Scene1.h"

Scene1::Scene1()
{
    m_regular_alpha=0;

    obj_nebo=gluNewQuadric();
    obj_planet=gluNewQuadric();
    m_planet_angle=200;

    tex_nebo=new CTexture("cosmo.tga");
    tex_klain=new CTexture("korabl.tga");

    klain=new CMeshKlain(30, 7, KLAIN_LISTOK, 1.3f);
    klain->SetColorCos();
    klain->SetTexture(tex_klain->GetTexID());

    spos_camera=new CSoftPosArr(0.0005, 10);
    spos_camera->AddPoint(100,100,100);
    spos_camera->AddPoint(0,-130,0);
    spos_camera->AddPoint(-100,-100,-50);
    spos_camera->AddPoint(-600,-130,-280);

    spos_direction=new CSoftPosArr(0.0005, 10);
    spos_direction->AddPoint(2,6,4);
    spos_direction->AddPoint(2,-1,0.8f);
    spos_direction->AddPoint(2,1,0.5f);

    font_piter=new CFontTGA("Font.tga");
    font_piter->SetText("привет");
    font_piter->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_piter->SetSpeedGliph(150.0f);
    font_piter->SetXYScale(10, 15, 2);

    font_piter2=new CFontTGA("Font.tga");
    font_piter2->SetText("санкт-петербург!!");
    font_piter2->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_piter2->SetSpeedGliph(150.0f);
    font_piter2->SetXYScale(150, 430, 2);

    r_eff=new CRenderErr();
    r_eff2=new CRenderErr();
    r_eff2->SetRGBA(1,1,1,0.2f);
    r_eff3=new CRenderErr();

    part_stars=new CParticles(1000);
    part_stars->SetGravity(0,0,0);
    part_stars->SetFade(0.001f);
    part_stars->SetSpeed(0.001f);
    part_stars->SetRGB(1.0f, 1.0f, 1.0f);
    part_stars->SetRazbros(10.0f);

    for (int i=0; i<400; i++)
        part_stars->Update(1000);

    part_klain=new CParticles(100);
    part_klain->SetRGB(1.0f, 0.2f, 0.3f);
    part_klain->SetGravity(0,0,0);

    for (int i=0; i<10; i++)
        part_klain->Update(100);
}


Scene1::~Scene1()
{
//    delete obj_nebo;
    delete tex_nebo;
    delete tex_klain;
    delete klain;
    delete spos_camera;
    delete spos_direction;
    delete font_piter;
    delete font_piter2;
    delete r_eff;
    delete r_eff2;
    delete r_eff3;
    delete part_stars;
    delete part_klain;
}


void Scene1::Draw()
{
    gluLookAt(0, -100, 0, spos_camera->getX(), spos_camera->getY(), spos_camera->getZ(), 0, 0, 1);


    r_eff->Begin();
        part_stars->Draw();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_nebo->GetTexID());
        gluQuadricTexture(obj_nebo, GL_TRUE);
        glColor4f(1, 1, 1, 1);
        gluSphere(obj_nebo, 1800, 10, 10);
        glDisable(GL_TEXTURE_2D);

        glPushMatrix();
            glTranslated(-750,-200,-410);

            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, tex_nebo->GetTexID());
            gluQuadricTexture(obj_planet, GL_TRUE);

            glColor4f(1.0f, 0.5f, 0.5f, 1.0f);
            gluSphere(obj_nebo, 140, 20, 20);

            glEnable(GL_BLEND);

            glRotatef(m_planet_angle, 0.5f ,-0.1f, 1.0f);
            glColor4f(0.5f, 0.75f, 1.0f, 0.5f);
            gluSphere(obj_nebo, 142, 20, 20);

            for (double i=0; i<10; i++) {
                glColor4f(0.5f, 0.75f, 1.0f, 0.1f);
                gluSphere(obj_nebo, 142+i, 20, 20);
            }

            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        font_piter->Draw();
        font_piter2->Draw();

    r_eff->End();


    r_eff2->Begin();
        glPushMatrix();
            glTranslatef(spos_camera->getX(), spos_camera->getY(), spos_camera->getZ());
            part_klain->SetDirection(spos_direction->getX(), spos_direction->getY(), spos_direction->getZ());
            part_klain->Draw();
        glPopMatrix();
    r_eff2->End();


    r_eff3->Begin();
        glPushMatrix();
            glTranslatef(spos_camera->getX(), spos_camera->getY(), spos_camera->getZ());
            glRotatef(210, 0, 0, 1);
            glRotatef(10, 0, 1, 0);
            glRotatef(180, 1, 0, 0);
            glTranslatef(1.5f, 0, 0);
            klain->Draw();
        glPopMatrix();
    r_eff3->End();


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


void Scene1::Update(double misc)
{
    if (time_line>25000 && time_line<27000) m_regular_alpha+=0.0005*misc;
    if (time_line>36000 && time_line<38000) m_regular_alpha-=0.0005*misc;
    if (time_line>25000+2500) font_piter->Update(misc);
    if (time_line>25000+4000) font_piter2->Update(misc);

    m_planet_angle+=misc/50;

    spos_camera->Update(misc);
    spos_direction->Update(misc);
    part_stars->Update(misc);
    part_klain->Update(misc);

}
