#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include"read_map.h"

unsigned int read_map(t_tile map[MAP_SIZE][MAP_SIZE], const char *Path)
{
    int fd = 0;
    int len = 0;
    char buf = 0;

    fd = open(Path, O_RDONLY);
    if(fd)
    {
        for (int i = 0; i < MAP_SIZE; i++)
        {
            for (int j = 0; j < MAP_SIZE; j++)
            {
                len = read(fd, &buf, sizeof(buf));
                if (buf == 'B')
                {
//                    map[i][j].texture[0] = j;
                    map[i][j].texture[0] = 17;
//                    printf("map[%d][%d]\n", i, j);
                }
                else
                {
                    map[i][j].texture[0] = 0;
                }
//                printf("%c", buf); 
            }
//            printf("\n"); 
        }
    // printf("len = %d\n", len);
    }
    close(fd);
    for (int i = 0; i < MAP_SIZE; i++)
    {
        for (int j = 0; j < MAP_SIZE; j++)
        {
            map[i][j].pos[0] = TILE_SIZE * j;//width;
            map[i][j].pos[1] = TILE_SIZE * i;// height * i;
        }
    }
    return (0);
}

