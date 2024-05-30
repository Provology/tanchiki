#ifndef SHADER_MODULE_H
#define SHADER_MODULE_H

#include <glad/glad.h>
// #include <string.h>
// #include <stdio.h>

unsigned int ID;

unsigned int build_shader(const char *vertexPath, const char *fragmentPath);
// void use(void);

// void set_int(const char *name, int value);
// void set_float(const char *name, float value);


#endif // SHADER_MODULE_H