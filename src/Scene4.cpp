
#include "Scene4.h"

Scene4::Scene4()
{
    m_regular_alpha=0;
    m_planet_angle=1;

    obj_nebo=gluNewQuadric();
    obj_planet=gluNewQuadric();

    tex_hmap=new CTexture("ground.tga");
    tex_klain=new CTexture("korabl.tga");
    tex_nebo=new CTexture("cosmo.tga");

    klain0=new CMeshKlain(30, 7, KLAIN_LISTOK, 1.3f);
    klain0->SetColorCos();
    klain0->SetTexture(tex_klain->GetTexID());

    klain=new CMeshKlain(40, 20, KLAIN_VOSMERKA, 2.0f, 0.5f);
    klain->SetColorCos();
    klain->SetTexture(tex_klain->GetTexID());
    klain->StartEff1();

    klain2=new CMeshKlain(50, 60, KLAIN_VOSMERKA, 2.0f, 0.5f);
    klain2->SetColorCos();
    klain2->StartEff0();

    klain3=new CMeshKlain(50, 60, KLAIN_VOSMERKA, 2.0f, 0.5f);
    klain3->StartEff0();
    klain3->SetLineType(GL_LINES);

    klain4=new CMeshKlain(60, 20, KLAIN_VOSMERKA, 2.0f, 0.6f);
    klain4->SetColorCos();
    klain4->StartEff0();

    klain5=new CMeshKlain(60, 20, KLAIN_VOSMERKA, 2.0f, 0.6f);
    klain5->StartEff0();
    klain5->SetLineType(GL_POINTS);
    glPointSize(3);

    hmap=new CHeightMap("higth_map.raw");
    hmap->SetTexture(tex_hmap->GetTexID());
    hmap->SetScale(2,2,70);

    r_eff=new CRenderErr();
    r_eff2=new CRenderErr();
    r_eff2->SetRGBA(1,1,1,0.2f);
    r_eff3=new CRenderErr();
    r_eff4=new CRenderErr();
    r_eff5=new CRenderErr();
    r_eff5->SetRGBA(1,1,1,0.2f);

    spos_camera=new CSoftPosArr(0.0008, 10);
    spos_camera->AddPoint(20,-7,60);
    spos_camera->AddPoint(20,-7,60);
    spos_camera->AddPoint(20,-7,40);
    spos_camera->AddPoint(20,-8,42);
    spos_camera->AddPoint(20,-15,70);
    spos_camera->AddPoint(0,-20,80);
    spos_camera->AddPoint(-15,-10,80);
    spos_camera->AddPoint(-10,10,85);
    spos_camera->AddPoint(5.6,-4,62.5);
    spos_camera->AddPoint(5.6,-8,50.5);

    spos_direction3=new CSoftPosArr(0.0008, 9);
    spos_direction3->AddPoint(0,-10,45);
    spos_direction3->AddPoint(0,-8,50);
    spos_direction3->AddPoint(0,-10,50);
    spos_direction3->AddPoint(0,-10,50);
    spos_direction3->AddPoint(0,-7,50);
    spos_direction3->AddPoint(0,-7,50);
    spos_direction3->AddPoint(0,-7,50);
    spos_direction3->AddPoint(0,-7,50);
    spos_direction3->AddPoint(5.3,-9.5,50.25);
    spos_direction3->AddPoint(4,-13,50.25);


    font_1=new CFontTGA("Font.tga");
    font_1->SetText("- взрыватель установлен");
    font_1->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_1->SetSpeedGliph(10.0f);
    font_1->SetXYScale(10, 50, 1.3);

    font_2=new CFontTGA("Font.tga");
    font_2->SetText("- так что передаэ приветы");
    font_2->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_2->SetSpeedGliph(10.0f);
    font_2->SetXYScale(10, 100, 1.3);

    font_3=new CFontTGA("Font.tga");
    font_3->SetText("- фоксу, престону, унцу");
    font_3->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_3->SetSpeedGliph(10.0f);
    font_3->SetXYScale(10, 150, 1.3);

    font_4=new CFontTGA("Font.tga");
    font_4->SetText("- тохе, штукеру, афиксу, фз");
    font_4->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_4->SetSpeedGliph(10.0f);
    font_4->SetXYScale(10, 200, 1.3);

    font_5=new CFontTGA("Font.tga");
    font_5->SetText("- агрессору, дозу, драку ");
    font_5->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_5->SetSpeedGliph(10.0f);
    font_5->SetXYScale(10, 250, 1.3);

    font_6=new CFontTGA("Font.tga");
    font_6->SetText("- троексу, зедогу, алиену");
    font_6->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_6->SetSpeedGliph(10.0f);
    font_6->SetXYScale(10, 300, 1.3);


    part_stars=new CParticles(500);
    part_stars->SetGravity(0,0,0);
    part_stars->SetFade(0.001f);
    part_stars->SetSpeed(0.0001f);
    part_stars->SetRGB(1.0f, 1.0f, 1.0f);
    part_stars->SetRazbros(10.0f);

    for (int i=0; i<3000; i++)
        part_stars->Update(1000);

    part_klain=new CParticles(750);
    part_klain->SetRGB(0.0f, 0.75f, 0.5f);
    part_klain->SetGravity(0,0,-0.15);
    part_klain->SetDirection(0,0,1.2);
    part_klain->SetRazbros(1.0);

    for (int i=0; i<100; i++)
        part_klain->Update(100);


    part_klain2=new CParticles(100);
    part_klain2->SetFade(1.0f);
    part_klain2->SetRGB(1.0f, 0.2f, 0.3f);
    part_klain2->SetGravity(0,0,0);
    part_klain2->SetDirection(-1,0,0);

    for (int i=0; i<10; i++)
        part_klain2->Update(100);

}


