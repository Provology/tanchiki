#ifndef VERTICES_MODULE_H
#define VERTICES_MODULE_H

#include <glad/glad.h>
// #include <string.h>
// #include <stdio.h>

typedef struct s_vbuff
{
    unsigned int VBO;
    unsigned int VAO;
    unsigned int EBO;
} t_vbuff;


void initRenderData(t_vbuff *vbuff);
// void vertices_buffer(t_vbuff *vbuff);

#endif // VERTICES_MODULE_H


