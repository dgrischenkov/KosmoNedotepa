
#include "Scene6.h"

Scene6::Scene6()
{
    m_regular_alpha=0;
    m_planet_angle=0;

    obj_nebo=gluNewQuadric();
    obj_planet=gluNewQuadric();
    obj_sf=gluNewQuadric();

    tex_hmap=new CTexture("ground.tga");
    tex_klain=new CTexture("korabl.tga");
    tex_nebo=new CTexture("cosmo.tga");

    klain0=new CMeshKlain(30, 7, KLAIN_LISTOK, 1.3f);
    klain0->SetColorCos();
    klain0->SetTexture(tex_klain->GetTexID());

    klain=new CMeshKlain(40, 20, KLAIN_VOSMERKA, 2.0f, 0.5f);
    klain->SetTexture(tex_klain->GetTexID());
    klain->SetColorCos();

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
    r_eff4->SetRGBA(1,1,1,0.2f);


    spos_camera=new CSoftPosArr(0.0018,9);
    spos_camera->AddPoint(-31.4, -4.6, 67);
    spos_camera->AddPoint(-27.3, -2.5, 66.5);
    spos_camera->AddPoint(-27.2, 5.0, 54.1);
    spos_camera->AddPoint(5.8, 7.6, 72.0);
    spos_camera->AddPoint(6.5, 1.5, 61.6);
    spos_camera->AddPoint(-46.3, -15.5, 61.6);
    spos_camera->AddPoint(-44.8, 63.9, 53.2);
    spos_camera->AddPoint(-43.2, 83.9, 72.1);
    spos_camera->AddPoint(-52.0, 124.9, 108.0);
    spos_camera->AddPoint(-18.7, 145.7, 144.6);
    spos_camera->AddPoint(39.2, 131.1, 181.7);
    spos_camera->AddPoint(74.2, 61.9, 251.7);
    spos_camera->AddPoint(69.9, 24.8, 336.3);
    spos_camera->AddPoint(66.6, 18.7, 371.7);

    sdir_camera=new CSoftPosArr(0.0018,9);
    sdir_camera->AddPoint(-0.2, 3.9, 40.9);
    sdir_camera->AddPoint(23.6, -0.5, 51.0);
    sdir_camera->AddPoint(24.6, -13.9, 56.0);
    sdir_camera->AddPoint(-8.6, -15.2, 54.0);
    sdir_camera->AddPoint(-39.5, -1.1, 54.8);
    sdir_camera->AddPoint(-46.1, 11.1, 54.6);
    sdir_camera->AddPoint(-44.5, 77.2, 52.4);
     sdir_camera->AddPoint(-35.7, 99.7, 72.7);
     sdir_camera->AddPoint(5.0, 127.4, 54.5);
     sdir_camera->AddPoint(0.0, 105.0, 55.0);
     sdir_camera->AddPoint(0.0, 65.1, 65.0);
     sdir_camera->AddPoint(0.0, 32.2, 59.9);
     sdir_camera->AddPoint(0.0, 0.0, 70.0);
     sdir_camera->AddPoint(0.0, 0.0, 70.0);

    spos_klain=new CSoftPosArr(0.0018,9);
    spos_klain->AddPoint(-0.2, 3.9, 40.9);
    spos_klain->AddPoint(23.6, -0.5, 51.0);
    spos_klain->AddPoint(24.6, -13.9, 56.0);
    spos_klain->AddPoint(-8.6, -15.2, 54.0);
    spos_klain->AddPoint(-39.5, -1.1, 54.8);
    spos_klain->AddPoint(-46.1, 11.1, 54.6);
    spos_klain->AddPoint(-44.5, 77.2, 52.4);
     spos_klain->AddPoint(-41.4, 132.4, 52.6);
     spos_klain->AddPoint(-38.6, 142.4, 72.8);
     spos_klain->AddPoint(-31.6, 147.1, 99.4);
     spos_klain->AddPoint(-31.6, 147.1, 99.4);
     spos_klain->AddPoint(72.0, 65, 220);
     spos_klain->AddPoint(67.0, 0, 300);
     spos_klain->AddPoint(62.0, -65, 380);

    srot_klain=new CSoftPosArr(0.0018,9);
    srot_klain->AddPoint(10,10,180);
    srot_klain->AddPoint(10,10,180);
    srot_klain->AddPoint(10,10,180);
    srot_klain->AddPoint(10,10,180);
    srot_klain->AddPoint(10,10,90);
    srot_klain->AddPoint(10,10,75);
    srot_klain->AddPoint(10,10,75);
    srot_klain->AddPoint(10,10,75);
    srot_klain->AddPoint(10,10,-90);
    srot_klain->AddPoint(10,10,-90);
    srot_klain->AddPoint(10,10,-90);

    sdir_partklain=new CSoftPosArr(0.0017,9);
    sdir_partklain->AddPoint(-1,-1,-2);
    sdir_partklain->AddPoint(-1,-0.5,0);
    sdir_partklain->AddPoint(-1,0,0);
    sdir_partklain->AddPoint(-1,0,0);
    sdir_partklain->AddPoint(-2,0,0);
    sdir_partklain->AddPoint(-2,0,0);
    sdir_partklain->AddPoint(-3,0,0);
    sdir_partklain->AddPoint(-3,0,0);
    sdir_partklain->AddPoint(-3,0,0);
    sdir_partklain->AddPoint(-2,0,0);



    part_stars=new CParticles(500);
    part_stars->SetGravity(0,0,0);
    part_stars->SetFade(0.001f);
    part_stars->SetSpeed(0.0001f);
    part_stars->SetRGB(1.0f, 1.0f, 1.0f);
    part_stars->SetRazbros(10.0f);

    for (int i=0; i<3500; i++)
        part_stars->Update(1000);

    part_klain=new CParticles(100);
    part_klain->SetRGB(1.0f, 0.2f, 0.3f);
    part_klain->SetGravity(0,0,0);

    for (int i=0; i<100; i++)
        part_klain->Update(100);

}


