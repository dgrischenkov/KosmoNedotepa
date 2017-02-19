
#include "Scene2.h"

Scene2::Scene2()
{
    m_regular_alpha=0;

    obj_nebo=gluNewQuadric();
    obj_planet=gluNewQuadric();
    m_planet_angle=0;

    tex_hmap=new CTexture("ground.tga");
    tex_klain=new CTexture("korabl.tga");
    tex_nebo=new CTexture("cosmo.tga");

    klain=new CMeshKlain(30, 7, KLAIN_LISTOK, 1.3f);
    klain->SetColorCos();
    klain->SetTexture(tex_klain->GetTexID());

    hmap=new CHeightMap("higth_map.raw");
    hmap->SetTexture(tex_hmap->GetTexID());
    hmap->SetScale(2,2,70);

    r_eff=new CRenderErr();
    r_eff2=new CRenderErr();
    r_eff2->SetRGBA(1,1,1,0.2f);
    r_eff3=new CRenderErr();

    spos_camera=new CSoftPosArr(0.00085, 5);
    spos_camera->AddPoint(-18,-175,50);
    spos_camera->AddPoint(0,-130,45);
    spos_camera->AddPoint(-20,-145,60);
    spos_camera->AddPoint(-47,-185,55);
    spos_camera->AddPoint(-47,0,75);

    spos_direction=new CSoftPosArr(0.0008, 8);
    spos_direction->AddPoint(75,-160,80);
    spos_direction->AddPoint(-20,-180,40);
    spos_direction->AddPoint(-45,-170,60);
    spos_direction->AddPoint(-40,-50,65);
    spos_direction->AddPoint(-35,0,55);

    spos_direction2=new CSoftPosArr(0.0013, 8);
    spos_direction2->AddPoint(-1,0,0);
    spos_direction2->AddPoint(-0.75,0,0);
    spos_direction2->AddPoint(-0.1,0,0);
    spos_direction2->AddPoint(-5,0,0);
    spos_direction2->AddPoint(-0.75,0,0);
    spos_direction2->AddPoint(-0.5,0,0);

    srotate_klain=new CSoftPosArr(0.0008, 12);
    srotate_klain->AddPoint(180,0,0);
    srotate_klain->AddPoint(180,0,25);
    srotate_klain->AddPoint(90,0,10);
    srotate_klain->AddPoint(90,0,0);
    srotate_klain->AddPoint(20,0,0);

    font_1=new CFontTGA("Font.tga");
    font_1->SetText("добро пожаловать");
    font_1->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_1->SetSpeedGliph(150.0f);
    font_1->SetXYScale(160, 5, 2);

    font_2=new CFontTGA("Font.tga");
    font_2->SetText("на цц ноль девять");
    font_2->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_2->SetSpeedGliph(150.0f);
    font_2->SetXYScale(5, 430, 2);

    part_stars=new CParticles(500);
    part_stars->SetGravity(0,0,0);
    part_stars->SetFade(0.001f);
    part_stars->SetSpeed(0.0001f);
    part_stars->SetRGB(1.0f, 1.0f, 1.0f);
    part_stars->SetRazbros(10.0f);

    for (int i=0; i<4000; i++)
        part_stars->Update(1000);

    part_klain=new CParticles(100);
    part_klain->SetRGB(1.0f, 0.2f, 0.3f);
    part_klain->SetGravity(0,0,0);

    for (int i=0; i<10; i++)
        part_klain->Update(100);

}


Scene2::~Scene2()
{

}


void Scene2::Draw()
{
    gluLookAt(spos_camera->getX(), spos_camera->getY(), spos_camera->getZ(),
        spos_direction->getX(), spos_direction->getY(), spos_direction->getZ(), 0, 0, 1);


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

        font_1->Draw();
        font_2->Draw();

	r_eff->End();


    r_eff3->Begin();
        glPushMatrix();
            glTranslatef(spos_direction->getX(), spos_direction->getY(), spos_direction->getZ());
            glRotatef(srotate_klain->getX(), 0, 0, 1);
            glRotatef(srotate_klain->getY(), 0, 1, 0);
            glRotatef(srotate_klain->getZ(), 1, 0, 0);
            glTranslatef(1.5f, 0, 0);
            klain->Draw();
        glPopMatrix();
    r_eff3->End();


    r_eff2->Begin();
        glPushMatrix();
            glTranslatef(spos_direction->getX(), spos_direction->getY(), spos_direction->getZ());
            glRotatef(srotate_klain->getX(), 0, 0, 1);
            glRotatef(srotate_klain->getY(), 0, 1, 0);
            glRotatef(srotate_klain->getZ(), 1, 0, 0);
            part_klain->SetDirection(spos_direction2->getX(), spos_direction2->getY(), spos_direction2->getZ());
            part_klain->Draw();
        glPopMatrix();
    r_eff2->End();



    if (m_regular_alpha>1) m_regular_alpha=1;

    r_eff->SetRGBA(1, 1, 1, m_regular_alpha);
    r_eff->Draw();

    r_eff->SetRGBA(1, 1, 1, m_regular_alpha/2);
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


void Scene2::Update(double misc)
{
    if (time_line>38000 && time_line<40000) m_regular_alpha+=0.0005*misc;
    if (time_line>49000 && time_line<50000) m_regular_alpha-=0.0005*misc*2;
    if (time_line>41000+2000) font_1->Update(misc);
    if (time_line>41000+4000) font_2->Update(misc);

    m_planet_angle+=misc/50;

    spos_camera->Update(misc);
    spos_direction->Update(misc);
    spos_direction2->Update(misc);
    srotate_klain->Update(misc);

    part_stars->Update(misc);
    part_klain->Update(misc);
}
