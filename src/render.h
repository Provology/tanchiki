#ifndef RENDER_H
#define RENDER_H

#include"vertices.h"


void DrawSprite(unsigned int shaderProgram_tex, t_vbuff *vbuff, int texture, float position[3], float size[3], float angle, float color[3]);
void create_ortho_proj(float left, float right, float bottom, float top);

#endif // RENDER_H


