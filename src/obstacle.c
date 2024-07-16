#include "obstacle.h"



void is_there_way(int *tank_cell, t_tile *tank, t_tile map[MAP_SIZE][MAP_SIZE])
{
    int x = tank_cell[0];
    int y = tank_cell[1];
    
    memset(tank->stop, 0, sizeof(*tank->stop) * 4);
    if (x > 0 && (map[y + 1][x - 1].texture[0] != 0 || map[y][x - 1].texture[0] != 0 || (y > 0 && map[y - 1][x - 1].texture[0] != 0)) && (tank->pos[0] - (map[y][x - 1].pos[0] + TILE_SIZE) < PIXEL_SIZE))
    {
        if ((y < MAP_SIZE - 1) && map[y + 1][x - 1].texture[0] != 0 && tank->pos[1] + TILE_SIZE - PIXEL_SIZE - map[y + 1][x - 1].pos[1] > 0.0)
        {
            tank->stop[0] = 1; // left
            printf("stop1\n");
        }
        if (map[y][x - 1].texture[0] != 0) 
        {
            tank->stop[0] = 1; // left
            printf("stop2\n");
        }
        if (y > 0 && map[y - 1][x - 1].texture[0] != 0 && tank->pos[1] + PIXEL_SIZE < map[y - 1][x - 1].pos[1] + TILE_SIZE)
        {
            tank->stop[0] = 1; // left
            printf("stop3\n");
        }
    }
    if ((x < MAP_SIZE - 1) && (map[y + 1][x + 1].texture[0] != 0 || map[y][x + 1].texture[0] != 0 || (y > 0 && map[y - 1][x + 1].texture[0] != 0)) && (map[y][x + 1].pos[0] -  (tank->pos[0] + TILE_SIZE) < PIXEL_SIZE))
    {
        if ((y < MAP_SIZE - 1) && map[y + 1][x + 1].texture[0] != 0 && tank->pos[1] + TILE_SIZE - PIXEL_SIZE - map[y + 1][x + 1].pos[1] > 0.0)
        {
            tank->stop[1] = 1; // right
            printf("stop r1\n");
        }
        if (map[y][x + 1].texture[0] != 0) 
        {
            tank->stop[1] = 1; // right
            printf("stop r2\n");
        }
        if (y > 0 && map[y - 1][x + 1].texture[0] != 0 && tank->pos[1] + PIXEL_SIZE < map[y - 1][x + 1].pos[1] + TILE_SIZE)
        {
            tank->stop[1] = 1; // right
            printf("stop r3\n");
        }
    }
    if (y > 0 && (map[y - 1][x + 1].texture[0] != 0 || map[y - 1][x].texture[0] != 0 || (x > 0 && map[y - 1][x - 1].texture[0] != 0)) && (tank->pos[1] - map[y - 1][x].pos[1] - TILE_SIZE < PIXEL_SIZE))
    {
        if (x < MAP_SIZE - 1 && map[y - 1][x + 1].texture[0] != 0 && tank->pos[0] + TILE_SIZE - PIXEL_SIZE - map[y - 1][x + 1].pos[0] > 0.0)
        {
            tank->stop[2] = 1; // down
            printf("stop d1\n");
        }
        if (map[y - 1][x].texture[0] != 0) 
        {
            tank->stop[2] = 1; // down
            printf("stop d2\n");
        }
        if (x > 0 && map[y - 1][x - 1].texture[0] != 0 && tank->pos[0] + PIXEL_SIZE < map[y - 1][x - 1].pos[0] + TILE_SIZE)
        {
            tank->stop[2] = 1; // down
            printf("stop d3\n");
        }
    }
    if ((y < MAP_SIZE - 1) && (map[y + 1][x + 1].texture[0] != 0 || map[y + 1][x].texture[0] != 0 || (x > 0 && map[y + 1][x - 1].texture[0] != 0)) && (map[y + 1][x].pos[1] -  (tank->pos[1] + TILE_SIZE) < PIXEL_SIZE))
    {
        if ((x < MAP_SIZE - 1) && map[y + 1][x + 1].texture[0] != 0 && tank->pos[0] + TILE_SIZE - PIXEL_SIZE - map[y + 1][x + 1].pos[0] > 0.0)
        {
            tank->stop[3] = 1; // up 
            printf("stop u1\n");
        }
        if (map[y + 1][x].texture[0] != 0) 
        {
            tank->stop[3] = 1; // up 
            printf("stop u2\n");
        }
        if (x > 0 && map[y + 1][x - 1].texture[0] != 0 && tank->pos[0] + PIXEL_SIZE < map[y + 1][x - 1].pos[0] + TILE_SIZE)
        {
            tank->stop[3] = 1; // up 
            printf("stop u3\n");
        }
    }
    printf("pos x=%f, y = %f map[%d][%d] = {%f, %f}\n", tank->pos[0], tank->pos[1], y, x, map[y][x].pos[0], map[y][x].pos[1]);
}

