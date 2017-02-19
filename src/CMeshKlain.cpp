
#include "CMeshKlain.h"


CMeshKlain::CMeshKlain(GLuint num_u, GLuint num_v,
	GLuint type, GLfloat radius, GLfloat scale, GLboolean eff_prodol)
{
    eff0_start=false;
    eff1_start=false;
    eff0_var0=0;
    eff1_var0=0;

    m_tex=0;
	m_type=type;
	m_num_v=num_v;
	m_num_u=num_u;
	m_radius=radius;
	m_scale=scale;

    m_ltype=GL_QUAD_STRIP;

	// schitaem shag
	GLdouble step_u=2.0f*(GLdouble)M_PI/(GLdouble)num_u;
	GLdouble step_v;

	if (type==KLAIN_LISTOK)
		step_v=2.0f/(GLdouble)num_v;
	else step_v=2.0f*M_PI/num_v;

//	num_u++; num_v++; // magic worlds.. :)


	// dlja indexachii massivov i forov
	GLuint i;


	// alloc mesh
	m_num_vertexes=num_u*num_v+num_v;
	m_mesh = new GLdouble *[m_num_vertexes];
	m_mesh_colors_cur = new GLfloat *[m_num_vertexes];
	for(i=0; i<m_num_vertexes; i++){
		m_mesh[i] = new GLdouble[3];
		m_mesh[i][0]=0;
		m_mesh[i][1]=0;
		m_mesh[i][2]=0;
		m_mesh_colors_cur[i] = new GLfloat[4];
		m_mesh_colors_cur[i][0]=0;
		m_mesh_colors_cur[i][1]=0;
		m_mesh_colors_cur[i][2]=0;
		m_mesh_colors_cur[i][3]=0;
	}


	// schitaem koordinati vsex tochek mesha
	GLuint cur_num_u;
	GLuint cur_num_v;
	GLdouble cur_u;
	GLdouble cur_v;

	GLuint i_count=m_num_v;
	GLuint i_base=0;


	if (!eff_prodol)
	{
		for (i=0, cur_num_u=0, cur_u=0.0f; cur_num_u<num_u;
				cur_u+=step_u, cur_num_u++, cur_num_v=0)
		{
			for (cur_num_v=0, cur_v=-1.0f; cur_num_v<num_v;
					cur_v+=step_v, cur_num_v++, i++)
			{
				if (type==KLAIN_LISTOK)
				{
					m_mesh[i][0] = (radius + (cur_v/2.0f) * cos(cur_u/2.0f)) * cos(cur_u);
					m_mesh[i][1] = (radius + (cur_v/2.0f) * cos(cur_u/2.0f)) * sin(cur_u);
					m_mesh[i][2] = (cur_v/2.0f) * sin(cur_u/2.0f);
				}
				else if (type==KLAIN_BUTILKA)
				{
					if (cur_u < M_PI) {
						m_mesh[i][0] = 6*cos(cur_u)*(1+sin(cur_u))+4*radius*(1-cos(cur_u)/2)*cos(cur_u)*cos(cur_v);
						m_mesh[i][1] = 16*sin(cur_u)+4*radius*(1-cos(cur_u)/2)*sin(cur_u)*cos(cur_v);
						m_mesh[i][2] = 4*radius*(1-cos(cur_u)/2)*sin(cur_v);
					} else {
						cur_v-=step_v*5.5f;

						if (i_count==m_num_v){
							i_count=0;
							i_base=i;
						}
						i_count++;

						m_mesh[i_base+m_num_v-i_count][0] = 6*cos(cur_u)*(1+sin(cur_u))+4*radius*(1-cos(cur_u)/2)*cos(cur_v);
						m_mesh[i_base+m_num_v-i_count][1] = 16*sin(cur_u);
						m_mesh[i_base+m_num_v-i_count][2] = 4*radius*(1-cos(cur_u)/2)*sin(cur_v);

						cur_v+=step_v*5.5f;
					}
				}
				else if (type==KLAIN_VOSMERKA)
				{
					m_mesh[i][0] = (radius + cos(cur_u/2)*sin(cur_v) - sin(cur_u/2)*sin(2*cur_v)) * cos(cur_u);
					m_mesh[i][1] = (radius + cos(cur_u/2)*sin(cur_v) - sin(cur_u/2)*sin(2*cur_v)) * sin(cur_u);
					m_mesh[i][2] = sin(cur_u/2)*sin(cur_v) + cos(cur_u/2)*sin(2*cur_v);
				} else {
					printf("--> error in init CMeshKlain - wrong type\n");
					exit(1);
				}
			}
		}
	} else {
		for (i=0, cur_num_v=0, cur_v=-1.0f; cur_num_v<num_v;
				cur_v+=step_v, cur_num_v++)
		{
			for (cur_num_u=0, cur_u=0.0f; cur_num_u<num_u;
					cur_u+=step_u, cur_num_u++, i++)
			{
				m_mesh[i][0] = (radius + cos(cur_u/2)*sin(cur_v) - sin(cur_u/2)*sin(2*cur_v)) * cos(cur_u);
				m_mesh[i][1] = (radius + cos(cur_u/2)*sin(cur_v) - sin(cur_u/2)*sin(2*cur_v)) * sin(cur_u);
				m_mesh[i][2] = sin(cur_u/2)*sin(cur_v) + cos(cur_u/2)*sin(2*cur_v);
			}
		}
	}


	// init color array
	for (i=0; i<m_num_vertexes-m_num_v; i++)
	{
		m_mesh_colors_cur[i][0]=KLAIN_DEF_COL1;
		m_mesh_colors_cur[i][1]=KLAIN_DEF_COL2;
		m_mesh_colors_cur[i][2]=KLAIN_DEF_COL3;
		m_mesh_colors_cur[i][3]=KLAIN_DEF_COL4;
	}


	// soedinjaem pervii i poslednii rjad
	if (type==KLAIN_LISTOK) {
		for (i=0; i<m_num_vertexes-num_v*3; i++)
		{
			m_mesh[i]=m_mesh[i+num_v*3];
		}
        m_num_vertexes-=num_v*3*2;

	} else if (type==KLAIN_BUTILKA)
		for (i=0; i<num_v; i++)
		{
			m_mesh[(m_num_vertexes)-(num_v-i)][0] = m_mesh[i][0];
			m_mesh[(m_num_vertexes)-(num_v-i)][1] = m_mesh[i][1];
			m_mesh[(m_num_vertexes)-(num_v-i)][2] = m_mesh[i][2];
		}
	else if (type==KLAIN_VOSMERKA)
        for (i=0; i<m_num_v; i++)
        {
            if (i<m_num_v/3+1)
            {
                m_mesh[m_num_vertexes-m_num_v+i][0]=m_mesh[m_num_v/3-i][0];
                m_mesh[m_num_vertexes-m_num_v+i][1]=m_mesh[m_num_v/3-i][1];
                m_mesh[m_num_vertexes-m_num_v+i][2]=m_mesh[m_num_v/3-i][2];
            } else {
                m_mesh[m_num_vertexes-m_num_v+i][0]=m_mesh[m_num_v*4/3-i][0];
                m_mesh[m_num_vertexes-m_num_v+i][1]=m_mesh[m_num_v*4/3-i][1];
                m_mesh[m_num_vertexes-m_num_v+i][2]=m_mesh[m_num_v*4/3-i][2];
            }
        }

}


