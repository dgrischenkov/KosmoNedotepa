#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

#include <windows.h>

#define RESOLUTION_W 800
#define RESOLUTION_H 600

extern double time_line;
extern double glob_x_pos, glob_y_pos, glob_z_pos;
extern double glob_x_rot, glob_y_rot, glob_z_rot;

//    gluLookAt(glob_x_pos, glob_y_pos, glob_z_pos,
//        glob_x_rot, glob_y_rot, glob_z_rot, 0, 0, 1);


#endif // MAIN_H_INCLUDED
