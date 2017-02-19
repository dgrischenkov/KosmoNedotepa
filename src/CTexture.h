#ifndef CTEXTURE_H_INCLUDED
#define CTEXTURE_H_INCLUDED

#include <stdio.h>
#include <windows.h>
#include "GL/gl.h"


class CTexture
{
	GLubyte	*m_imageData;
	GLuint	m_bpp;
	GLuint	m_width;
	GLuint	m_height;
	GLuint	m_texID;

public:
    CTexture(const char *filename);
    ~CTexture();

    GLuint GetTexID();

};


#endif // CTEXTURE_H_INCLUDED
