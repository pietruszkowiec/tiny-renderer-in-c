#include <stdio.h>
#include <stdlib.h>

#include "tgaimage.h"


void mk_empty_tga_image(tga_image *const image, const short width, 
                        const short height, const char bits_per_pixel) {
    image->width = width;
    image->height = height;
    image->bits_per_pixel = bits_per_pixel;
    int n = width * height;

    image->pixels = (tga_pixel *) malloc(n * sizeof(tga_pixel));

    if (!image->pixels) {
        printf("can't allocate memory\n");
        exit(-1);
    }
}


void set_tga_pixel(tga_image *const image, const tga_pixel *pixel, 
                   const short x, const short y) {
    image->pixels[x + y * image->width] = *pixel;
}


void write_tga_image(tga_image *const image, const char *file_name) {
    FILE *file_ptr;

    if (!(file_ptr = fopen(file_name, "w"))) {
        printf("can't write to file %s\n", file_name);
        free(image->pixels);
        exit(-1);
    }

    char header[18] = { 0 };
    header[2] = 2;  // truecolor
    header[12] = image->width & 0xFF;
    header[13] = (image->width >> 8) & 0xFF;
    header[14] = image->height & 0xFF;
    header[15] = (image->height >> 8) & 0xFF;
    header[16] = (image->bits_per_pixel == RGB) ? 24 : 32;

    fwrite((const char*)&header, 1, sizeof(header), file_ptr);

    for (int i = 0; i < image->width * image->height; i++) {
        putc(image->pixels[i].b & 0xFF, file_ptr);
        putc(image->pixels[i].g & 0xFF, file_ptr);
        putc(image->pixels[i].r & 0xFF, file_ptr);

        if (image->bits_per_pixel == RGBA)
            putc(image->pixels[i].a & 0xFF, file_ptr);
   }

    static const char footer[26] =
        "\0\0\0\0" // extension area
        "\0\0\0\0" // developer directory
        "TRUEVISION-XFILE.";
    
    fwrite((const char*)&footer, 1, sizeof(footer), file_ptr);

    fclose(file_ptr);
}
                    