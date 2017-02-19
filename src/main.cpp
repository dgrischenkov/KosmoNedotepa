
//#pragma comment(linker, "/ENTRY:main")

#include "main.h"
#include "CDriverWin.h"
#include "Scene_0.h"
#include "Scene0.h"
#include "Scene1.h"
#include "Scene2.h"
#include "Scene3.h"
#include "Scene4.h"
#include "Scene5.h"
#include "Scene6.h"
#include "Scene7.h"
#include "Scene_1.h"
#include "fmod.h"

CDriverWin *driver;
Scene_0 *scene_0;
Scene0 *scene0;
Scene1 *scene1;
Scene2 *scene2;
Scene3 *scene3;
Scene4 *scene4;
Scene5 *scene5;
Scene6 *scene6;
Scene7 *scene7;
Scene_1 *scene_1;

double time_line=0;


double glob_x_pos=0, glob_y_pos=0, glob_z_pos=0;
double glob_x_rot=0, glob_y_rot=0, glob_z_rot=0;


void Initialize ( )
{
    driver=new CDriverWin("first demo!!", true, RESOLUTION_W, RESOLUTION_H);

	glClearColor(0, 0, 0, 1.0f);
	glClearDepth (1.0f);
	glDepthFunc (GL_LEQUAL);
	glEnable (GL_DEPTH_TEST);
	glShadeModel (GL_FLAT);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);

	scene_0=new Scene_0;
	scene0=new Scene0;
	scene1=new Scene1;
	scene2=new Scene2;
	scene3=new Scene3;
	scene4=new Scene4;
	scene5=new Scene5;
	scene6=new Scene6;
	scene7=new Scene7;
	scene_1=new Scene_1;
}


void Draw (void)
{
	if (musicstart==false)
	{
		Music_Start();
		musicstart=true;
	}

	glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    if (time_line<9000) scene_0->Draw();
    else if (time_line<25000) scene0->Draw();
    else if (time_line<38000) scene1->Draw();
    else if (time_line<50000) scene2->Draw();
    else if (time_line<55000) scene3->Draw();
    else if (time_line<85000) scene4->Draw();
    else if (time_line<92000) scene5->Draw();
    else if (time_line<114000) scene6->Draw();
    else if (time_line<126000) scene7->Draw();
    else if (time_line<138000) scene_1->Draw();
    else 
	{
		FMUSIC_StopSong(mod);
		FMUSIC_FreeSong(mod);
		driver->halt();
	}

	glFlush ();
}


void Update (double misc)
{
    time_line+=misc;
    if (time_line<9000) scene_0->Update(misc);
    else if (time_line<25000) scene0->Update(misc);
    else if (time_line<38000) scene1->Update(misc);
    else if (time_line<50000) scene2->Update(misc);
    else if (time_line<55000) scene3->Update(misc);
    else if (time_line<85000) scene4->Update(misc);
    else if (time_line<92000) scene5->Update(misc);
    else if (time_line<114000) scene6->Update(misc);
    else if (time_line<126000) scene7->Update(misc);
    else if (time_line<138000) scene_1->Update(misc);
    else driver->halt();
}


//int main ()

int WINAPI WinMain(	HINSTANCE	hInstance,			// Instance
					HINSTANCE	hPrevInstance,		// Previous Instance
					LPSTR		lpCmdLine,			// Command Line Parameters
					int			nCmdShow)			// Window Show State
{
    Initialize();
    driver->SetFuncUpdate(Update);
    driver->SetFuncDraw(Draw);
    driver->run();

	return 0;
}
