#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "definitions.h"

void is_there_way(t_tile *tanks, const t_tile map[MAP_SIZE][MAP_SIZE]);
// void is_there_way(int *tank_cell, t_tile *tank, t_tile map[MAP_SIZE][MAP_SIZE]);
void tank_collision(t_tile *tanks);

#endif // OBSTACLE_H


