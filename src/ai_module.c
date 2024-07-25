#include "ai_module.h"

void simple_ai_of_tanks(t_tile *tanks)
{
    static int counter = 0;

    if (counter > 40) // random number of turns tank goes in one direction
    {
//        tanks[1].velocity[0] = -tanks[1].velocity[0];
        tanks[2].velocity[1] = -tanks[2].velocity[1];
        counter = 0;
    }
    counter++;
}

void ai_of_tanks(t_tile *tanks)
{
    int dir = 0;
    float rand = 0.0f;

    for (int i = 1; i < Q_TANKS; i++)
    {
//        rand = glfwGetTime();
        if (tanks[i].pos[0] == tanks[i].pos_prev[0] && tanks[i].pos[1] == tanks[i].pos_prev[1])
        {
            tanks[i].counter++;
        }
        if (tanks[i].counter > 1000)
        {
            dir = ((signed char)rand + i) % 4; // TODO use real random numbers
            if (dir == 0)
            {
                tanks[i].velocity[0] = 0;
                tanks[i].velocity[1] = 1;
            }
            else if (dir == 1)
            {
                tanks[i].velocity[0] = 0;
                tanks[i].velocity[1] = -1;
            }
            else if (dir == 2)
            {
                tanks[i].velocity[0] = 1;
                tanks[i].velocity[1] = 0;
            }
            else if (dir == 3)
            {
                tanks[i].velocity[0] = -1;
                tanks[i].velocity[1] = 0;
            }
            tanks[i].counter = 0;
        }
        tanks[i].pos_prev[0] = tanks[i].pos[0];
        tanks[i].pos_prev[1] = tanks[i].pos[1];
//        printf("i = %d, counter = %d, rand = %d\n", i, tanks[i].counter, (signed char)rand & 1);
    }
}


