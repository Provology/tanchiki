#include "obstacle.h"

// TODO fix bug with transparent tanks. Maybe it position of collision relativly to tile map. Need to set series of tests with two colliding tanks on varios distances from each other.


static void locate_tank_on_map(int *x, int *y, const t_tile *tank)
{
    *x = (tank->pos[0] + (TILE_SIZE / 2)) / TILE_SIZE;
    *y = (tank->pos[1] + (TILE_SIZE / 2)) / TILE_SIZE;
//    printf("tank[%d][%d], meanwhile PIXEL_SIZE=%f\n", tank_cell[0], tank_cell[1], PIXEL_SIZE);  
}

static void locate_bullet_on_map(int *x, int *y, const t_tile *tank)
{
    *x = (tank->bullet_pos[0] + (TILE_SIZE / 2)) / TILE_SIZE;
    *y = (tank->bullet_pos[1] + (TILE_SIZE / 2)) / TILE_SIZE;
//    printf("tank[%d][%d], meanwhile PIXEL_SIZE=%f\n", tank_cell[0], tank_cell[1], PIXEL_SIZE);  
}

static void obstacle_list(int x, int y, t_tile *list[3][3], const t_tile map[MAP_SIZE][MAP_SIZE])
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
}

static void intersection(float *width, float *height, const float pos1[2], const float pos2[2])
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

static void is_there_way2(t_tile *list[3][3], t_tile *tank)
{
    float width = 0.0;
    float height = 0.0;
    const t_tile *obst[Q_DIRS][3] = {
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
//                printf("w = %f", width);
//                printf("h = %f\n", height);
//                printf("pos1 = %f, pos2 = %f\n", tank->pos[1], obst[dir][i]->pos[1]);
                if (width > 0.0 && height > 0.0) 
                {
                    tank->stop[dir] = 1;
//                    printf("dir = %d, i = %d\n", dir, i);
//                    printf("h = %f\n", height);
                    break;
                }
            }
        }
    }
//   printf("pos x=%f, y = %f\n", tank->pos[0], tank->pos[1]);
}

void neighbors(const int tank_cell[Q_TANKS][2], t_tile *list[3][3], const t_tile *tanks, const int tanknum)
{
    int x = tank_cell[tanknum][0];
    int y = tank_cell[tanknum][1];
    int pos_x[3] = {x - 1, x, x + 1};
    int pos_y[3] = {y + 1, y, y - 1};

    for (int i = 0; i < Q_TANKS; i++)
    {
        if (tanknum == i)
        {
            continue;
        }
        for (int j = 0; j < 3; j++)
        {
            if (tank_cell[i][0] == pos_x[j])
            {
                for (int k = 0; k < 3; k++)
                {
                    if (tank_cell[i][1] == pos_y[k])
                    {
                        list[k][j] = &tanks[i];
                    }
                }
            }
        }
    }
}

void minimap_draw(int x, int y, t_tile *list[3][3])
{
    // minimap press m
    if (minimap == 1)
    {
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
}

void is_there_way(t_tile *tanks, const t_tile map[MAP_SIZE][MAP_SIZE])
{
    int tank_cell[Q_TANKS][2] = {0};
    t_tile *list[3][3] = {0};

    for (int i = 0; i < Q_TANKS; i++)
    {
        locate_tank_on_map(&tank_cell[i][0], &tank_cell[i][1], &tanks[i]);
    }
    for (int i = 0; i < Q_TANKS; i++)
    {
        // form list of fixed obstacles around one square of map
        obstacle_list(tank_cell[i][0], tank_cell[i][1], list, map);
        // other tanks on a way
        neighbors(tank_cell, list, tanks, i);
        if (0 == i || 2 == i) // TODO debug config for two tanks
        {
            is_there_way2(list, &tanks[i]);
            minimap_draw(tank_cell[i][0], tank_cell[i][1], list);
        }
        // ready list of obstacles for one tank
//        is_there_way2(list, &tanks[i]);
    }
}

static void target_list(int x, int y, t_tile *list[3][3], const t_tile map[MAP_SIZE][MAP_SIZE])
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
            if ((MAP_SIZE - 1 == x && 2 == j) || (0 == x && 0 == j))
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
}

void bullet_collide(t_tile *tanks, const t_tile map[MAP_SIZE][MAP_SIZE])
{
    int tank_cell[Q_TANKS][2] = {0};
    t_tile *list[3][3] = {0};

    for (int i = 0; i < Q_TANKS; i++)
    {
        locate_bullet_on_map(&tank_cell[i][0], &tank_cell[i][1], &tanks[i]);
    }
    for (int i = 0; i < Q_TANKS; i++)
    {
        target_list(tank_cell[i][0], tank_cell[i][1], list, map);
        // TODO all
    }
}

//void tank_collision(t_tile *tanks)
//{
//
//    for (int i = 0; i < Q_TANKS; i++)
//    {
//        for (int j = 1; j < Q_TANKS; j++)
//        {
//            if (j == i)
//            {
//                continue;
//            }
//            if ((tanks[i].pos[0] > tanks[j].pos[0] &&
//                        tanks[i].pos[0] - tanks[j].pos[0] < TILE_SIZE) ||
//                    (tanks[i].pos[0] < tanks[j].pos[0] &&
//                     tanks[j].pos[0] - tanks[i].pos[0] < TILE_SIZE))
//            {
//                if ((tanks[i].pos[1] > tanks[j].pos[1] &&
//                        tanks[i].pos[1] - tanks[j].pos[1] < TILE_SIZE) ||
//                    (tanks[i].pos[1] < tanks[j].pos[1] &&
//                     tanks[j].pos[1] - tanks[i].pos[1] < TILE_SIZE))
//                {
//                    printf("ENTER FIELD\n");
//                }
//            }
//        }
//    }
//}

