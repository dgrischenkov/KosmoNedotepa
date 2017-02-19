
#include "CDriverWin.h"
#include "stdio.h"

CDriverWin *global_driver; // для работы с WndProc



// private

void CDriverWin::Draw( )
{
    if (m_Draw) {
        m_Draw();
        return;
    }

	glClearColor(0.5f, 0.5f, 0.7f, 0.5);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void CDriverWin::Update(double dtime)
{
    if (m_Update) {
        m_Update(dtime);
        return;
    }
}


void CDriverWin::Resize(unsigned int w, unsigned int h)
{
    if (m_Resize) {
        m_Resize(w, h);
        return;
    }

	glMatrixMode(GL_PROJECTION);
		glViewport(0, 0, w, h);
		glLoadIdentity();
		float width = 0.5f;
		float height = 0.5f * ((float)h/(float)w);
		glFrustum(-width, width, -height, height, 0.01f, 2000.0f);

	glMatrixMode(GL_MODELVIEW);
		glViewport(0, 0, w, h);
}


void printPos()
{
    printf("%f, %f, %f, %f, %f, %f\n", glob_x_pos, glob_y_pos, glob_z_pos, glob_x_rot, glob_y_rot, glob_z_rot);
}


void CDriverWin::EventKey(int key)
{
    double dpos=0.1;

    if (m_EventKey) {
        m_EventKey(key);
        return;
    }

	switch(key)
	{
		case VK_ESCAPE:
			halt();
			break;
        case VK_UP: glob_x_pos+=dpos;printPos();break;
        case VK_DOWN: glob_x_pos-=dpos;printPos();break;
        case VK_LEFT: glob_y_pos+=dpos;printPos();break;
        case VK_RIGHT: glob_y_pos-=dpos;printPos();break;
        case VK_F1: glob_z_pos+=dpos;printPos();break;
        case VK_F2: glob_z_pos-=dpos;printPos();break;
        case VK_F3: glob_x_rot+=dpos;printPos();break;
        case VK_F4: glob_x_rot-=dpos;printPos();break;
        case VK_F5: glob_y_rot+=dpos;printPos();break;
        case VK_F6: glob_y_rot-=dpos;printPos();break;
        case VK_F7: glob_z_rot+=dpos;printPos();break;
        case VK_F8: glob_z_rot-=dpos;printPos();break;
	}
}



// private static

LRESULT CALLBACK CDriverWin::WindowProc (HWND hWnd,
    UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
        case WM_CLOSE:
            global_driver->halt();
            break;

        case WM_SIZE:
            if (wParam==SIZE_MAXIMIZED || wParam==SIZE_RESTORED) {
                global_driver->mp_user_win.width = LOWORD (lParam);
                global_driver->mp_user_win.height = HIWORD (lParam);
                global_driver->Resize(LOWORD(lParam), HIWORD(lParam));
            }
            break;

        case WM_KEYDOWN:
            if ((wParam >= 0) && (wParam <= 255))
                global_driver->EventKey((int)(wParam));
            break;
    }
    return DefWindowProc (hWnd, uMsg, wParam, lParam);
}



// public

