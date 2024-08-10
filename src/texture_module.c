#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include"texture_module.h"
#include"stb_image.h"



#define SPRITE_16 16

static void sprite_cut(char *sprite, const unsigned char *data, int width, int size)
{
    for(int i = 0; i < size; i++)
    {
    	for(int j = 0; j < 3 * size; j++)
	    {
	        sprite[j + (3 * size * i)] = data[j + (3 * width * i)];
	    }
    }
}

void texture_loader(unsigned int texnum, unsigned int *texture, const char *path_image)
{
    unsigned char *data = NULL;
    int width, height, nrChannels;
    
//    stbi_set_flip_vertically_on_load(1); // tell stb_image.h to flip loaded texture's on the y-axis.
    data = stbi_load(path_image, &width, &height, &nrChannels, 0);
    char sprite[3 * SPRITE_16 * SPRITE_16] = {0};
    int row_size = width / SPRITE_16;
    int indent = 0;
    int pseudo_height = 0;

//    glGenTextures(TEX_Q, texture);
    glGenTextures(texnum, texture);
    if (data)
    {
    	for(int i = 0; i < texnum; i++)
	    {
            glBindTexture(GL_TEXTURE_2D, texture[i]);
            // set the texture wrapping parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);	
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
            // set texture filtering parameters
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            // load image, create texture and generate mipmaps

            indent = 3 * SPRITE_16 * (i % row_size); // position of pixel in row
            pseudo_height = 3 * width * SPRITE_16 * (i / row_size); // all pixels in prev rows
            sprite_cut(sprite, data + pseudo_height + indent, width, SPRITE_16);
 
 //           glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        //    printf("width = %d, height = %d, data = %s\n", width, height, data);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, SPRITE_16, SPRITE_16, 0, GL_RGB, GL_UNSIGNED_BYTE, sprite);
            glGenerateMipmap(GL_TEXTURE_2D);
//            printf("row-size = %d, i = %d, width = %d\n", row_size, i, width);
	    }
    }
    else
    {
	    printf("Failed to load texture\n");
    }
    stbi_image_free(data);
}


