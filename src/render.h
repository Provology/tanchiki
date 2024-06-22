#ifndef RENDER_H
#define RENDER_H

#include"vertices.h"

typedef struct s_tile 
{
    float pos[3];
//    float size[3] = {80.0f, 60.0f, 1.0};
    float angle;
    float color[3]; 
} t_tile;


void DrawSprite(unsigned int shaderProgram_tex, t_vbuff *vbuff, int texture, float position[3], float size[3], float angle, float color[3], unsigned int width, unsigned int height);

#endif // RENDER_H


