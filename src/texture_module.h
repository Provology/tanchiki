#ifndef TEXTURE_MODULE_H
#define TEXTURE_MODULE_H

unsigned char *texture_unpack(const char *Path, 
                    int *width, int *height, 
                    int *color_channels);

void texture_free(unsigned char *data);

#endif // TEXTURE_MODULE_H