// void is_there_way(int *tank_cell, t_tile *tank, t_tile map[MAP_SIZE][MAP_SIZE])
// {
//     int x = tank_cell[0];
//     int y = tank_cell[1];
//     
//     memset(tank->stop, 0, sizeof(*tank->stop) * 4);
//     if (x > 0 && (map[y + 1][x - 1].texture[0] != 0 || map[y][x - 1].texture[0] != 0 || (y > 0 && map[y - 1][x - 1].texture[0] != 0)) && (tank->pos[0] - (map[y][x - 1].pos[0] + TILE_SIZE) < PIXEL_SIZE))
//     {
//         if ((y < MAP_SIZE - 1) && map[y + 1][x - 1].texture[0] != 0 && tank->pos[1] + TILE_SIZE - PIXEL_SIZE - map[y + 1][x - 1].pos[1] > 0.0)
//         {
//             tank->stop[0] = 1; // left
//             printf("stop1\n");
//         }
//         if (map[y][x - 1].texture[0] != 0) 
//         {
//             tank->stop[0] = 1; // left
//             printf("stop2\n");
//         }
//         if (y > 0 && map[y - 1][x - 1].texture[0] != 0 && tank->pos[1] + PIXEL_SIZE < map[y - 1][x - 1].pos[1] + TILE_SIZE)
//         {
//             tank->stop[0] = 1; // left
//             printf("stop3\n");
//         }
//     }
//     if ((x < MAP_SIZE - 1) && (map[y + 1][x + 1].texture[0] != 0 || map[y][x + 1].texture[0] != 0 || (y > 0 && map[y - 1][x + 1].texture[0] != 0)) && (map[y][x + 1].pos[0] -  (tank->pos[0] + TILE_SIZE) < PIXEL_SIZE))
//     {
//         if ((y < MAP_SIZE - 1) && map[y + 1][x + 1].texture[0] != 0 && tank->pos[1] + TILE_SIZE - PIXEL_SIZE - map[y + 1][x + 1].pos[1] > 0.0)
//         {
//             tank->stop[1] = 1; // right
//             printf("stop r1\n");
//         }
//         if (map[y][x + 1].texture[0] != 0) 
//         {
//             tank->stop[1] = 1; // right
//             printf("stop r2\n");
//         }
//         if (y > 0 && map[y - 1][x + 1].texture[0] != 0 && tank->pos[1] + PIXEL_SIZE < map[y - 1][x + 1].pos[1] + TILE_SIZE)
//         {
//             tank->stop[1] = 1; // right
//             printf("stop r3\n");
//         }
//     }
//     if (y > 0 && (map[y - 1][x + 1].texture[0] != 0 || map[y - 1][x].texture[0] != 0 || (x > 0 && map[y - 1][x - 1].texture[0] != 0)) && (tank->pos[1] - map[y - 1][x].pos[1] - TILE_SIZE < PIXEL_SIZE))
//     {
//         if (x < MAP_SIZE - 1 && map[y - 1][x + 1].texture[0] != 0 && tank->pos[0] + TILE_SIZE - PIXEL_SIZE - map[y - 1][x + 1].pos[0] > 0.0)
//         {
//             tank->stop[2] = 1; // down
//             printf("stop d1\n");
//         }
//         if (map[y - 1][x].texture[0] != 0) 
//         {
//             tank->stop[2] = 1; // down
//             printf("stop d2\n");
//         }
//         if (x > 0 && map[y - 1][x - 1].texture[0] != 0 && tank->pos[0] + PIXEL_SIZE < map[y - 1][x - 1].pos[0] + TILE_SIZE)
//         {
//             tank->stop[2] = 1; // down
//             printf("stop d3\n");
//         }
//     }
//     if ((y < MAP_SIZE - 1) && (map[y + 1][x + 1].texture[0] != 0 || map[y + 1][x].texture[0] != 0 || (x > 0 && map[y + 1][x - 1].texture[0] != 0)) && (map[y + 1][x].pos[1] -  (tank->pos[1] + TILE_SIZE) < PIXEL_SIZE))
//     {
//         if ((x < MAP_SIZE - 1) && map[y + 1][x + 1].texture[0] != 0 && tank->pos[0] + TILE_SIZE - PIXEL_SIZE - map[y + 1][x + 1].pos[0] > 0.0)
//         {
//             tank->stop[3] = 1; // up 
//             printf("stop u1\n");
//         }
//         if (map[y + 1][x].texture[0] != 0) 
//         {
//             tank->stop[3] = 1; // up 
//             printf("stop u2\n");
//         }
//         if (x > 0 && map[y + 1][x - 1].texture[0] != 0 && tank->pos[0] + PIXEL_SIZE < map[y + 1][x - 1].pos[0] + TILE_SIZE)
//         {
//             tank->stop[3] = 1; // up 
//             printf("stop u3\n");
//         }
//     }
//     printf("pos x=%f, y = %f map[%d][%d] = {%f, %f}\n", tank->pos[0], tank->pos[1], y, x, map[y][x].pos[0], map[y][x].pos[1]);
// }


