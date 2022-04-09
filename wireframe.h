#ifndef WIREFRAME_H
#define WIREFRAME_H

#include "tgaimage.h"

#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))


typedef enum {XY, XZ, YZ} AXIS;

void swap(int *a, int *b);

void draw_line(tga_image *const image, const tga_pixel *const pixel,
               int x0, int y0, int x1, int y1);

void draw_wireframe(tga_image *const image, const char *file_name, 
                    AXIS axis, int width, int height);


#endif // WIREFRAME_H