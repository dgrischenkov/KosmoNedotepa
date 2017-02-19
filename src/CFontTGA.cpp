
#include "CFontTGA.h"

CFontTGA::CFontTGA(const char *filename)
{
    m_tex=new CTexture(filename);

    m_text=new char[80];
    strcpy(m_text, "текст\0");

    m_x=20; m_y=20;
    m_scale=1.0f;
    m_speed_gliph=500.0f;
    m_a_speed_gliph=0.0f;
    m_cur_visible_gliph=0;

    m_r=1.0f;
    m_g=1.0f;
    m_b=1.0f;
    m_a=1.0f;

	m_base=glGenLists(256);
    glBindTexture(GL_TEXTURE_2D, m_tex->GetTexID());
	for (int loop1=0; loop1<255; loop1++)
	{
		float cx=float(loop1%16)/16.0f;
		float cy=float(loop1/16)/16.0f;

		glNewList(m_base+loop1,GL_COMPILE);
			glBegin(GL_QUADS);
				glTexCoord2f(cx,1.0f-cy-0.0625f);
				glVertex2d(0,16);
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.0625f);
				glVertex2i(16,16);
				glTexCoord2f(cx+0.0625f,1.0f-cy-0.001f);
				glVertex2i(16,0);
				glTexCoord2f(cx,1.0f-cy-0.001f);
				glVertex2i(0,0);
			glEnd();
			glTranslated(14,0,0);
		glEndList();
	}
}


CFontTGA::~CFontTGA()
{
    delete [] m_tex;
    delete [] m_text;
}


void CFontTGA::Draw()
{
	glPushAttrib(GL_POLYGON_BIT | GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);
		glPolygonMode(GL_FRONT, GL_FILL);

	glMatrixMode(GL_PROJECTION);
		glPushMatrix( );
		glLoadIdentity();
        glOrtho(0.0f,640,480,0.0f,-1.0f,1.0f);

	glMatrixMode(GL_MODELVIEW);
		glPushMatrix( );
		glLoadIdentity();

	glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, m_tex->GetTexID());
        glColor4f(m_r, m_g, m_b, m_a);
        glTranslated(m_x,m_y,0);

        glListBase(m_base);
        glScalef(m_scale*1.0f, m_scale*1.0f, m_scale*1.0f);

        if (!m_speed_gliph)
            glCallLists(strlen(m_text),GL_UNSIGNED_BYTE, m_text);
        else glCallLists(m_cur_visible_gliph,GL_UNSIGNED_BYTE, m_text);

	glDisable(GL_TEXTURE_2D);

	glPopAttrib( );

	glMatrixMode(GL_PROJECTION);
		glPopMatrix( );

	glMatrixMode(GL_MODELVIEW);
		glPopMatrix( );
}


void CFontTGA::Update(double misc)
{
    if (m_speed_gliph)
    {
        m_a_speed_gliph+=misc;

        if (m_a_speed_gliph > m_speed_gliph)
        {
            m_a_speed_gliph=0;
            if (m_cur_visible_gliph<strlen(m_text))
                m_cur_visible_gliph++;
        }
    }
}


void CFontTGA::SetText(const char *text)
{
    delete [] m_text;
    m_text=new char [80];
    strcpy(m_text, text);
}


void CFontTGA::SetXYScale(int x, int y, double scale)
{
    m_x=x;
    m_y=y;
    m_scale=scale;
}


void CFontTGA::SetSpeedGliph(double speed_gliph)
{
    m_speed_gliph=speed_gliph;
}


void CFontTGA::SetRGBA(double r, double g, double b, double a)
{
    m_r=r;
    m_g=g;
    m_b=b;
    m_a=a;
}
