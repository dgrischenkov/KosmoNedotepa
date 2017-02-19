
#ifndef _CFONTTTF_H_
#define _CFONTTTF_H_

#include <string>
#include <GL/gl.h>
#include <ft2build.h>
#include FT_FREETYPE_H

#define CHARSET_KEY 912
#define CHARSET_MAP 912

class CFontTTF
{
	GLuint m_textures[256];
	GLuint m_list_base;

	GLuint m_height;

	GLvoid GenError(char *message);
	GLuint NextP2 (GLuint a);
	GLvoid GenGlyph(FT_Face face, GLubyte ch);

	GLvoid StartDraw(GLfloat zoom);
	GLvoid EndDraw( );

public:
	CFontTTF(char *filename, GLuint height=20);
	~CFontTTF();

	GLvoid OutLine(wchar_t *str,
		GLfloat pos_x, GLfloat pos_y,
		GLfloat zoom=0, GLfloat rt_grad=0);
};


#endif

/* TODO
Системные шрифты, что б не зависили от конретного дистриба линуха
*/
