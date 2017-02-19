#ifndef CFONTTGA_H_INCLUDED
#define CFONTTGA_H_INCLUDED

#include "CTexture.h"


class CFontTGA
{
    GLuint m_base;
    CTexture *m_tex;

    char *m_text;
    int m_x, m_y;
    double m_scale;
    double m_speed_gliph, m_a_speed_gliph; // скорость печати по буквам,
    // если 0 - печатаються все буквы сразу, a_ - аккамулятор времени
    unsigned int m_cur_visible_gliph; // количество уже нарисованных глифов

    double m_r, m_g, m_b, m_a;

public:
    CFontTGA(const char *filename);
    ~CFontTGA();

    void SetText(const char *text);
    void SetXYScale(int x, int y, double scale);
    void SetSpeedGliph(double speed_gliph);
    void SetRGBA(double r, double g, double b, double a);

    void Draw();
    void Update(double misc);

};


#endif // CFONTTGA_H_INCLUDED