CDriverWin::CDriverWin(const char* title, bool fullscreen,
						int width, int height, int bpp)
{
	m_running=false;
	m_fps=0;
	m_current_time=0;

	m_Draw=0;
	m_Update=0;
	m_Resize=0;
	m_EventKey=0;

    mp_user_win.title=new char[strlen(title)];
    strcpy(mp_user_win.title, title);
    mp_user_win.x=0;
    mp_user_win.y=0;
    mp_user_win.width=width;
    mp_user_win.height=height;
    mp_user_win.bpp=bpp;
    mp_user_win.fullscreen=fullscreen;

    m_windows_win.className="OpenGL";
    m_windows_win.hInstance=GetModuleHandle(0);
    m_windows_win.hWnd=0;
    m_windows_win.hDC=0;
    m_windows_win.hRC=0;

    global_driver=this; // для работы с WndProc


    // Регистрация класса окна
	WNDCLASSEX windowClass;
	ZeroMemory (&windowClass, sizeof (WNDCLASSEX));
	windowClass.cbSize			= sizeof (WNDCLASSEX);
	windowClass.style			= CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	windowClass.lpfnWndProc 	= (WNDPROC)(this->WindowProc);
	windowClass.hInstance		= m_windows_win.hInstance;
	windowClass.hbrBackground	= (HBRUSH)(COLOR_APPWORKSPACE);
	windowClass.hCursor	        = LoadCursor(NULL, IDC_ARROW);
	windowClass.lpszClassName   = m_windows_win.className;

	if (RegisterClassEx (&windowClass) == 0)
	{
		MessageBox (HWND_DESKTOP, "RegisterClassEx Failed!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}


    // Инициализация временных переменных
	DWORD windowStyle = WS_OVERLAPPEDWINDOW;
	DWORD windowExtendedStyle = WS_EX_APPWINDOW;

	RECT windowRect =
	{
        mp_user_win.x,
        mp_user_win.y,
        mp_user_win.width,
        mp_user_win.height
    };

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof (PIXELFORMATDESCRIPTOR), // Size Of This Pixel Format Descriptor
		1,								// Version Number
		PFD_DRAW_TO_WINDOW |			// Format Must Support Window
		PFD_SUPPORT_OPENGL |			// Format Must Support OpenGL
		PFD_DOUBLEBUFFER,				// Must Support Double Buffering
		PFD_TYPE_RGBA,					// Request An RGBA Format
		mp_user_win.bpp,		// Select Our Color Depth
		0, 0, 0, 0, 0, 0,				// Color Bits Ignored
		0,								// No Alpha Buffer
		0,								// Shift Bit Ignored
		0,								// No Accumulation Buffer
		0, 0, 0, 0,						// Accumulation Bits Ignored
		16,								// 16Bit Z-Buffer (Depth Buffer)
		0,								// No Stencil Buffer
		0,								// No Auxiliary Buffer
		PFD_MAIN_PLANE,					// Main Drawing Layer
		0,								// Reserved
		0, 0, 0							// Layer Masks Ignored
	};


    // Установка полноэкранного режима
    if (mp_user_win.fullscreen)
    {
        DEVMODE dmScreenSettings;
        ZeroMemory (&dmScreenSettings, sizeof (DEVMODE));
        dmScreenSettings.dmSize				= sizeof (DEVMODE);
        dmScreenSettings.dmPelsWidth		= mp_user_win.width;
        dmScreenSettings.dmPelsHeight		= mp_user_win.height;
        dmScreenSettings.dmBitsPerPel		= mp_user_win.bpp;
        dmScreenSettings.dmFields			= DM_BITSPERPEL | DM_PELSWIDTH | DM_PELSHEIGHT;

        if (ChangeDisplaySettings (&dmScreenSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
        {
            MessageBox (HWND_DESKTOP, "Mode Switch Failed.\nRunning In Windowed Mode.", "Error", MB_OK | MB_ICONEXCLAMATION);
            mp_user_win.fullscreen=false;
        } else {
            ShowCursor (FALSE);
            windowStyle = WS_POPUP;
            windowExtendedStyle |= WS_EX_TOPMOST;
        }

    } else AdjustWindowRectEx (&windowRect, windowStyle, 0, windowExtendedStyle);


	// Создание окна
	m_windows_win.hWnd = CreateWindowEx ( windowExtendedStyle,  // Extended Style
                        m_windows_win.className,	            // Class Name
                        mp_user_win.title,			    // Window Title
                        windowStyle,							// Window Style
                        0, 0,								    // Window X,Y Position
                        windowRect.right - windowRect.left,	    // Window Width
                        windowRect.bottom - windowRect.top,	    // Window Height
                        HWND_DESKTOP,						    // Desktop Is Window's Parent
                        0,									    // No Menu
                        m_windows_win.hInstance, 0);            // Pass The Window Instance

	if (m_windows_win.hWnd == 0)
	{
		MessageBox (HWND_DESKTOP, "hWnd is NULL!", "Error", MB_OK | MB_ICONEXCLAMATION);
		return;
	}


    // Взятие контекста рисования
	m_windows_win.hDC = GetDC (m_windows_win.hWnd);
	if (m_windows_win.hDC == 0)
	{
		MessageBox (HWND_DESKTOP, "hDC is NULL!", "Error", MB_OK | MB_ICONEXCLAMATION);
		DestroyWindow (m_windows_win.hWnd);
		m_windows_win.hWnd = 0;
		return;
	}


    // Настройка пиксельформата
	GLuint PixelFormat = ChoosePixelFormat (m_windows_win.hDC, &pfd);
	if (PixelFormat == 0 || SetPixelFormat (m_windows_win.hDC, PixelFormat, &pfd) == FALSE)
	{
		MessageBox (HWND_DESKTOP, "SetPixelFormat error!", "Error", MB_OK | MB_ICONEXCLAMATION);
		ReleaseDC (m_windows_win.hWnd, m_windows_win.hDC);
		m_windows_win.hDC = 0;
		DestroyWindow (m_windows_win.hWnd);
		m_windows_win.hWnd = 0;
		return;
	}


    // Взятие контекста ресурса
	m_windows_win.hRC = wglCreateContext (m_windows_win.hDC);
	if (m_windows_win.hRC == 0 || wglMakeCurrent (m_windows_win.hDC, m_windows_win.hRC) == FALSE)
	{
		MessageBox (HWND_DESKTOP, "hRC error!", "Error", MB_OK | MB_ICONEXCLAMATION);
		wglDeleteContext (m_windows_win.hRC);
		m_windows_win.hRC = 0;
		ReleaseDC (m_windows_win.hWnd, m_windows_win.hDC);
		m_windows_win.hDC = 0;
		DestroyWindow (m_windows_win.hWnd);
		m_windows_win.hWnd = 0;
		return;
	}
}


CDriverWin::~CDriverWin( )
{

}


void CDriverWin::run( )
{
	m_running=true;
	m_fps=9999;
	MSG msg;
	DWORD old_current_time=0;
	DWORD old_current_secund=0;
	DWORD start_time=GetTickCount();
	long frames=0;

	ShowWindow (m_windows_win.hWnd, SW_NORMAL);
    Resize(mp_user_win.width, mp_user_win.height);

    while (m_running)
    {
        if (PeekMessage (&msg, m_windows_win.hWnd, 0, 0, PM_REMOVE) == 0)
        {
            m_current_time = GetTickCount() - start_time;
            Update((double)(m_current_time - old_current_time));
            old_current_time = m_current_time;

            if (m_current_time > old_current_secund+1000){
                m_fps=frames;
                frames=0;
                old_current_secund=m_current_time;
            }

            Draw( );
            SwapBuffers (m_windows_win.hDC);
            frames++;
        } else DispatchMessage (&msg);
    }
}


unsigned int CDriverWin::GetFPS( )
{
	return m_fps;
}


double CDriverWin::GetCurTime( )
{
	return m_current_time;
}


void CDriverWin::halt( )
{
	if (m_windows_win.hWnd != 0)
	{
		if (m_windows_win.hDC != 0)
		{
			wglMakeCurrent (m_windows_win.hDC, 0);
			if (m_windows_win.hRC != 0)
			{
				wglDeleteContext (m_windows_win.hRC);
				m_windows_win.hRC = 0;
			}
			ReleaseDC (m_windows_win.hWnd, m_windows_win.hDC);
			m_windows_win.hDC = 0;
		}
		DestroyWindow (m_windows_win.hWnd);
		m_windows_win.hWnd = 0;
	}

	if (mp_user_win.fullscreen)
	{
		ChangeDisplaySettings(NULL, 0);
		ShowCursor (TRUE);
	}

	UnregisterClass (m_windows_win.className, m_windows_win.hInstance);
	m_running = false;
}


void CDriverWin::SetFuncDraw(void (*func)( ))
{
	m_Draw = func;
}


void CDriverWin::SetFuncUpdate(void (*func)(double))
{
	m_Update = func;
}


void CDriverWin::SetFuncResize(void (*func)(unsigned int, unsigned int))
{
	m_Resize = func;
}


void CDriverWin::SetFuncEventKey(void (*func)(int))
{
	m_EventKey = func;
}
