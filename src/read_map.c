#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#include"render.h"

unsigned int read_map(t_tile map[12][12], const char *Path)
{
    int fd = 0;
    int len = 0;
    char buf = 0;

    fd = open(Path, O_RDONLY);
    if(fd)
    {
        for (int i = 0; i < 12; i++)
        {
            for (int j = 0; j < 12; j++)
            {
                len = read(fd, &buf, sizeof(buf));
                if (buf == 'B')
                {
                    map[i][j].texture[0] = 17;
                    printf("map[%d][%d]\n", i, j);
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

}

