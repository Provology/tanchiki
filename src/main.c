#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include"shader_module.h"
#include"stb_image.h"
#include"texture_module.h"
#include"vertices.h"
#include"create_window.h"
//#include"linear_algebra.h"
//#include"transformations.h"
#include"render.h"
#include"read_map.h"
#include"obstacle.h"

#define PATH_BANANA "/home/ruslan/Downloads/banana.png"
#define MAP_SIZE 12

typedef struct s_player
{
    signed int velocity[2];
} t_player;

enum e_game_state
{
    GAME_INACTIVE = 0,
    GAME_ACTIVE = 1
};

enum e_dir
{
    LEFT = 0,
    RIGHT,
    DOWN,
    UP,
    Q_DIRS
};


// images
const char *PATH_BC = "/home/ruslan/Downloads/battle_city.jpg";
// map
const char *PATH_MAP = "/home/ruslan/Desktop/PROJ/ping_pong/src/map.txt";
// shaders
const char *SHADER_VERTEX = "/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/projection.vs"; 
const char *SHADER_FRAGMENT = "/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/projection.fs";

void processInput(GLFWwindow *window);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void render_tank(float deltaTime, t_tile *tank, unsigned int shaderProgram_tex, t_vbuff *vbuff);
void locate_tank_on_map(int *tank_cell, t_tile *tank);
void is_there_way(int *tank_cell, t_tile *tank, t_tile map[12][12]);
void is_there_way2(t_tile *list[3][3], t_tile *tank);
void obstacle_list(int x, int y, t_tile *list[3][3], t_tile map[MAP_SIZE][MAP_SIZE]);

// settings
const float SCR_WIDTH = 600.0f;
const float SCR_HEIGHT = 600.0f; // unequal width and height lead to double calculations for pixel and tile sizes and changing params in case of tank 90dg turn.
// const unsigned int MAP_SIZE = 12;
const float TILE_SIZE = SCR_WIDTH / MAP_SIZE;
const float PIXEL_SIZE = TILE_SIZE / 16;
const float size[3] = {TILE_SIZE, TILE_SIZE, 1.0f};
const float angle = 0.0f;
const float color[3] = {1.0, 1.0, 1.0};

// settings
int keys[1024] = {0};
// float mixValue = 0.0f;
// int col = 0;
t_player player = {0};
enum e_game_state game_state = GAME_ACTIVE;
// unsigned int quadVAO;



int main()
{

    GLFWwindow *window = NULL;
    int error = 0;
    t_vbuff vbuff = {0};
    unsigned int textures[17];
    unsigned int shaderProgram_tex;//TODO create shader program object

    float currentFrame = 0;
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;
//    float timeStep = 0;
//    float animStep = 0;
//    int tex = 0;

    t_tile tanks[2] = {{0}};
    t_tile map[MAP_SIZE][MAP_SIZE] = {0};
    float pos[3] = {TILE_SIZE * 9, TILE_SIZE * 7, 0.0};
    int tank_cell[2] = {0};
    t_tile list[3][3] = {0};

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
    texture_loader(17, textures, PATH_BC);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(shaderProgram_tex);
//    printf("%d, %d, %d\n", textures[0], textures[1], textures[2]);


    create_ortho_proj(0.0f, SCR_WIDTH, 0.0f, SCR_HEIGHT); 
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 10; j++)
        {
            tanks[i].texture[j] = textures[j];
        }
        memcpy(tanks[i].pos, pos, sizeof(pos)); 
        memcpy(tanks[i].color, color, sizeof(color));
    }
//    printf("tex = %u, pos = %u\n", sizeof(textures), sizeof(pos));
    read_map(map, PATH_MAP);
    
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            map[i][j].pos[0] = TILE_SIZE * j;//width;
            map[i][j].pos[1] = TILE_SIZE * i;// height * i;
        }
    }

    printf("left = %d, right = %d, top = %d, bottom = %d\n", tanks[0].stop[0], tanks[0].stop[1], tanks[0].stop[2], tanks[0].stop[3]);
//    printf("%d\n", textures[16]);

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

        // update game state
        //
        for (int i = 0; i < 2; i++)
        {
            tanks[i].velocity[0] = 0;
            tanks[i].velocity[1] = 0;
        }

        // input
        // -----
        processInput(window);
        memcpy(tanks[0].velocity, player.velocity, sizeof(player.velocity));

       // TODO experimental color change
       // tanks[0].color[0] = sin(col);
       // tanks[0].color[1] = sin(col);
       // tanks[0].color[2] = sin(col);
       // printf("sin(col) = %f, col = %d\n", sin(col), col);

 
