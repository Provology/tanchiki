#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include"definitions.h"
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
#include"ai_module.h"

//typedef struct s_player
//{
//    signed int velocity[2];
//} t_player;

enum e_game_state
{
    GAME_INACTIVE = 0,
    GAME_ACTIVE = 1
};


// images
static const char *PATH_BC = "/home/ruslan/Downloads/battle_city.jpg";
// map
static const char *PATH_MAP = "/home/ruslan/Desktop/PROJ/ping_pong/src/map2.txt";
// shaders
static const char *SHADER_VERTEX = "/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/projection.vs"; 
static const char *SHADER_FRAGMENT = "/home/ruslan/Desktop/PROJ/ping_pong/src/shaders/projection.fs";

//debug vars
int minimap = 0;
// settings
const float TILE_SIZE = SCR_WIDTH / MAP_SIZE;
const float PIXEL_SIZE = TILE_SIZE / 16;
static const float size[3] = {TILE_SIZE, TILE_SIZE, 1.0f};
static const float angle = 0.0f;
static const float color[3] = {1.0, 1.0, 1.0};

// settings
static int keys[1024] = {0};
// static t_player player = {0};
static enum e_game_state game_state = GAME_ACTIVE;


void processInput(GLFWwindow *window, int velocity[2], int *fire);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);
void render_tank(t_tile *tank, unsigned int shaderProgram_tex, t_vbuff *vbuff);
void render_map(unsigned int shaderProgram_tex, t_vbuff *vbuff, t_tile map[MAP_SIZE][MAP_SIZE]);
void init_tanks(t_tile *tanks, unsigned int *textures);
void move_tank(t_tile *tank);
void update_game(float deltaTime, t_tile *tanks, t_tile map[MAP_SIZE][MAP_SIZE]);
void guns(t_tile *tank);

int main()
{

    GLFWwindow *window = NULL;
    int error = 0;
    t_vbuff vbuff = {0};
    unsigned int textures[17];
    unsigned int shaderProgram_tex;//TODO create shader program object

    float currentFrame = 0.0f;
    float lastFrame = 0.0f;
    float deltaTime = 0.0f;

    t_tile tanks[Q_TANKS] = {{0}};
    t_tile map[MAP_SIZE][MAP_SIZE] = {0};

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
    texture_loader(sizeof(textures) / sizeof(unsigned int), textures, PATH_BC);
    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    glUseProgram(shaderProgram_tex);
//    printf("%d, %d, %d\n", textures[0], textures[1], textures[2]);

    create_ortho_proj(0.0f, SCR_WIDTH, 0.0f, SCR_HEIGHT); 
    init_tanks(tanks, textures);
    read_map(map, PATH_MAP);

//    printf("left = %d, right = %d, top = %d, bottom = %d\n", tanks[0].stop[0], tanks[0].stop[1], tanks[0].stop[2], tanks[0].stop[3]);
//    printf("%d\n", textures[16]);
    
    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // calculate deltatime
        //
        // TODO put this calculations in state updater
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        glfwPollEvents();

        // update game state
        //
        update_game(deltaTime, tanks, map);

        // input
        // -----
        processInput(window, tanks[0].velocity, &tanks[0].fire);

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

        render_map(shaderProgram_tex, &vbuff, map);
//        printf("x=%d, y=%d, ", tank_cell[0], tank_cell[1]);
//        printf("left = %d, right = %d, top = %d, bottom = %d\n", tanks[0].stop[0], tanks[0].stop[1], tanks[0].stop[2], tanks[0].stop[3]);
        for (int i = 0; i < Q_TANKS; i++)
        {
            render_tank(&tanks[i], shaderProgram_tex, &vbuff);
        }
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

void init_tanks(t_tile *tanks, unsigned int *textures)
{
    float pos[3] = {TILE_SIZE * 9, TILE_SIZE * 7, 0.0};

    for (int i = 0; i < Q_TANKS; i++)
    {
        for (int j = 0; j < 10; j++) // TODO 10 sprites of tank
        {
            tanks[i].texture[j] = textures[j];
        }
        memcpy(tanks[i].pos, pos, sizeof(pos)); 
        memcpy(tanks[i].color, color, sizeof(color));
    }

    // TODO random initial positions
    tanks[1].pos[0] -= 2 * TILE_SIZE;
    tanks[1].velocity[0] = -1;
    tanks[2].pos[0] -= 3 * TILE_SIZE;
    tanks[2].velocity[1] = -1;
}

void update_game(float deltaTime, t_tile *tanks, t_tile map[MAP_SIZE][MAP_SIZE])
{
    static float animStep = 0;
    static float moveTime = 0;
    
    animStep += deltaTime;
    moveTime += deltaTime;
    if (animStep > 0.1)
    {
        for (int i = 0; i < Q_TANKS; i++)
        {
            tanks[i].tex = ((tanks[i].tex + 1) % 2) + tanks[i].tex_index; // 2 - number of frames in animation loop
        }
        animStep = 0;
    }

    if (moveTime > 0.05)
    {
        guns(&tanks[0]);
//        for (int i = 0; i < 1; i++) 
//        {
//            tanks[i].velocity[0] = 0;
//            tanks[i].velocity[1] = 0;
//        }
//        ai_of_tanks(tanks); // TODO collision debug
        simple_ai_of_tanks(tanks);
        is_there_way(tanks, map);
        for (int i = 0; i < Q_TANKS; i++)
        {
            move_tank(&tanks[i]);
        }
        moveTime = 0;
    }
}

void guns(t_tile *tank)
{
    static int cannon_reload = 0;

//        printf("tank-fire = %d\n", tanks[0].fire);
    if (1 == tank->fire)
    {
        printf("FIRE!!\n");
        cannon_reload++;
        if (cannon_reload > 14)
        {
            tank->fire = 0;
            cannon_reload = 0;
            printf("RELOAD\n");
        }
    }
}

void render_map(unsigned int shaderProgram_tex, t_vbuff *vbuff, t_tile map[MAP_SIZE][MAP_SIZE])
{
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
           	DrawSprite(shaderProgram_tex, vbuff, map[i][j].texture[0], map[i][j].pos, size, angle, color);
//          printf("map[%d][%d] = %d\n", i, j, map[i][j].texture[0]);
        }
//      printf("%f\n", pos[0]);
    }
