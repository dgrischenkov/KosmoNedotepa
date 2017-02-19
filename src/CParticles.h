#ifndef CPARTICLES_H_INCLUDED
#define CPARTICLES_H_INCLUDED

#include "main.h"
#include <stdlib.h>
#include "GL/gl.h"


class CParticles
{
    struct m_SParticles {
        float life;
        float fade;
        float x, y, z;
        float xi, yi, zi;
        float xg, yg, zg;
        float raz; // разброс в размере частицы,
        float araz; // аккамулятор миллисекунд, что
        // бы менять переменную raz спустя определённое время
    } *m_particle;

    int m_num_particles;

    float m_fade;
    float m_speed;
    float m_r, m_g, m_b;

    float m_xi, m_yi, m_zi;
    float m_xg, m_yg, m_zg;

    float m_razbros;
    float m_araz; // время в миллисекундах
    // спустя которое надо менять переменную raz

    float m_arazkof; // ограничитель минимального
    // размера частицы при разбросе размера.
    // 1 - самая маленькая частица разна нулю,
    // 2 - половине частицы,
    // 4 - трём четвёртым частицы и т.п.

    float m_scale; // изменение размера частицы

public:
    CParticles(int num_particles);
    ~CParticles();

    void SetFade(float fade);
    void SetSpeed(float speed);
    void SetRGB(float r, float g, float b);
    void SetDirection(float x, float y, float z);
    void SetGravity(float x, float y, float z);
    void SetRazbros(float razbros);
    void SetARaz(float araz);
    void SetARazkof(float arazkof);
    void SetScale(float scale);

    void Draw();
    void Update(double misc);

};


#endif // CPARTICLES_H_INCLUDED