//        printf("%u\n", sizeof(player.velocity));

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // create transformations

        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {
           	    DrawSprite(shaderProgram_tex, &vbuff, map[i][j].texture[0], map[i][j].pos, size, angle, color);
//                printf("map[%d][%d] = %d\n", i, j, map[i][j].texture[0]);
            }
//            printf("%f\n", pos[0]);
        }
//        printf("-------------\n");

        locate_tank_on_map(tank_cell, &tanks[0]);
//        is_there_way(tank_cell, &tanks[0], map);
        obstacle_list(tank_cell[0], tank_cell[1], list, map);
        is_there_way2(list, &tanks[0]);
//        printf("x=%d, y=%d, ", tank_cell[0], tank_cell[1]);
//        printf("left = %d, right = %d, top = %d, bottom = %d\n", tanks[0].stop[0], tanks[0].stop[1], tanks[0].stop[2], tanks[0].stop[3]);
        render_tank(deltaTime, &tanks[0], shaderProgram_tex, &vbuff);
        render_tank(deltaTime, &tanks[1], shaderProgram_tex, &vbuff);
//        printf("%f, %f\n", tanks[0].pos[0], tanks[0].pos[1]);
//        printf("%d, %d\n", tanks[0].texture[0], textures[0]);


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

void locate_tank_on_map(int *tank_cell, t_tile *tank)
{
    tank_cell[0] = (tank->pos[0] + (TILE_SIZE / 2)) / TILE_SIZE;
    tank_cell[1] = (tank->pos[1] + (TILE_SIZE / 2)) / TILE_SIZE;
//    printf("tank[%d][%d], meanwhile PIXEL_SIZE=%f\n", tank_cell[0], tank_cell[1], PIXEL_SIZE);  
}


void obstacle_list(int x, int y, t_tile *list[3][3], t_tile map[MAP_SIZE][MAP_SIZE])
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            list[i][j] = NULL;
        }
    }
    for (int i = 0; i < 3; i++)
    {
        if ((MAP_SIZE - 1 == y && 0 == i) || (0 == y && 2 == i))
        {
            continue;
        }
        for (int j = 0; j < 3; j++)
        {
            if ((MAP_SIZE - 1 == x && 2 == j) || (0 == x && 0 == j) || (1 == i && 1 == j))
            {
//                printf("x,y,list=%d,%d,%d\n", j, i, list[i][j]);
                continue;
            }
            if (map[y + 1 - i][x - 1 + j].texture[0] != 0)
            {
                list[i][j] = &map[y + 1 - i][x - 1 + j];
            }
//            printf("list[%d][%d] = %f\n", i, j, list[i][j]->pos[0]);
        }
    }
    printf("list(x=%d, y=%d\n", x, y);
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (list[i][j])
            {
                printf("%3d [%d][%d], ", (int)list[i][j]->pos[0], i, j);
            }
            else
            {
                printf("NULL[%d][%d], ", i, j);
            }
        }
        printf("\n");
    }
    printf(")\n");
}

void intersection(float *width, float *height, const float pos1[2], const float pos2[2])
{
    float left = (pos1[0] > pos2[0]) ? pos1[0] : pos2[0];
    float right = (pos1[0] < pos2[0]) ? pos1[0] : pos2[0];
    right += TILE_SIZE;
    float top = (pos1[1] < pos2[1]) ? pos1[1] : pos2[1];
    top += TILE_SIZE;
    float bottom = (pos1[1] > pos2[1]) ? pos1[1] : pos2[1];
    *width = right - left;
    *height = top - bottom;

//    printf("pos1(%f, %f) pos2(%f, %f) width = %f, height = %f\n", pos1[0], pos1[1], pos2[0], pos2[1], *width, *height);
}

void is_there_way2(t_tile *list[3][3], t_tile *tank)
{
    float width = 0.0;
    float height = 0.0;
    const t_tile *obst[4][3] = {
        {list[0][0], list[1][0], list[2][0]}, // left
        {list[0][2], list[1][2], list[2][2]}, // right
        {list[2][0], list[2][1], list[2][2]}, // down
        {list[0][0], list[0][1], list[0][2]}// up
    };// iterate this obst array instead of list

    memset(tank->stop, 0, sizeof(*tank->stop) * 4);
    for (int dir = 0; dir < Q_DIRS; dir++)
    {
        for (int i = 0; i < 3; i++)
        {
            if (obst[dir][i])
            {
                intersection(&width, &height, tank->pos, obst[dir][i]->pos);
                if (LEFT == dir || RIGHT == dir)
                {
                    height -= PIXEL_SIZE;
                }
                if (DOWN == dir || UP == dir)
                {
                    width -= PIXEL_SIZE;
                }
                if (width > 0.0 && height > 0.0) 
                {
                    tank->stop[dir] = 1;
                    printf("dir = %d, i = %d\n", dir, i);
                    break;
                }
            }
        }
    }
//   printf("pos x=%f, y = %f\n", tank->pos[0], tank->pos[1]);
}

