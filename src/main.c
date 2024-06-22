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
//#include"linear_algebra.h"
//#include"transformations.h"
#include"render.h"

#define PATH_BANANA "/home/ruslan/Downloads/banana.png"

// images
const char *PATH_BC = "/home/ruslan/Downloads/battle_city.jpg";
// shaders
const char *SHADER_VERTEX = "/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/projection.vs"; 
const char *SHADER_FRAGMENT = "/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/projection.fs";
// settings
int Keys[1024] = {0};
float mixValue = 0.0f;
// unsigned int quadVAO;



void processInput(GLFWwindow *window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);



// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

int main()
{

    GLFWwindow *window = NULL;
    int error = 0;
    t_vbuff vbuff = {0};
    unsigned int textures[3];
    unsigned int shaderProgram_tex;//TODO create shader program object

    float currentFrame = 0;
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
    float timeStep = 0;
    float animStep = 0;
    int tex = 0;

    t_tile tanks[2] = {0};
    t_tile map[100] = {0};

    float pos[3] = {500.0, 390.0, 0.0};
//  float size[3] = {400.0f, 256.0f, 1.0};
//  float size[3] = {800.0f, 600.0f, 1.0};
    float size[3] = {80.0f, 60.0f, 1.0};
    float angle = 0.0f;
    float color[3] = {1.0, 1.0, 1.0};

     glfw_init();
    error = glfw_window(&window, SCR_WIDTH, SCR_HEIGHT);
    if(error < 0)
    {
        return(-1);
    }
    
    glfwSetKeyCallback(window, key_callback);

    shaderProgram_tex = build_shader(SHADER_VERTEX, SHADER_FRAGMENT);

    glUseProgram(shaderProgram_tex);

    initRenderData(&vbuff);

    // load and create a texture 
    // -------------------------
    texture_loader(textures, PATH_BC);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(shaderProgram_tex);
//    printf("%d, %d, %d\n", textures[0], textures[1], textures[2]);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // calculate deltatime
        //
        currentFrame = glfwGetTime();
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
        animStep += deltaTime;
        timeStep += deltaTime;
//        printf("%f\n", timeStep);
        if (animStep > 0.1)
        {
            tex = (tex + 1) % 2; // 2 - number of frames in animation loop
            animStep = 0;
        }
        if (timeStep > 0.05)
        {
            pos[1] -= 5.0;
            if (pos[1] <= 20.0)
            {
                pos[1] = 20.0;
            }
            timeStep = 0;
        }

        tanks[0].pos[0] = pos[0];
        tanks[0].pos[1] = pos[1];
        tanks[0].pos[2] = pos[2];

    	DrawSprite(shaderProgram_tex, &vbuff, textures[tex], tanks[0].pos, size, angle, color, SCR_WIDTH, SCR_HEIGHT);
        for (int i = 0; i < 10; i++)
        {
            map[i].pos[0] = 80.0;
            map[i].pos[1] = 60.0 * i;
        	DrawSprite(shaderProgram_tex, &vbuff, textures[2], map[i].pos, size, angle, color, SCR_WIDTH, SCR_HEIGHT);
//            printf("%f\n", pos[0]);
        }
//        printf("-------------\n");
        for (int i = 0; i < 10; i++)
        {
            map[i].pos[1] = 360.0;
            map[i].pos[0] = 80.0 * i;
        	DrawSprite(shaderProgram_tex, &vbuff, textures[2], map[i].pos, size, angle, color, SCR_WIDTH, SCR_HEIGHT);
//            printf("%f\n", pos[0]);
        }
//        printf("-------------\n");
//    	DrawSprite(shaderProgram_tex, &vbuff, textures[tex], pos, size, angle, color); 
//        pos[0] = 700.0;

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







