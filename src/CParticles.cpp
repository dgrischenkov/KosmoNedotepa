
#include "CParticles.h"
#include <stdio.h>

CParticles::CParticles(int num_particles)
{
    m_num_particles=num_particles;
    m_particle=new m_SParticles[num_particles];

    m_fade=0.04f;
    m_speed=0.015f;
    m_r=0.05f, m_g=0.75f, m_b=1.0f;

    m_xi=0.0f, m_yi=-1.0f, m_zi=0.0f;
    m_xg=0.0f, m_yg=0.0f, m_zg=0.05f;

    m_razbros=0.5f;
    m_araz=20;
    m_arazkof=1.5f;
    m_scale=1.0f;

	for (int loop=0; loop<m_num_particles; loop++)
        m_particle[loop].life=0.0f;

    Update(1.0f);
}


CParticles::~CParticles()
{
    delete [] m_particle;
}


void CParticles::Draw()
{
	glEnable(GL_BLEND);
	//glDisable(GL_DEPTH_TEST);

	for (int loop=0; loop<m_num_particles; loop++)
	{
        float x=m_particle[loop].x;
        float y=m_particle[loop].y;
        float z=m_particle[loop].z;
        float raz=m_particle[loop].raz;

        glColor4f(m_r, m_g, m_b, m_particle[loop].life);

        glBegin(GL_TRIANGLE_STRIP);
            glVertex4f(x+raz, y+raz, z+raz, m_scale);
            glVertex4f(x-raz, y+raz, z+raz, m_scale);
            glVertex4f(x+raz, y-raz, z+raz, m_scale);
            glVertex4f(x-raz, y-raz, z+raz, m_scale);
        glEnd();

        glBegin(GL_TRIANGLE_STRIP);
            glVertex4f(x+raz, y+raz, z-raz, m_scale);
            glVertex4f(x-raz, y+raz, z-raz, m_scale);
            glVertex4f(x+raz, y-raz, z-raz, m_scale);
            glVertex4f(x-raz, y-raz, z-raz, m_scale);
        glEnd();

        glBegin(GL_TRIANGLE_STRIP);
            glVertex4f(x+raz, y+raz, z-raz, m_scale);
            glVertex4f(x+raz, y+raz, z+raz, m_scale);
            glVertex4f(x+raz, y-raz, z-raz, m_scale);
            glVertex4f(x+raz, y-raz, z+raz, m_scale);
        glEnd();

        glBegin(GL_TRIANGLE_STRIP);
            glVertex4f(x-raz, y+raz, z-raz, m_scale);
            glVertex4f(x-raz, y+raz, z+raz, m_scale);
            glVertex4f(x-raz, y-raz, z-raz, m_scale);
            glVertex4f(x-raz, y-raz, z+raz, m_scale);
        glEnd();

        glBegin(GL_TRIANGLE_STRIP);
            glVertex4f(x+raz, y+raz, z+raz, m_scale);
            glVertex4f(x-raz, y+raz, z+raz, m_scale);
            glVertex4f(x+raz, y+raz, z-raz, m_scale);
            glVertex4f(x-raz, y+raz, z-raz, m_scale);
        glEnd();

        glBegin(GL_TRIANGLE_STRIP);
            glVertex4f(x+raz, y-raz, z+raz, m_scale);
            glVertex4f(x-raz, y-raz, z+raz, m_scale);
            glVertex4f(x+raz, y-raz, z-raz, m_scale);
            glVertex4f(x-raz, y-raz, z-raz, m_scale);
        glEnd();

    }

	//glEnable (GL_DEPTH_TEST);
	glDisable(GL_BLEND);
}


void CParticles::Update(double misc)
{
	for (int loop=0;loop<m_num_particles;loop++)
	{
        if (m_particle[loop].life<=0.0f)
        {
            m_particle[loop].life=1.0f;
            m_particle[loop].fade=m_fade*(rand()/(float)RAND_MAX)+m_fade;
            m_particle[loop].x=0.0f;
            m_particle[loop].y=0.0f;
            m_particle[loop].z=0.0f;
            m_particle[loop].xg=m_xg;
            m_particle[loop].yg=m_yg;
            m_particle[loop].zg=m_zg;
            m_particle[loop].xi=(m_razbros/2)-m_razbros*(rand()/(float)RAND_MAX)+m_xg+m_xi;
            m_particle[loop].yi=(m_razbros/2)-m_razbros*(rand()/(float)RAND_MAX)+m_yg+m_yi;
            m_particle[loop].zi=(m_razbros/2)-m_razbros*(rand()/(float)RAND_MAX)+m_zg+m_zi;
            m_particle[loop].raz=0.25f;
            m_particle[loop].araz=0;
            continue;
        }

        m_particle[loop].x+=misc*m_particle[loop].xi*m_speed;
        m_particle[loop].y+=misc*m_particle[loop].yi*m_speed;
        m_particle[loop].z+=misc*m_particle[loop].zi*m_speed;

        m_particle[loop].xi+=misc*m_particle[loop].xg*m_speed;
        m_particle[loop].yi+=misc*m_particle[loop].yg*m_speed;
        m_particle[loop].zi+=misc*m_particle[loop].zg*m_speed;
        m_particle[loop].life-=misc*m_particle[loop].fade*m_speed;

        m_particle[loop].araz+=misc;

        if (m_particle[loop].araz>m_araz)
        {
            m_particle[loop].araz=0;
            m_particle[loop].raz=0.25f+((m_razbros/2)-m_razbros*(rand()/(float)RAND_MAX))/m_arazkof;
        }

    }
}


void CParticles::SetFade(float fade)
{
    m_fade=fade;
}


void CParticles::SetSpeed(float speed)
{
    m_speed=speed;
}


void CParticles::SetRGB(float r, float g, float b)
{
    m_r=r; m_g=g; m_b=b;
}


void CParticles::SetDirection(float x, float y, float z)
{
    m_xi=x;
    m_yi=y;
    m_zi=z;
}


void CParticles::SetGravity(float x, float y, float z)
{
    m_xg=x;
    m_yg=y;
    m_zg=z;
}


void CParticles::SetRazbros(float razbros)
{
    m_razbros=razbros;
}


void CParticles::SetARaz(float araz)
{
    m_araz=araz;
}


void CParticles::SetARazkof(float arazkof)
{
    m_arazkof=arazkof;
}


void CParticles::SetScale(float scale)
{
    m_scale=scale;
}
