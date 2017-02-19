
#ifndef _CMESHKLAIN_H_
#define _CMESHKLAIN_H_

#include "main.h"
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define KLAIN_LISTOK	0
#define KLAIN_BUTILKA 	1
#define KLAIN_VOSMERKA	2
#define KLAIN_DEF_COL1	0.6f
#define KLAIN_DEF_COL2	0.8f
#define KLAIN_DEF_COL3	1.0f
#define KLAIN_DEF_COL4	1.0f
#define M_PI 3.14


class CMeshKlain
{
	GLdouble **m_mesh;
	GLuint m_num_vertexes;
	GLuint m_tex;

	GLfloat m_radius; // ������ �������
	GLuint m_num_v; // ���������� ���������� ������
	GLuint m_num_u; // ���������� ���������� ������
	GLuint m_type; // ��� �������
	GLfloat m_scale; // ����������

	GLfloat **m_mesh_colors_cur; // ������� ����� ����� �������

    GLboolean eff0_start; // ������� ��� ��� ������ ����� 0
    GLboolean eff1_start;
    GLfloat eff0_var0; // ���������� ����� 0 ��� ������� ����� 0
    GLfloat eff1_var0;

    GLenum m_ltype;

    GLvoid drawPart(unsigned int start, unsigned int end, GLenum mode);

public:
	~CMeshKlain( );

	CMeshKlain(GLuint num_u=40, GLuint num_v=40,
			GLuint type=KLAIN_LISTOK, GLfloat radius=1.0f, GLfloat scale=1.0f, GLboolean eff_prodol=false);

	GLvoid Draw( );
	GLvoid Update(GLdouble dtime);

	GLvoid SetColorCos( );

	GLvoid StartEff0(); // ��������� ������ ������
	GLvoid StartEff1();

	GLvoid SetLineType(GLenum ltype=GL_QUAD_STRIP);

	GLvoid SetTexture(GLuint tex);

};


#endif
