#ifndef TGAIMAGE_H
#define TGAIMAGE_H


typedef enum {GRAYSCALE=1, RGB=3, RGBA=4} TGA_FORMAT;


typedef struct {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} tga_pixel;


typedef struct {
    tga_pixel *pixels;
    short width;
    short height;
    char bits_per_pixel;
} tga_image;


void mk_empty_tga_image(tga_image *const image, const short width, 
                        const short height, const char bits_per_pixel);

void set_tga_pixel(tga_image *const image, const tga_pixel *const pixel, 
                   const short x, const short y);

void write_tga_image(tga_image *const image, const char *file_name);

void free_tga_image(tga_image *const image);


#endif // TGAIMAGE_H
