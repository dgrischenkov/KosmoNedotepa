
#include "Scene7.h"

Scene7::Scene7()
{
    m_regular_alpha=0;
    m_alfa_bang=0;

    obj_nebo=gluNewQuadric();
    obj_planet=gluNewQuadric();
    m_planet_angle=200;

    tex_nebo=new CTexture("cosmo.tga");
    tex_klain=new CTexture("korabl.tga");

    klain=new CMeshKlain(30, 7, KLAIN_LISTOK, 1.3f);
    klain->SetColorCos();
    klain->SetTexture(tex_klain->GetTexID());

    spos_camera=new CSoftPosArr(0.005, 10);
    spos_camera->AddPoint(-500,-130,-280);
    spos_camera->AddPoint(-600,-130,-280);
    spos_camera->AddPoint(-600,-130,-280);
    spos_camera->AddPoint(-600,-130,-280);
    spos_camera->AddPoint(-600,-130,-280);

    spos_direction=new CSoftPosArr(0.002, 10);
    spos_direction->AddPoint(-750,-200,-410);
    spos_direction->AddPoint(-750,-200,-410);
    spos_direction->AddPoint(-750,-200,-410);
    spos_direction->AddPoint(-350,-150,-200);
    spos_direction->AddPoint(0,-85,-5);

    r_eff=new CRenderErr();
    r_eff2=new CRenderErr();
    r_eff2->SetRGBA(1,1,1,0.2f);
    r_eff3=new CRenderErr();
    r_eff4=new CRenderErr();
    r_eff4->SetRGBA(1,1,1,0.2f);

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

    part_bang=new CParticles(400);
    part_bang->SetRGB(0.5f, 0.5f, 0.0f);
    part_bang->SetFade(0.1f);
    part_bang->SetSpeed(0.005f);
    part_bang->SetGravity(0,0,0);
    part_bang->SetScale(0.2);
    part_bang->SetRazbros(20.0);
    part_bang->SetDirection(1,0,1);
    part_bang->SetARazkof(3);

    for (int i=0; i<200; i++)
        part_bang->Update(1000);


    part_bang2=new CParticles(400);
    part_bang2->SetRGB(0.2f, 0.75f, 0.2f);
    part_bang2->SetFade(0.1f);
    part_bang2->SetSpeed(0.005f);
    part_bang2->SetGravity(0,0,0);
    part_bang2->SetScale(0.2);
    part_bang2->SetRazbros(10.0);
    part_bang2->SetDirection(1,0,1);

    for (int i=0; i<200; i++)
        part_bang2->Update(1000);
}


Scene7::~Scene7()
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


void Scene7::Draw()
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

        if (time_line<114000+3000)
        {
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
        }

    r_eff->End();


    r_eff2->Begin();
        glPushMatrix();
            glTranslatef(spos_direction->getX(), spos_direction->getY(), spos_direction->getZ());
            part_klain->SetDirection(-0.5, -1, 0.2);
            part_klain->Draw();
        glPopMatrix();
    r_eff2->End();


    r_eff4->Begin();
        glPushMatrix();
            glTranslated(-750,-200,-410);
            part_bang->Draw();
            part_bang2->Draw();
        glPopMatrix();
    r_eff4->End();


    r_eff3->Begin();
        glPushMatrix();
            glTranslatef(spos_direction->getX(), spos_direction->getY(), spos_direction->getZ());
            glTranslatef(8, 0, 4);
            glRotatef(25, 0, 0, 1);
            glRotatef(-20, 0, 1, 0);
            glRotatef(0, 1, 0, 0);
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

    if (time_line>114000+1000 && time_line<114000+1500) m_alfa_bang+=0.075;
    if (time_line>114000+3000 && time_line<114000+4000) m_alfa_bang-=0.04;

    r_eff4->SetRGBA(1, 1, 1, m_regular_alpha/9*m_alfa_bang);
    for (double i=0.9f; i<1.0f; i+=0.005)
    {
        r_eff4->SetZoom(i);
        r_eff4->Draw();
    }

}


void Scene7::Update(double misc)
{
    if (time_line>114000 && time_line<116000) m_regular_alpha+=0.0005*misc;
    if (time_line>122000 && time_line<126000) m_regular_alpha-=0.00025*misc;

    m_planet_angle+=misc/50;

    spos_camera->Update(misc);
    spos_direction->Update(misc);
    part_stars->Update(misc);

    if (time_line<114000+6000) part_klain->Update(misc);

    part_bang->Update(misc);
    part_bang2->Update(misc);

}
