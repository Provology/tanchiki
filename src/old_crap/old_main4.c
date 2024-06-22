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

// images
const char *PATH_BC = "/home/ruslan/Downloads/battle_city.jpg";
// shaders
const char *SHADER_VERTEX = "/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/projection.vs"; 
const char *SHADER_FRAGMENT = "/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/projection.fs";
// settings
int Keys[1024] = {0};
float mixValue = 0.0f;
unsigned int shaderProgram_tex;//TODO create shader program object
// unsigned int quadVAO;



void processInput(GLFWwindow *window);
void DrawSprite(t_vbuff *vbuff, int texture, float position[3], float size[3], float angle, float color[3]);
void initRenderData(t_vbuff *vbuff);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int main()
{
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    GLFWwindow *window = NULL;
    int error = 0;
    t_vbuff vbuff = {0};
    unsigned int texture1[3];

    glfw_init();
    error = glfw_window(&window);
    if(error < 0)
    {
        return(-1);
    }
    
    glfwSetKeyCallback(window, key_callback);

       // build and compile our shader program
    // ------------------------------------
    shaderProgram_tex = build_shader(SHADER_VERTEX, SHADER_FRAGMENT);
    glUseProgram(shaderProgram_tex);
    initRenderData(&vbuff);
 
    printf("error %d\n", glGetError());
//    vertices_buffer(&vbuff);
    // load and create a texture 
    // -------------------------
    texture_loader(texture1, PATH_BC);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(shaderProgram_tex);

//    printf("vao = %d\n", vbuff->VAO);
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // calculate deltatime
        //
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        // input
        // -----
        processInput(window);

        // update game state
        //

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // create transformations
    	// float trans[4][4] = {0};
        float pos[3] = {100.0, 5.0, 0.0};
        float size[3] = {1.0, 1.0, 1.0};
        float angle = 50.0;
        float color[3] = {1.0, 0.4, 1.0};

    	DrawSprite(&vbuff, texture1[0], pos, size, angle, color); 

        glfwSwapBuffers(window);
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

void DrawSprite(t_vbuff *vbuff, int texture, float position[3], float size[3], float angle, float color[3])
{
    float vec_centr[3] = {0.0f};
    float model[4][4] = {0.0f};
    float vec_rotate[3] = {0.0f, 0.0f, 1.0f};
    vec_centr[0] = 0.5f * size[0];
    vec_centr[1] = 0.5f * size[1];

    // prepare transformations
    glBindTexture(GL_TEXTURE_2D, texture);
    glUseProgram(shaderProgram_tex);
    create_mat4(model, 1.0f);
//    translate(model, position); 
//    translate(model, vec_centr); // move origin of rotation to center of quad
//    rotate(model, angle, vec_rotate); // then rotate
    vec_centr[0] = -vec_centr[0];
    vec_centr[1] = -vec_centr[1];
//    translate(model, vec_centr); // move origin back

//    scale(model, size); // last scale z = 1.0f

//    transform(shaderProgram_tex, model, "model");
    // render textured quad
//    glUniform3fv(glGetUniformLocation(shaderProgram_tex, "spriteColor"), 1, color);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glBindVertexArray(vbuff->VAO);
    glDrawArrays(GL_TRIANGLES, 0, 6);
//  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void initRenderData(t_vbuff *vbuff)
{
    // unsigned int vbuff->VAO = vbuff->VAO;
    // unsigned int VBO = vbuff->VBO;
    // configure VAO/VBO
       static float vertices[] = { 
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &vbuff->VAO);
    glGenBuffers(1, &vbuff->VBO);

    glBindVertexArray(vbuff->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, vbuff->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}


void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            Keys[key] = 1;
        else if (action == GLFW_RELEASE)
            Keys[key] = 0;
    }
}



