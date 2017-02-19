
#ifndef _CDRIVERWIN_H_
#define _CDRIVERWIN_H_

#include <windows.h>

#include <wchar.h> //!!
#include <gl\gl.h> //!!
#include <gl\glu.h> //!!
#include "main.h"


class CDriverWin
{
    struct {
        char* title;
        int x,y;
        unsigned int width, height;
        unsigned int bpp;
        bool fullscreen;
    } mp_user_win;

    struct {
        const char* className;
        HINSTANCE hInstance;
        HWND hWnd;
        HDC hDC;
        HGLRC hRC;
    } m_windows_win;

	bool m_running;
	unsigned int m_fps;
	DWORD m_current_time;

	void (*m_Draw)( );
	void (*m_Update)(double);
	void (*m_Resize)(unsigned int, unsigned int);
	void (*m_EventKey)(int);

	void Draw( );
	void Update(double dtime);
	void EventKey(int key);
	void Resize(unsigned int w, unsigned int h);

    static LRESULT CALLBACK WindowProc (HWND hWnd,
        UINT uMsg, WPARAM wParam, LPARAM lParam);

public:
	~CDriverWin( );

	CDriverWin(const char *title="simple demo", bool fullscreen=false,
		int width=640, int height=480, int bpp=32);

	unsigned int GetFPS( );
	double GetCurTime( );

	void SetFuncDraw(void (*func)( ));
	void SetFuncUpdate(void (*func)(double));
	void SetFuncResize(void (*func)(unsigned int, unsigned int));
	void SetFuncEventKey(void (*func)(int));

	void run( );
	void halt( );

};


#endif