Scene4::~Scene4()
{

}


void Scene4::Draw()
{
    gluLookAt(spos_camera->getX(), spos_camera->getY(), spos_camera->getZ(),
        spos_direction3->getX(), spos_direction3->getY(), spos_direction3->getZ(), 0, 0, 1);


    r_eff->Begin();
        part_stars->Draw();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, tex_nebo->GetTexID());
        gluQuadricTexture(obj_nebo, GL_TRUE);
        glColor4f(0.2, 0.2, 0.5, 1);
        gluSphere(obj_nebo, 1800, 10, 10);
        glDisable(GL_TEXTURE_2D);

        glPushMatrix();
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, tex_nebo->GetTexID());
            gluQuadricTexture(obj_planet, GL_TRUE);
            glEnable(GL_BLEND);
            glRotatef(m_planet_angle, 0.5f ,-0.1f, 1.0f);
            glColor4f(1.0f, 0.75f, 0.5f, 0.6f);
            gluSphere(obj_nebo, 400, 20, 20);
            glDisable(GL_BLEND);
            glDisable(GL_TEXTURE_2D);
        glPopMatrix();

        glPushMatrix();
            glTranslatef(-200,-200,0);
            hmap->Draw();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(0,-8,50);
            glRotatef(10,0,0,1);
            klain->Draw();
            klain3->Draw();
            klain5->Draw();
        glPopMatrix();

        font_1->Draw();
        font_2->Draw();
        font_3->Draw();
        font_4->Draw();
        font_5->Draw();
        font_6->Draw();

	r_eff->End();


    r_eff4->Begin();
        glPushMatrix();
            glTranslatef(-5,7,40);
            glRotatef(10,0,0,1);
            klain0->Draw();
        glPopMatrix();
    r_eff4->End();


    r_eff5->Begin();
        glPushMatrix();
            glTranslatef(-6,6,40);
            glRotatef(10,0,0,1);
            part_klain2->Draw();
        glPopMatrix();
    r_eff5->End();


    r_eff3->Begin();
        glPushMatrix();
            glTranslatef(0,-8,50);
            klain2->Draw();
            klain4->Draw();
        glPopMatrix();
    r_eff3->End();


    r_eff2->Begin();
        glPushMatrix();
            glTranslatef(0,-8,46.5);
            part_klain->Draw();
        glPopMatrix();
    r_eff2->End();



    if (m_regular_alpha>1) m_regular_alpha=1;

    r_eff->SetRGBA(1, 1, 1, m_regular_alpha);
    r_eff->Draw();
    r_eff->SetRGBA(1, 1, 1, m_regular_alpha/2);
    r_eff->Draw();

    r_eff4->SetRGBA(1, 1, 1, m_regular_alpha);
    r_eff4->Draw();
    r_eff4->Draw();


    r_eff5->SetRGBA(1, 1, 1, m_regular_alpha/9);
    for (double i=0.95f; i<1.0f; i+=0.005)
    {
        r_eff5->SetZoom(i);
        r_eff5->Draw();
    }


    r_eff3->SetRGBA(1, 1, 1, m_regular_alpha/9);
    for (double i=0.95f; i<1.0f; i+=0.0075)
    {
        r_eff3->SetZoom(i);
        r_eff3->Draw();
    }

	r_eff2->SetRGBA(1, 1, 1, (m_regular_alpha/9)*m_planet_angle);
    for (double i=0.975f; i<1.0f; i+=0.001)
    {
        r_eff2->SetZoom(i);
        r_eff2->Draw();
    }

}


void Scene4::Update(double misc)
{
    if (time_line>55000 && time_line<56000) m_regular_alpha+=0.0005*misc*4;
    if (time_line>84500 && time_line<85000) m_regular_alpha-=0.0005*misc*4;
    if (time_line>73000+500) font_1->Update(misc);
    if (time_line>73000+2000) font_2->Update(misc);
    if (time_line>73000+3500) font_3->Update(misc);
    if (time_line>73000+5000) font_4->Update(misc);
    if (time_line>73000+6500) font_5->Update(misc);
    if (time_line>73000+8000) font_6->Update(misc);

    if (m_planet_angle>0) m_planet_angle-=misc/2000;

    spos_camera->Update(misc);
    spos_direction3->Update(misc);

    part_stars->Update(misc);
    part_klain->Update(misc);
    part_klain2->Update(misc);

    klain->Update(misc);
    klain2->Update(misc);
    klain3->Update(misc);
    klain4->Update(misc);
    klain5->Update(misc);
}
