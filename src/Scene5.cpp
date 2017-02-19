
#include "Scene5.h"

Scene5::Scene5()
{
    m_regular_alpha=0;

    tex_klain=new CTexture("korabl.tga");

    klain=new CMeshKlain(40, 40, KLAIN_VOSMERKA, 2.0f, 0.3f);
    klain->SetColorCos();
    klain->SetTexture(tex_klain->GetTexID());

    klain2=new CMeshKlain(60, 70, KLAIN_VOSMERKA, 2.0f, 0.31f);
    klain2->SetColorCos();
    klain2->StartEff0();

    klain3=new CMeshKlain(60, 70, KLAIN_VOSMERKA, 2.0f, 0.31f);
    klain3->StartEff0();
    klain3->SetLineType(GL_LINES);

    r_eff=new CRenderErr();
    r_eff2=new CRenderErr();
    r_eff2->SetRGBA(1,1,1,0.2f);

    font_1=new CFontTGA("Font.tga");
    font_1->SetText("- бомба активизирована");
    font_1->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_1->SetSpeedGliph(10.0f);
    font_1->SetXYScale(10, 360, 0.8);

    font_2=new CFontTGA("Font.tga");
    font_2->SetText("- удаленный доспут закрыт");
    font_2->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_2->SetSpeedGliph(10.0f);
    font_2->SetXYScale(10, 380, 0.8);

    font_3=new CFontTGA("Font.tga");
    font_3->SetText("- деактивация невозможна ");
    font_3->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_3->SetSpeedGliph(10.0f);
    font_3->SetXYScale(10, 400, 0.8);

    font_4=new CFontTGA("Font.tga");
    font_4->SetText("- врыв очень-очень скоро ");
    font_4->SetRGBA(0.0f, 1.0f, 0.0f, 1.0f);
    font_4->SetSpeedGliph(10.0f);
    font_4->SetXYScale(10, 420, 0.8);


    spos_camera=new CSoftPosArr(0.0027, 7);
    spos_camera->AddPoint(9.5, 0.8, 0.6);
    spos_camera->AddPoint(9.5, 0.8, 0.6);
    spos_camera->AddPoint(7.8, -4.9, 0.6);
    spos_camera->AddPoint(-2.0, -8.7, -1.8);
    spos_camera->AddPoint(-6.2, -6.6, -0.8);
    spos_camera->AddPoint(-7.6, 0.1, -1.9);
    spos_camera->AddPoint(-3.1, 5.5, -1.9);
    spos_camera->AddPoint(2.9, 5.5, -1.9);
    spos_camera->AddPoint(5.1, 0.9, 1.0);
    spos_camera->AddPoint(5.1, -3.3, 0.9);
    spos_camera->AddPoint(1.1, -6.5, 0.9);
    spos_camera->AddPoint(-6, -3.4, 2.7);
    spos_camera->AddPoint(-7.2, 1.3, 2.7);
    spos_camera->AddPoint(-3.9, 6.4, 1.4);
    spos_camera->AddPoint(2.8, 7.7, 1.9);
    spos_camera->AddPoint(7.5, 4.5, 0.7);
    spos_camera->AddPoint(8.6, -1.9, 0.7);
    spos_camera->AddPoint(7.8, -4.9, 0.6);
    spos_camera->AddPoint(-2.0, -8.7, -1.8);
    spos_camera->AddPoint(-6.2, -6.6, -0.8);
    spos_camera->AddPoint(-7.6, 0.1, -1.9);
    spos_camera->AddPoint(-3.1, 5.5, -1.9);

    sdir_camera=new CSoftPosArr(0.0027, 7);
    sdir_camera->AddPoint(7.1, -5.9, -0.4);
    sdir_camera->AddPoint(7.1, -5.9, -0.4);
    sdir_camera->AddPoint(5.3, -7.1, -0.5);
    sdir_camera->AddPoint(-2.9, -7.3, -1.9);
    sdir_camera->AddPoint(-6.1, 0.0, -1.9);
    sdir_camera->AddPoint(-0.7, 7.4, -1.4);
    sdir_camera->AddPoint(3.0, 4.6, -0.8);
    sdir_camera->AddPoint(5.9, -0.2, 0.9);
    sdir_camera->AddPoint(4.2, -5.6, 1.5);
    sdir_camera->AddPoint(-1.4, -5.4, 1.5);
    sdir_camera->AddPoint(-7.1, -2.6, 1.5);
    sdir_camera->AddPoint(-7.3, 3.7, 1.5);
    sdir_camera->AddPoint(-0.9, 9.4, 1.5);
    sdir_camera->AddPoint(3.3, 8.1, 1.5);
    sdir_camera->AddPoint(7.9, 4.0, 0.7);
    sdir_camera->AddPoint(8.9, -2.6, -1.1);
    sdir_camera->AddPoint(3.9, -8.2, -1.1);
    sdir_camera->AddPoint(5.3, -7.1, -0.5);
    sdir_camera->AddPoint(-2.9, -7.3, -1.9);
    sdir_camera->AddPoint(-6.1, 0.0, -1.9);
    sdir_camera->AddPoint(-0.7, 7.4, -1.4);
    sdir_camera->AddPoint(3.0, 4.6, -0.8);
}


Scene5::~Scene5()
{

}


void Scene5::Draw()
{

    gluLookAt(spos_camera->getX(), spos_camera->getY(), spos_camera->getZ(),
        sdir_camera->getX(), sdir_camera->getY(), sdir_camera->getZ(), 0, 0, 1);

    r_eff->Begin();
        klain->Draw();
        klain3->Draw();

        font_1->Draw();
        font_2->Draw();
        font_3->Draw();
        font_4->Draw();
	r_eff->End();

    r_eff2->Begin();
        klain2->Draw();
    r_eff2->End();


    if (m_regular_alpha>1) m_regular_alpha=1;

    r_eff->SetRGBA(1, 1, 1, m_regular_alpha);
    r_eff->Draw();
    r_eff->Draw();

    r_eff2->SetRGBA(1, 1, 1, m_regular_alpha/9);
    for (double i=0.95f; i<1.0f; i+=0.0075)
    {
        r_eff2->SetZoom(i);
        r_eff2->Draw();
    }
}


void Scene5::Update(double misc)
{
    if (time_line>85000 && time_line<86000) m_regular_alpha+=0.0005*misc*3;
    if (time_line>90000 && time_line<92000) m_regular_alpha-=0.0005*misc;
    if (time_line>86000+500) font_1->Update(misc);
    if (time_line>86000+1000) font_2->Update(misc);
    if (time_line>86000+1500) font_3->Update(misc);
    if (time_line>86000+2000) font_4->Update(misc);

    spos_camera->Update(misc);
    sdir_camera->Update(misc);

    klain->Update(misc);
    klain2->Update(misc);
    klain3->Update(misc);
}