Scene6::~Scene6()
{

}


void Scene6::Draw()
{
    gluLookAt(spos_camera->getX(), spos_camera->getY(), spos_camera->getZ(),
        sdir_camera->getX(), sdir_camera->getY(), sdir_camera->getZ(), 0, 0, 1);


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
            klain->Draw();
            klain3->Draw();
            klain5->Draw();
        glPopMatrix();

        glPushMatrix();
            glTranslatef(glob_x_rot, glob_y_rot, glob_z_rot);
            glColor4f(1,1,1,1);
            gluSphere(obj_sf, 0.1, 10, 10);
        glPopMatrix();

    r_eff->End();


    r_eff3->Begin();
        glPushMatrix();
            glTranslatef(0,-8,50);
            klain2->Draw();
            klain4->Draw();
        glPopMatrix();
    r_eff3->End();


    r_eff2->Begin();
        glPushMatrix();
            glTranslatef(spos_klain->getX(), spos_klain->getY(), spos_klain->getZ());
            glRotatef(srot_klain->getX(), 1, 0, 0);
            glRotatef(srot_klain->getY(), 0, 1, 0);
            glRotatef(srot_klain->getZ(), 0, 0, 1);
            part_klain->SetDirection(sdir_partklain->getX(), sdir_partklain->getY(), sdir_partklain->getZ());
            part_klain->Draw();
        glPopMatrix();
    r_eff2->End();


    r_eff4->Begin();
        glPushMatrix();
            glTranslatef(spos_klain->getX(), spos_klain->getY(), spos_klain->getZ());
            glRotatef(srot_klain->getX(), 1, 0, 0);
            glRotatef(srot_klain->getY(), 0, 1, 0);
            glRotatef(srot_klain->getZ(), 0, 0, 1);
            glTranslatef(1.5f, 0, 0);
            klain0->Draw();
        glPopMatrix();
    r_eff4->End();


    if (m_regular_alpha>1) m_regular_alpha=1;

    r_eff->SetRGBA(1, 1, 1, m_regular_alpha);
    r_eff->Draw();
    r_eff->SetRGBA(1, 1, 1, m_regular_alpha/2);
    r_eff->Draw();

    r_eff4->SetRGBA(1, 1, 1, m_regular_alpha);
    r_eff4->Draw();
    r_eff4->Draw();

    r_eff3->SetRGBA(1, 1, 1, m_regular_alpha/9);
    for (double i=0.95f; i<1.0f; i+=0.0075)
    {
        r_eff3->SetZoom(i);
        r_eff3->Draw();
    }

    r_eff2->SetRGBA(1, 1, 1, m_regular_alpha/9);
    for (double i=0.95f; i<1.0f; i+=0.005)
    {
        r_eff2->SetZoom(i);
        r_eff2->Draw();
    }

}


void Scene6::Update(double misc)
{
    if (time_line>92000 && time_line<94000) m_regular_alpha+=0.0005*misc;
    if (time_line>112000 && time_line<114000) m_regular_alpha-=0.0005*misc;

    m_planet_angle+=misc/50;

    spos_camera->Update(misc);
    sdir_camera->Update(misc);
    spos_klain->Update(misc);
    srot_klain->Update(misc);
    sdir_partklain->Update(misc);

    part_stars->Update(misc);
    part_klain->Update(misc);

    klain->Update(misc);
    klain2->Update(misc);
    klain3->Update(misc);
    klain4->Update(misc);
    klain5->Update(misc);
}
