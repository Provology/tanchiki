#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "definitions.h"

enum e_dir
{
    LEFT = 0,
    RIGHT,
    DOWN,
    UP,
    Q_DIRS
};

void is_there_way(t_tile *tanks, const t_tile map[MAP_SIZE][MAP_SIZE]);
void bullet_collide(t_tile *tanks, const t_tile map[MAP_SIZE][MAP_SIZE]);
// void tank_collision(t_tile *tanks);

#endif // OBSTACLE_H


