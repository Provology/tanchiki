#ifndef CREATE_WINDOW_H 
#define CREATE_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
// #include <string.h>
#include <stdio.h>

int glfw_window(GLFWwindow **window, int src_width, int src_height);
void glfw_init(void);

#endif // CREATE_WINDOW_H


