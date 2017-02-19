
#include "CRenderErr.h"

CRenderErr::CRenderErr()
{
	glGenTextures(1, &m_tex);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	m_frustum=1.0f;
	m_r=1.0f; m_g=1.0f; m_b=1.0f; m_a=1.0f;
	m_zoom=1.0f;
}


CRenderErr::~CRenderErr()
{

}


void CRenderErr::Begin()
{
	glMatrixMode(GL_PROJECTION);
		glPushMatrix( );
        glViewport(0, 0, 512, 512);
		glLoadIdentity();
		float width = 0.5f;
		float height = 0.5f * ((float)RESOLUTION_H/(float)RESOLUTION_W);
		glFrustum(-width, width, -height, height, m_frustum, 2000.0f);

	glMatrixMode(GL_MODELVIEW);
        glViewport(0, 0, 512, 512);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void CRenderErr::End()
{
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glCopyTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 0, 0, 512, 512, 0);

	glMatrixMode(GL_PROJECTION);
		glPopMatrix( );

	glMatrixMode(GL_MODELVIEW);
		glPopMatrix( );

	glViewport(0, 0, RESOLUTION_W, RESOLUTION_H);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void CRenderErr::Draw()
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
		glOrtho(0, RESOLUTION_W, 0, RESOLUTION_H, -1, 1);

	glMatrixMode(GL_MODELVIEW);
		glPushMatrix( );
		glLoadIdentity();

	glBindTexture(GL_TEXTURE_2D, m_tex);

    glBegin(GL_QUADS);
        glColor4f(m_r, m_g, m_b, m_a);
        glTexCoord2d(1-m_zoom, m_zoom); glVertex2f(0, RESOLUTION_H-RESOLUTION_H/8);
        glTexCoord2d(1-m_zoom, 1-m_zoom); glVertex2f(0, RESOLUTION_H/6);
        glTexCoord2d(m_zoom, 1-m_zoom); glVertex2f(RESOLUTION_W, RESOLUTION_H/6);
        glTexCoord2d(m_zoom, m_zoom); glVertex2f(RESOLUTION_W, RESOLUTION_H-RESOLUTION_H/8);
    glEnd();

	glPopAttrib( );

	glMatrixMode(GL_PROJECTION);
		glPopMatrix( );

	glMatrixMode(GL_MODELVIEW);
		glPopMatrix( );
}


void CRenderErr::Update(double misc)
{

}


void CRenderErr::SetFrustum(double frustum)
{
    m_frustum=frustum;
}


void CRenderErr::SetRGBA(double r, double g, double b, double a)
{
    m_r=r;
    m_g=g;
    m_b=b;
    m_a=a;
}


void CRenderErr::SetZoom(double zoom)
{
    m_zoom=zoom;
}
