#ifndef DEFINITIONS_H
#define DEFINITIONS_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <math.h>

#define MAP_SIZE 12
#define SCR_WIDTH 600.0f
#define SCR_HEIGHT 600.0f // unequal width and height lead to double calculations for pixel and tile sizes and changing params in case of tank 90dg turn.
#define Q_TANKS 3

typedef struct s_tile 
{
    float timeStep;
    float animStep;
    int tex;
    int tex_index;
    signed int velocity[2];
    float pos[3];
//    float size[3] = {80.0f, 60.0f, 1.0};
    float angle;
    float color[3];
    unsigned int texture[10]; //TODO animations of explosion, idle, all directions
    int stop[4];
    float pos_prev[2];
    int counter;
} t_tile;

// settings
extern const float TILE_SIZE;
extern const float PIXEL_SIZE;
extern int minimap;

#endif // DEFINITIONS_H
