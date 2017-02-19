
#include "CHeightMap.h"


CHeightMap::CHeightMap(const char *filename)
{
    m_map_data=0;
    m_map_size=0;
    m_texture=0;
    m_scale_x=0;
    m_scale_y=0;
    m_scale_z=0;

	HMODULE hMod=GetModuleHandle(NULL);
    HRSRC hRes=FindResource(hMod,filename,"RAW");
    HGLOBAL hGlob=LoadResource(hMod,hRes);
    unsigned char *file_data=(unsigned char *)LockResource(hGlob);
	long file_size=SizeofResource(hMod,hRes);

    m_map_data=file_data;
    m_map_size=(int)sqrt((double)file_size);
    m_scale_x=1.0f;
    m_scale_y=1.0f;
    m_scale_z=1.0f;
}


CHeightMap::~CHeightMap()
{
    delete [] m_map_data;
}


void CHeightMap::SetTexture(GLuint texture)
{
    m_texture=texture;
}


void CHeightMap::SetScale(double x, double y, double z)
{
    m_scale_x=x;
    m_scale_y=y;
    m_scale_z=z;
}


void CHeightMap::Draw()
{
	double X, Y=0;
    double tmp, r, g, b;

	for (Y = 0; Y < m_map_size-1; Y++){
	    if (m_texture)
	    {
            glEnable(GL_TEXTURE_2D);
            glBindTexture(GL_TEXTURE_2D, m_texture);
	    }

        glBegin(GL_QUAD_STRIP);
        for (X = 0; X < m_map_size; X++){
            tmp=m_map_data[(int)(X*m_map_size+Y)]/255.0f;

            if (m_texture)
            {
                if ((int)X%2) glTexCoord2d(0,0);
                else glTexCoord2d(1,0);
            }

            r=tmp-pow(tmp, 3); b=tmp-pow(tmp, 3); g=tmp;
            glColor3f(r, g, b);

			glVertex3f(X*m_scale_x, Y*m_scale_y, tmp*m_scale_z);

            tmp=m_map_data[(int)(X*m_map_size+Y+1)]/255.0f;

            if (m_texture)
            {
                if ((int)X%2) glTexCoord2d(0,1);
                else glTexCoord2d(1,1);
            }

            r=tmp-pow(tmp, 3); b=tmp-pow(tmp, 3); g=tmp;
            glColor3f(r, g, b);

			glVertex3f(X*m_scale_x, Y*m_scale_y+1*m_scale_y, tmp*m_scale_z);
		}
        glEnd();

	    if (m_texture) glDisable(GL_TEXTURE_2D);
	}
}


void CHeightMap::Update(double misc)
{


}
