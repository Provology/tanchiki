#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include"shader_module.h"
#include"stb_image.h"
#include"texture_module.h"
#include"vertices.h"
#include"create_window.h"
#include"linear_algebra.h"
#include"transformations.h"


#define PATH_BANANA "/home/ruslan/Downloads/banana.png"

void processInput(GLFWwindow *window);

// images
const char *PATH_BC = "/home/ruslan/Downloads/battle_city.jpg";
// shaders
const char *SHADER_VERTEX = "/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/shader_matrix.vs"; 
const char *SHADER_FRAGMENT = "/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/shader_tex.fs";
// settings
float mixValue = 0.0f;
unsigned int shaderProgram_tex;//TODO create shader program object
unsigned int quadVAO;

// glfw: initialize and configure
// ------------------------------
void glfw_init(void)
{
   glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
}

int main()
{
    GLFWwindow *window = NULL;
    int error = 0;
    t_vbuff vbuff = {0};
    unsigned int texture1, texture2[3];

    glfw_init();
    error = glfw_window(&window);
    if(error < 0)
    {
        return(-1);
    }

    // build and compile our shader program
    // ------------------------------------
    shaderProgram_tex = build_shader(SHADER_VERTEX, SHADER_FRAGMENT);


    vertices_buffer(&vbuff);
    // load and create a texture 
    // -------------------------
//  texture_loader(&texture1, PATH_BANANA);
    texture_loader(texture2, PATH_BC);
    printf("%d, %d\n", texture2[0], texture2[1]);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(shaderProgram_tex);
    glUniform1i(glGetUniformLocation(shaderProgram_tex, "texture1"), 0);
    glUniform1i(glGetUniformLocation(shaderProgram_tex, "texture2"), 1);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // bind textures on corresponding texture units
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture1);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture2[1]);
//        glActiveTexture(GL_TEXTURE1);
//        glBindTexture(GL_TEXTURE_2D, texture2[0]);

//	glUniform1f(glGetUniformLocation(shaderProgram_tex, "mixValue"), mixValue);

        // create transformations
	float trans[4][4] = {0};
        // render container
//	matrix_trans1(trans);
//	transform(shaderProgram_tex, trans);
//        glBindVertexArray(vbuff.VAO); //TODO maybe for several triangles. not useful for now
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        // render container

//        glBindTexture(GL_TEXTURE_2D, texture2[1]);
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture2[0]);
//	matrix_trans2(trans);
//	transform(shaderProgram_tex, trans);
//        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
	
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &vbuff.VAO);
    glDeleteBuffers(1, &vbuff.VBO);
    glDeleteBuffers(1, &vbuff.EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
}

void DrawSprite(int texture, float position[3], float size[3], float angle, float color[3])
{
    float vec_centr[3] = {0.0f};
    float model[4][4] = {0.0f};
    float vec_rotate[3] = {0.0f, 0.0f, 1.0f};
    vec_centr[0] = 0.5f * size[0];
    vec_centr[1] = 0.5f * size[1];

    // prepare transformations
    glUseProgram(shaderProgram_tex);
    create_mat4(model, 1.0f);
    translate(model, position); 
    translate(model, vec_centr); // move origin of rotation to center of quad
    rotate(model, angle, vec_rotate); // then rotate
    vec_centr[0] = -vec_centr[0];
    vec_centr[1] = -vec_centr[1];
    translate(model, vec_centr); // move origin back

    scale(model, size); // last scale z = 1.0f

    transform(shaderProgram_tex, model, "model");
    // render textured quad
    glUniform3fv(glGetUniformLocation(shaderProgram_tex, "spriteColor"), 1, color);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(quadVAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

void initRenderData(unsigned int VBO)
{
    // configure VAO/VBO
        float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &quadVAO);
    glGenBuffers(1, &VBO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindVertexArray(quadVAO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}