CMeshKlain::~CMeshKlain( )
{
	for(GLuint i=0; i<m_num_vertexes; i++){
		delete [] m_mesh[i];
	}

	delete [] m_mesh;
}


GLvoid CMeshKlain::Draw( )
{
    if (eff1_start)
    {
        GLuint vertex_end;
        if (eff1_var0<(m_num_vertexes-m_num_v)) vertex_end=(int)eff1_var0;
        else vertex_end=m_num_vertexes-m_num_v;

        drawPart(0, vertex_end, m_ltype);

    } else if (eff0_start) {
        GLuint vertex_start0, vertex_end0, vertex_start1, vertex_end1;
        vertex_end0=(int)eff0_var0%(m_num_vertexes-m_num_v);

        if (vertex_end0>m_num_v*m_num_v/6){
            vertex_start0=vertex_end0-m_num_v*m_num_v/6;
            vertex_start1=0;
            vertex_end1=0;
        } else {
            vertex_start0=0;
            vertex_start1=m_num_vertexes-m_num_v*m_num_v/6+2+vertex_end0-m_num_v;
            vertex_end1=m_num_vertexes-m_num_v-1;
        }

        drawPart(vertex_start0, vertex_end0, m_ltype);
        drawPart(vertex_start1, vertex_end1, m_ltype);

    } else drawPart(0, m_num_vertexes-m_num_v, m_ltype);

}


GLvoid CMeshKlain::Update(GLdouble dtime)
{
    if (eff0_start) eff0_var0+=dtime*1.2f;
    if (eff1_start) eff1_var0+=dtime/35;
}


