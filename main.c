#include <stdio.h>
#include <stdlib.h>

#include "tgaimage.h"


int main(void) {
    const int width = 1000;
    const int height = 1000;

    tga_image image;
    
    mk_empty_tga_image(&image, width, height, RGB);
    
    tga_pixel pixel;

    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            pixel = (tga_pixel) {.r = 0xFF & ((j * 255) / height), 
                                 .g = 0xFF & ((i * 255) / width),
                                 .b = 0xFF & (((i * j * 255 * 255) / width) / height)};

            set_tga_pixel(&image, &pixel, i, j);
        }
    }
    
    write_tga_image(&image, "test.tga");
    
    free(image.pixels);
    
    return 0;
}
