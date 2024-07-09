#ifndef RENDER_H
#define RENDER_H

#include"vertices.h"

typedef struct s_tile 
{
    float timeStep;
    float animStep;
    int tex;
    int tex_index;
    signed int velocity[2];
    float pos[3];
//    float size[3] = {80.0f, 60.0f, 1.0};
    float angle;
    float color[3];
    unsigned int texture[10]; //TODO animations of explosion, idle, all directions
    int stop[4];
} t_tile;


void DrawSprite(unsigned int shaderProgram_tex, t_vbuff *vbuff, int texture, float position[3], float size[3], float angle, float color[3]);
void create_ortho_proj(float left, float right, float bottom, float top);

#endif // RENDER_H