//  printf("-------------\n");
}

void move_tank(t_tile *tank)// TODO separate tex_index and pos in two funcs
{
//   printf("vx=%d, vy=%d\n", tank->velocity[0], tank->velocity[1]);
    // direction
    if (tank->velocity[0] < 0)
    {
        tank->tex_index = 2;
//        printf("x=%f, y=%f\n", tank->pos[0], tank->pos[1]);
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
//        printf("x=%f, y=%f\n", tank->pos[0], tank->pos[1]);
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
}

void render_tank(t_tile *tank, unsigned int shaderProgram_tex, t_vbuff *vbuff)
{
    DrawSprite(shaderProgram_tex, vbuff, tank->texture[tank->tex], tank->pos, size, angle, tank->color);
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, int velocity[2], int *fire)
{
    static int pause_pressed = 0;
//    static int color_inc = 0;
//    static int color_dec = 0;
//    static int i = 0;
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, 1);
    if (game_state == GAME_ACTIVE)
    {
        velocity[0] = 0;
        velocity[1] = 0;
        if (keys[GLFW_KEY_A])
        {
            velocity[0] = -1;
//            printf("left=%d, right=%d, %d\n", keys[GLFW_KEY_A], keys[GLFW_KEY_D], i);
//            i++;
        }
        else if (keys[GLFW_KEY_D])
        {
            velocity[0] = 1;
//            printf("right\n");
        }
        else if (keys[GLFW_KEY_W])
        {
            velocity[1] = 1;
//            printf("up\n");
        }
        else if (keys[GLFW_KEY_S])
        {
            velocity[1] = -1;
//            printf("down\n");
        }

        // fire cannon
        if (keys[GLFW_KEY_SPACE] && !*fire)
        {
            *fire = 1;
        }
    }
    if (keys[GLFW_KEY_Z] && !pause_pressed)
    {
        game_state = !game_state;
        printf("game_state = %d\n", game_state);
    }
    pause_pressed = keys[GLFW_KEY_Z];
    if (keys[GLFW_KEY_M])
    {
        minimap = !minimap;
    }
//    if (keys[GLFW_KEY_Q] && !color_inc) // TODO color change experiment
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







