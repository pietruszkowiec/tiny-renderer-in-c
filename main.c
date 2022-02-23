#include <stdio.h>
#include <stdlib.h>

#include "tgaimage.h"


void swap(int *a, int *b) {
    *a = (*a) ^ (*b);
    *b = (*a) ^ (*b);
    *a = (*b) ^ (*a);
}


void draw_line(tga_image *const image, tga_pixel *const pixel,
             int x0, int y0, int x1, int y1) { 
    int steep = 0;
    if (abs(x0 - x1) < abs(y0 - y1)) {
        swap(&x0, &y0);
        swap(&x1, &y1);
        steep = 1;
    }
    if (x0 > x1) {
        swap(&x0, &x1);
        swap(&y0, &y1);
    }
    
    int dx = x1 - x0;
    int dy = y1 - y0;
    int derror2 = abs(dy) * 2;
    int error2 = 0;
    int y = y0; 
    for (int x = x0; x <= x1; x++) {
        if (steep)
            set_tga_pixel(image, pixel, y, x);
        else
            set_tga_pixel(image, pixel, x, y);
        
        error2 += derror2;
        if (error2 > dx) {
            y += (y1 > y0) ? 1 : -1;
            error2 -= dx * 2;
        }
    } 
}


int main(void) {
    const int width = 1000;
    const int height = 1000;

    tga_image image;
    
    mk_empty_tga_image(&image, width, height, RGB);
    
    tga_pixel white = (tga_pixel) {255, 255, 255, 255};
    tga_pixel red = (tga_pixel) {255, 0, 0, 255};
    tga_pixel green = (tga_pixel) {0, 255, 0, 255};

    draw_line(&image, &white, 13, 20, 800, 400); 
    draw_line(&image, &red, 20, 13, 400, 800); 
    draw_line(&image, &green, 80, 40, 130, 200);
    draw_line(&image, &white, 543, 124, 65, 175); 
    draw_line(&image, &red, 989, 123, 656, 234); 
    draw_line(&image, &green, 47, 432, 876, 999);
    
    write_tga_image(&image, "output.tga");
    
    free(image.pixels);
    
    return 0;
}
