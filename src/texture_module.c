#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// format png include 8byte png header,
// and chunks: IHDR, PLTE, IDAT, IEND
// chunk consists of 4bytes length, 4bytes type
// lenbytes data, 4bytes CRC
typedef struct s_textheadr
{
    unsigned int width;
    unsigned int height;
    unsigned char bit_depth;
    unsigned char color_type;
    unsigned char compress_method;
    unsigned char filter_method;
    unsigned char interlace_method;
} t_textheadr;

typedef struct s_texture
{
    unsigned char chunk_type[4];
    unsigned char *chunk_data;
    int CRC;
    t_textheadr headr;
} t_texture;

// first chunk: 4byte width, 4bytes height, etc
void texture_IHDR(t_texture *data, FILE *fd)
{
    int len = 0;
    char chunk_length[4] = {0};

    len = fread(chunk_length, sizeof(chunk_length), 1, fd);
    // data->chunk_data = (unsigned char *)malloc(chunk_length * sizeof(char));
    data->chunk_data = (unsigned char *)malloc(sizeof(chunk_length));
    len = fread(data->chunk_type, sizeof(data->chunk_type), 1, fd);
    len = fread(data->chunk_data, chunk_length[3], 1, fd);
    memcpy(&(data->headr), &(data->chunk_data), chunk_length);
    printf("chunk_length = %d\n", chunk_length);
    printf("chunk_length1 = %d\n", sizeof(data->chunk_data));
    printf("chunk_type = %s\n", data->chunk_type);
    printf("width = %d\n", data->headr.width);
}

// image data - output of a compression algorithm
void texture_IDAT(void)
{
    return;
}

unsigned char *texture_unpack(const char *Path, 
                int *width, int *height, 
                int *color_channels)
{
    FILE *fd;
    t_texture data = {0};
    (void) color_channels;
    char head[8] = {0};

    fd = fopen(Path, "rb");
    if(NULL != fd)
    {
    	fread(&head, sizeof(head), 1, fd);
        texture_IHDR(&data, fd);
        texture_IDAT();
        // fread(&size, sizeof(size), 1, fd);
        // data.chunk_data = (unsigned char *)malloc(size * sizeof(char));
        // len = fread(data.chunk_type, sizeof(data.chunk_type), 1, fd);
        // len = fread(data.chunk_data, sizeof(data.chunk_data), 1, fd);
        // memcpy(&(data.headr), &(data.chunk_data), sizeof(data.headr));
        *width = data.headr.width;
        *height = data.headr.height;
        // printf("size = %d\n", size);
        // printf("chunk_type = %s\n", data.chunk_type);
        // printf("width = %d\n", data.headr.width);
        printf("width = %d\n", *width);
        // printf("height = %d\n", data.headr.height);
        printf("height = %d\n", *height);
        // printf("bit_depth = %d\n", data.headr.bit_depth);
        // printf("color_type = %d\n", data.headr.color_type);
        // printf("interlace_method = %d\n", data.headr.interlace_method);
        // printf("filter_method = %d\n", data.headr.filter_method);
        // printf("compress_method = %d\n", data.headr.compress_method);
    }
    else
    {
		printf("Failed to load texture\n");
    }
    fclose(fd);

    return(data.chunk_data);
}

void texture_free(unsigned char *data)
{
    free(data);
}