void render_tank(float deltaTime, t_tile *tank, unsigned int shaderProgram_tex, t_vbuff *vbuff)
{
    tank->animStep += deltaTime;
    tank->timeStep += deltaTime;
//    printf("%f\n", tank->timeStep);
    if (tank->animStep > 0.1)
    {
//        printf("animbranch\n");
        tank->tex = ((tank->tex + 1) % 2) + tank->tex_index; // 2 - number of frames in animation loop
        tank->animStep = 0;
    }
    if (tank->timeStep > 0.05)// TODO separate tex_index and pos in two funcs
    {
//        printf("vx=%d, vy=%d\n", tank->velocity[0], tank->velocity[1]);
        // direction
        if (tank->velocity[0] < 0)
        {
            tank->tex_index = 2;
//            printf("x=%f, y=%f\n", tank->pos[0], tank->pos[1]);
        }
        else if (tank->velocity[0] > 0)
        {
            tank->tex_index = 6;
        }
        else if (tank->velocity[1] < 0)
        {
            tank->tex_index = 0;
        }
        else if (tank->velocity[1] > 0)
        {
            tank->tex_index = 4;
        }
        // movement
        if (tank->velocity[0] < 0 && !tank->stop[0])
        {
            tank->pos[0] -= PIXEL_SIZE;
//            printf("x=%f, y=%f\n", tank->pos[0], tank->pos[1]);
        }
        else if (tank->velocity[0] > 0 && !tank->stop[1])
        {
            tank->pos[0] += PIXEL_SIZE;
        }
        else if (tank->velocity[1] < 0 && !tank->stop[2])
        {
            tank->pos[1] -= PIXEL_SIZE;
        }
        else if (tank->velocity[1] > 0 && !tank->stop[3])
        {
            tank->pos[1] += PIXEL_SIZE;
        }


        for (int i = 0; i < 2; i++)
        {
             if (tank->pos[i] + PIXEL_SIZE < 0.0)
             {
                 tank->pos[i] = 0.0 - PIXEL_SIZE;
             }
             else if (tank->pos[i] - PIXEL_SIZE > TILE_SIZE * (MAP_SIZE - 1))
             {
                 tank->pos[i] = TILE_SIZE * (MAP_SIZE - 1) + PIXEL_SIZE;
             }
        }
        tank->timeStep = 0;
    }
//    printf("%f, %f, %f\n", tank->pos[0], tank->pos[1], tank->pos[2]);
//    printf("shader2=%d\n", shaderProgram_tex);
    DrawSprite(shaderProgram_tex, vbuff, tank->texture[tank->tex], tank->pos, size, angle, tank->color);

}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
    static int pause_pressed = 0;
//    static int color_inc = 0;
//    static int color_dec = 0;
//    static int i = 0;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
    if (game_state == GAME_ACTIVE)
    {
        player.velocity[0] = 0;
        player.velocity[1] = 0;
        if (keys[GLFW_KEY_A])
        {
            player.velocity[0] = -1;
//            printf("left=%d, right=%d, %d\n", keys[GLFW_KEY_A], keys[GLFW_KEY_D], i);
//            i++;
        }
        else if (keys[GLFW_KEY_D])
        {
            player.velocity[0] = 1;
//            printf("right\n");
        }
        else if (keys[GLFW_KEY_W])
        {
            player.velocity[1] = 1;
//            printf("up\n");
        }
        else if (keys[GLFW_KEY_S])
        {
            player.velocity[1] = -1;
//            printf("down\n");
        }
    }
    if (keys[GLFW_KEY_SPACE] && !pause_pressed)
    {
        game_state = !game_state;
        printf("game_state = %d\n", game_state);
    }
    pause_pressed = keys[GLFW_KEY_SPACE];

//    if (keys[GLFW_KEY_Q] && !color_inc)
//    {
//        col++;
//    }
//    color_inc = keys[GLFW_KEY_Q];
//    if (keys[GLFW_KEY_E] && !color_dec)
//    {
//        col--;
//    }
//    color_dec = keys[GLFW_KEY_E];


//    printf("size=%u\n", sizeof(keys));
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
    // when a user presses the escape key, we set the WindowShouldClose property to true, closing the application
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
    if (key >= 0 && key < 1024)
    {
        if (action == GLFW_PRESS)
            keys[key] = 1;
        else if (action == GLFW_RELEASE)
            keys[key] = 0;
    }
}







