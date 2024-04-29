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
    unsigned char *chunk_data[3];
    unsigned int CRC;
    t_textheadr headr;
} t_texture;

int endian_convert(unsigned char *read_buf)
{
    int num = (int)read_buf[3] | (int)read_buf[2] << 8 | (int)read_buf[1] << 16 | (int)read_buf[0] << 24; 
    return (num);
}


// first chunk: 4byte width, 4bytes height, etc
void texture_IHDR(t_texture *data, FILE *fd)
{
    int len = 0;
    unsigned char read_length[4] = {0};
    int chunk_length;

    len = fread(read_length, sizeof(read_length), 1, fd);
    chunk_length = endian_convert(read_length);
    data->chunk_data[0] = (unsigned char *)malloc(chunk_length * sizeof(char));
    if (data->chunk_data[0])
    {
        len = fread(data->chunk_type, sizeof(data->chunk_type), 1, fd);
//        printf("read_length = %d\n", read_length);
//        printf("chunk_length = %d\n", chunk_length);
        len = fread(data->chunk_data[0], chunk_length, 1, fd);
//        printf("chunk_length1 = %d\n", sizeof(data->chunk_data[0]));
        printf("chunk_type = %s\n", data->chunk_type);
        memcpy(&(data->headr), &(data->chunk_data[0]), chunk_length);
	data->headr.width = endian_convert(data->chunk_data[0]);
	data->headr.height = endian_convert(data->chunk_data[0] + sizeof(int)); 
//        printf("width = %d\n", data->headr.width);
//        printf("size of CRC = %d\n", sizeof(data->CRC));
        len = fread(&data->CRC, sizeof(data->CRC), 1, fd);
        printf("CRC = %u\n", data->CRC);

        printf("bit_depth = %d\n", data->headr.bit_depth);
        printf("color_type = %d\n", data->headr.color_type);
        printf("compress_method = %d\n", data->headr.compress_method);
        printf("filter_method = %d\n", data->headr.filter_method);
        printf("interlace_method = %d\n", data->headr.interlace_method);
    }
}

// list of colors
void texture_PLTE(t_texture *data, FILE *fd)
{
    if(data->headr.color_type)
    {
//	printf("color_type = %d\n", data->headr.color_type);
    }
    int len = 0;
    unsigned char read_length[4] = {0};
    int chunk_length;

    len = fread(read_length, sizeof(read_length), 1, fd);
    chunk_length = endian_convert(read_length);
    data->chunk_data[1] = (unsigned char *)malloc(chunk_length * sizeof(char));
    if (data->chunk_data[1])
    {
        len = fread(data->chunk_type, sizeof(data->chunk_type), 1, fd);
        printf("plt_read_length = %d\n", read_length);
        printf("plt_chunk_length = %d\n", chunk_length);
        len = fread(data->chunk_data[1], chunk_length, 1, fd);
        printf("plt_chunk_length1 = %d\n", sizeof(data->chunk_data[1]));
        printf("plt_chunk_type = %s\n", data->chunk_type);
        len = fread(&data->CRC, sizeof(data->CRC), 1, fd);
        printf("CRC = %u\n", data->CRC);
    }
    return;
}

// image data - output of a compression algorithm
void texture_IDAT(t_texture *data, FILE *fd)
{
    int len = 0;
    unsigned char read_length[4] = {0};
    int chunk_length;

    len = fread(read_length, sizeof(read_length), 1, fd);
    chunk_length = endian_convert(read_length);
    data->chunk_data[2] = (unsigned char *)malloc(chunk_length * sizeof(char));
    if (data->chunk_data[2])
    {
        len = fread(data->chunk_type, sizeof(data->chunk_type), 1, fd);
        printf("dat_read_length = %d\n", read_length);
        printf("dat_chunk_length = %d\n", chunk_length);
        len = fread(data->chunk_data[2], chunk_length, 1, fd);
        printf("dat_chunk_length1 = %d\n", sizeof(data->chunk_data[2]));
        printf("dat_chunk_type = %s\n", data->chunk_type);
        len = fread(&data->CRC, sizeof(data->CRC), 1, fd);
        printf("CRC = %u\n", data->CRC);
    }
 
    return;
}

// remains 
void texture_IDK(t_texture *data, FILE *fd)
{
    int len = 0;
    unsigned char read_length[4] = {0};
    int chunk_length;

    len = fread(read_length, sizeof(read_length), 1, fd);
    chunk_length = endian_convert(read_length);
    data->chunk_data[2] = (unsigned char *)malloc(chunk_length * sizeof(char));
    if (data->chunk_data[2])
    {
        len = fread(data->chunk_type, sizeof(data->chunk_type), 1, fd);
        printf("idk_read_length = %d\n", read_length);
        printf("idk_chunk_length = %d\n", chunk_length);
        len = fread(data->chunk_data[2], chunk_length, 1, fd);
        printf("idk_chunk_length1 = %d\n", sizeof(data->chunk_data[2]));
        printf("idk_chunk_type = %s\n", data->chunk_type);
        len = fread(&data->CRC, sizeof(data->CRC), 1, fd);
        printf("CRC = %u\n", data->CRC);
    }
 
    return;
}

unsigned char *texture_unpack(const char *Path, 
                int *width, int *height, 
                int *color_channels)
{
    FILE *fd;
    t_texture data = {0};
    char head[8] = {0};

    fd = fopen(Path, "rb");
    if(NULL != fd)
    {
    	fread(&head, sizeof(head), 1, fd);
        texture_IHDR(&data, fd);
	texture_PLTE(&data, fd);
        texture_IDAT(&data, fd);
	texture_IDK(&data, fd);
        // fread(&size, sizeof(size), 1, fd);
        // data.chunk_data = (unsigned char *)malloc(size * sizeof(char));
        // len = fread(data.chunk_type, sizeof(data.chunk_type), 1, fd);
        // len = fread(data.chunk_data, sizeof(data.chunk_data), 1, fd);
        // memcpy(&(data.headr), &(data.chunk_data), sizeof(data.headr));
        *width = data.headr.width;
        *height = data.headr.height;
	color_channels = (int *)data.chunk_data[1];	//TODO
         // printf("size = %d\n", size);
	printf("colors = %d\n", color_channels);
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

	free(data.chunk_data[0]);
	free(data.chunk_data[1]);
    }
    else
    {
		printf("Failed to load texture\n");
    }
    fclose(fd);

    return(data.chunk_data[2]);
}

void texture_free(unsigned char *data)
{
    free(data);
}