GLvoid CMeshKlain::SetColorCos( )
{
	for (GLuint i=0; i<m_num_vertexes-m_num_v; i++)
	{
		m_mesh_colors_cur[i][0]=cos(m_mesh[i][0])*0.5f-pow(cos(m_mesh[i][0]), 3)/10;
		m_mesh_colors_cur[i][1]=cos(m_mesh[i][1])*0.5f-pow(cos(m_mesh[i][1]), 3)/10;
		m_mesh_colors_cur[i][2]=cos(m_mesh[i][2])*0.7f-pow(cos(m_mesh[i][2]), 3)/10;
		m_mesh_colors_cur[i][3]=1.0f;
	}

	if (m_type==KLAIN_VOSMERKA)
	{
        for (GLuint i=0; i<m_num_v; i++)
        {
            if (i<m_num_v/3+1)
            {
                m_mesh_colors_cur[m_num_vertexes-m_num_v+i][0]=m_mesh_colors_cur[m_num_v/3-i][0];
                m_mesh_colors_cur[m_num_vertexes-m_num_v+i][1]=m_mesh_colors_cur[m_num_v/3-i][1];
                m_mesh_colors_cur[m_num_vertexes-m_num_v+i][2]=m_mesh_colors_cur[m_num_v/3-i][2];
                m_mesh_colors_cur[m_num_vertexes-m_num_v+i][3]=m_mesh_colors_cur[m_num_v/3-i][3];
            } else {
                m_mesh_colors_cur[m_num_vertexes-m_num_v+i][0]=m_mesh_colors_cur[m_num_v*4/3-i][0];
                m_mesh_colors_cur[m_num_vertexes-m_num_v+i][1]=m_mesh_colors_cur[m_num_v*4/3-i][1];
                m_mesh_colors_cur[m_num_vertexes-m_num_v+i][2]=m_mesh_colors_cur[m_num_v*4/3-i][2];
                m_mesh_colors_cur[m_num_vertexes-m_num_v+i][3]=m_mesh_colors_cur[m_num_v*4/3-i][3];
            }
        }
	} else if (m_type==KLAIN_LISTOK) {
        for (GLuint i=0; i<m_num_v; i++)
        {
            m_mesh_colors_cur[m_num_vertexes-m_num_v+i][0]=0;
            m_mesh_colors_cur[m_num_vertexes-m_num_v+i][1]=0;
            m_mesh_colors_cur[m_num_vertexes-m_num_v+i][2]=0;
            m_mesh_colors_cur[m_num_vertexes-m_num_v+i][3]=0;
        }
	}
}


GLvoid CMeshKlain::StartEff0( )
{
    eff0_start=true;
}


GLvoid CMeshKlain::StartEff1( )
{
    eff1_start=true;
}


GLvoid CMeshKlain::SetTexture(GLuint tex)
{
    m_tex=tex;
}


GLvoid CMeshKlain::SetLineType(GLenum ltype)
{
    m_ltype=ltype;
}


GLvoid CMeshKlain::drawPart(unsigned int start, unsigned int end, GLenum mode)
{
    if (m_tex) {
        glBindTexture(GL_TEXTURE_2D, m_tex);
        glEnable(GL_TEXTURE_2D);
    }

    glBegin(mode);
    for (GLuint i=start; i+1<=end; i++)
    {

        if (!(i%m_num_v) && i)
        {
            if (m_type!=KLAIN_LISTOK)
            {
                if (m_tex)
                {
                    if ((int)i%2) glTexCoord2d(0,0);
                    else glTexCoord2d(1,0);
                }

                glColor4f(	m_mesh_colors_cur[i-m_num_v][0],
                            m_mesh_colors_cur[i-m_num_v][1],
                            m_mesh_colors_cur[i-m_num_v][2],
                            m_mesh_colors_cur[i-m_num_v][3]);
                glVertex4f(	m_mesh[i-m_num_v][0],
                            m_mesh[i-m_num_v][1],
                            m_mesh[i-m_num_v][2], m_scale);

                if (m_tex)
                {
                    if ((int)i%2) glTexCoord2d(0,1);
                    else glTexCoord2d(1,1);
                }

                glColor4f(	m_mesh_colors_cur[i][0],
                            m_mesh_colors_cur[i][1],
                            m_mesh_colors_cur[i][2],
                            m_mesh_colors_cur[i][3]);
                glVertex4f(	m_mesh[i][0],
                            m_mesh[i][1],
                            m_mesh[i][2], m_scale);
            }
            glEnd();
            glBegin(mode);
        }

        if (m_tex)
        {
            if ((int)i%2) glTexCoord2d(0,0);
            else glTexCoord2d(1,0);
        }

        glColor4f(	m_mesh_colors_cur[i][0],
                    m_mesh_colors_cur[i][1],
                    m_mesh_colors_cur[i][2],
                    m_mesh_colors_cur[i][3]);
        glVertex4f(	m_mesh[i][0],
                    m_mesh[i][1],
                    m_mesh[i][2], m_scale);

        if (m_tex)
        {
            if ((int)i%2) glTexCoord2d(0,1);
            else glTexCoord2d(1,1);
        }

        glColor4f(	m_mesh_colors_cur[i+m_num_v][0],
                    m_mesh_colors_cur[i+m_num_v][1],
                    m_mesh_colors_cur[i+m_num_v][2],
                    m_mesh_colors_cur[i+m_num_v][3]);
        glVertex4f(	m_mesh[i+m_num_v][0],
                    m_mesh[i+m_num_v][1],
                    m_mesh[i+m_num_v][2], m_scale);
    }
    glEnd();

    if (m_tex) glDisable(GL_TEXTURE_2D);
}
