
#include "CFontTTF.h"

// узнать число, кратное 2 и не меньше a,
// нужно для вычисления размера текстуры
GLuint CFontTTF::NextP2 (GLuint a)
{
	GLuint rval=1;
	while(rval<a) rval<<=1;
	return rval;
}


GLvoid CFontTTF::GenError(char *message)
{
	printf("--> error in CFontTTF in: \"%s\"\n", message);
	exit(1);
}


GLvoid CFontTTF::GenGlyph(FT_Face face, GLubyte ch)
{
	if (FT_Load_Char(face, (ch<=127) ? ch : ch+CHARSET_MAP,
						FT_LOAD_RENDER | FT_LOAD_TARGET_LIGHT))
		GenError("in render glyph");

	GLint gly_width = face->glyph->bitmap.width;
	GLint gly_height = face->glyph->bitmap.rows;
	GLint gly_top = face->glyph->bitmap_top;
	GLint gly_left = face->glyph->bitmap_left;

	GLint tex_width = NextP2(gly_width);
	GLint tex_height = NextP2(gly_height);

	GLubyte *gdata = new GLubyte[2 * tex_width * tex_height];

    // копирование пиксилей глифа из face в gdata
    // с преобразованием в формат хранения текстуры gl
	for(GLint j=0; j<tex_height;j++)
		for(GLint i=0; i<tex_width; i++)
			gdata[2*(i+j*tex_width)]=gdata[2*(i+j*tex_width)+1] =
				(i>=gly_width || j>=gly_height) ? 0 :
				face->glyph->bitmap.buffer[i+face->glyph->bitmap.width*j];

	glBindTexture(GL_TEXTURE_2D, m_textures[ch]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, tex_width, tex_height,
				0, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, gdata);

	delete [] gdata;

	glNewList(m_list_base+ch, GL_COMPILE);
		glBindTexture(GL_TEXTURE_2D, m_textures[ch]);
		GLdouble x=(GLdouble)gly_width / (GLdouble)tex_width;
		GLdouble y=(GLdouble)gly_height / (GLdouble)tex_height;

		glPushMatrix( );
		glTranslatef(0, gly_top-gly_height, 0);
		glBegin(GL_QUADS);
			glTexCoord2d(0,0); glVertex2f(0, gly_height);
			glTexCoord2d(0,y); glVertex2f(0, 0);
			glTexCoord2d(x,y); glVertex2f(gly_width, 0);
			glTexCoord2d(x,0); glVertex2f(gly_width, gly_height);
		glEnd();
		glPopMatrix( );

		if (ch==' ') glTranslatef(m_height/2, 0, 0);
		else glTranslatef(gly_width+gly_left, 0, 0);
	glEndList();
}


GLvoid CFontTTF::StartDraw(GLfloat zoom)
{
	glPushAttrib(GL_COLOR_BUFFER_BIT | GL_ENABLE_BIT);
		glDisable(GL_LIGHTING);
		glDisable(GL_DEPTH_TEST);
		glEnable(GL_TEXTURE_2D);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE);

	glMatrixMode(GL_PROJECTION);
		glPushMatrix( );
		glLoadIdentity();
		glOrtho(0, 8*(100-zoom), 0, 6*(100-zoom), -1, 1);

	glMatrixMode(GL_MODELVIEW);
		glPushMatrix( );
		glLoadIdentity();
}


GLvoid CFontTTF::EndDraw( )
{
	glPopAttrib( );

	glMatrixMode(GL_PROJECTION);
		glPopMatrix( );

	glMatrixMode(GL_MODELVIEW);
		glPopMatrix( );
}


/****************************************************************************
******************************** Publuc *************************************
****************************************************************************/

CFontTTF::CFontTTF(char *filename, GLuint height)
{
	m_height=height;

	FT_Library library;	FT_Face face;
	if (FT_Init_FreeType(&library))	GenError("init library");
	if (FT_New_Face(library, filename, 0, &face)) {
		char mess[80];
		strcpy(mess, "load font ");
		if (strlen(filename)<60) strcat(mess, filename);
		GenError(mess);
	}
	FT_Set_Char_Size(face, 0, height << 6, 0, 120);

	glGenTextures(256, m_textures);
	m_list_base=glGenLists(256);

	for(GLubyte ch=0; ch<255; ch++) GenGlyph(face, ch);

	FT_Done_Face(face);
	FT_Done_FreeType(library);
}


CFontTTF::~CFontTTF( )
{
	glDeleteLists(m_list_base, 256);
	glDeleteTextures(256, m_textures);
}


GLvoid CFontTTF::OutLine(wchar_t *str,
						GLfloat pos_x, GLfloat pos_y,
						GLfloat zoom, GLfloat rt_grad)
{
	StartDraw(zoom);
	glTranslatef(pos_x, pos_y, 0);
	glRotatef(rt_grad, 0, 0, 1);
	for (unsigned int i=0; i<wcslen(str); i++)
		glCallList(m_list_base + ((str[i]<=127) ? str[i] : str[i]-CHARSET_KEY));
	// 'А(=1040,rus)'-128=912
	EndDraw( );
}
