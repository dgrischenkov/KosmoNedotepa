
#include "Scene_0.h"

Scene_0::Scene_0()
{
    m_regular_alpha=0;
    m_klain_angle=47;

    obj_nebo=gluNewQuadric();

    tex_nebo=new CTexture("cosmo.tga");
    tex_far=new CTexture("far.tga");

    klain=new CMeshKlain(40, 40, KLAIN_BUTILKA, 0.75f, 1.5f);
    klain->SetLineType(GL_POINTS);

    klain2=new CMeshKlain(40, 40, KLAIN_BUTILKA, 0.75f, 1.1f);
    klain2->SetLineType(GL_LINES);

    font_1=new CFontTGA("Font.tga");
    font_1->SetText("цель миссии");
    font_1->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_1->SetSpeedGliph(20.0f);
    font_1->SetXYScale(400, 45, 1);

    font_2=new CFontTGA("Font.tga");
    font_2->SetText("- прибыть на демопати");
    font_2->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_2->SetSpeedGliph(20.0f);
    font_2->SetXYScale(335, 90, 1);

    font_3=new CFontTGA("Font.tga");
    font_3->SetText("- найти рандома");
    font_3->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_3->SetSpeedGliph(20.0f);
    font_3->SetXYScale(335, 120, 1);

    font_4=new CFontTGA("Font.tga");
    font_4->SetText("- передать юту интру");
    font_4->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_4->SetSpeedGliph(20.0f);
    font_4->SetXYScale(335, 150, 1);

    font_5=new CFontTGA("Font.tga");
    font_5->SetText("- победить в конкурсе");
    font_5->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_5->SetSpeedGliph(20.0f);
    font_5->SetXYScale(335, 180, 1);

    font_6=new CFontTGA("Font.tga");
    font_6->SetText("- взорвать планету");
    font_6->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_6->SetSpeedGliph(20.0f);
    font_6->SetXYScale(335, 210, 1);
  
    r_eff=new CRenderErr();
    r_eff2=new CRenderErr();
    r_eff2->SetRGBA(1,1,1,0.2f);

    part_stars=new CParticles(1000);
    part_stars->SetGravity(0,0,0);
    part_stars->SetFade(0.001f);
    part_stars->SetSpeed(0.001f);
    part_stars->SetRGB(1.0f, 1.0f, 1.0f);
    part_stars->SetRazbros(10.0f);

    for (int i=0; i<300; i++)
        part_stars->Update(1000);
}


Scene_0::~Scene_0()
{

}


void Scene_0::Draw()
{
    gluLookAt(0, -100, 0, 0, 0, 0, 0, 0, 1);

    r_eff->Begin();
        part_stars->Draw();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_nebo->GetTexID());
        gluQuadricTexture(obj_nebo, GL_TRUE);
        glColor4f(1, 0.5, 0.3, 1);
        gluSphere(obj_nebo, 1800, 10, 10);

        glBindTexture(GL_TEXTURE_2D, tex_far->GetTexID());

        glEnable(GL_BLEND);
        glBegin(GL_QUADS);
            glColor4f(1, 1, 1, 0.75);

            glTexCoord2d(0,0);
            glVertex3d(-100,100, -140);

            glTexCoord2d(0,1);
            glVertex3d(-100, 100, 140);

            glTexCoord2d(1,1);
            glVertex3d(100, 100, 140);

            glTexCoord2d(1,0);
            glVertex3d(100,100, -140);
        glEnd();
        glDisable(GL_BLEND);

        glDisable(GL_TEXTURE_2D);

        font_1->Draw();
        font_2->Draw();
        font_3->Draw();
        font_4->Draw();
        font_5->Draw();
        font_6->Draw();

    r_eff->End();


    r_eff2->Begin();
        glPushMatrix();
            glTranslatef(-36,0,-10);
            glRotatef(45, 0, 0, 1);
            glRotatef(-15, 0, 1, 0);
            glRotatef(m_klain_angle, 1, 0, 0);
            klain->Draw();
        glPopMatrix();


        glPushMatrix();
            glTranslatef(-13,0,0);
            glRotatef(m_klain_angle, 0, 0, 1);
            glRotatef(0, 0, 1, 0);
            glRotatef(90, 1, 0, 0);
            klain2->Draw();
        glPopMatrix();
    r_eff2->End();


    if (m_regular_alpha>1) m_regular_alpha=1;

    r_eff->SetRGBA(1, 1, 1, m_regular_alpha);
    r_eff->Draw();
    r_eff->Draw();

    r_eff2->SetRGBA(1, 1, 1, m_regular_alpha/9);
    for (double i=0.975f; i<1.0f; i+=0.002)
    {
        r_eff2->SetZoom(i);
        r_eff2->Draw();
    }

}


void Scene_0::Update(double misc)
{
    if (time_line>0 && time_line<2000) m_regular_alpha+=0.0005*misc;
    if (time_line>7000 && time_line<9000) m_regular_alpha-=0.0005*misc;
    if (time_line>0+1500) font_1->Update(misc);
    if (time_line>0+2000) font_2->Update(misc);
    if (time_line>0+3000) font_3->Update(misc);
    if (time_line>0+4000) font_4->Update(misc);
    if (time_line>0+5000) font_5->Update(misc);
    if (time_line>0+6000) font_6->Update(misc);

    m_klain_angle+=misc/10;

    part_stars->Update(misc);
}
