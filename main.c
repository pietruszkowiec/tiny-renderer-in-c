#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>

#include "tgaimage.h"
#include "wireframe.h"

#ifndef NAME_MAX
#define NAME_MAX 255
#endif


int main(int argc, char **argv) {
    char source_name[NAME_MAX];
    char destin_name[NAME_MAX];
    AXIS axis;
    int width = 800, height = 800;

    switch (argc) {
        case 1:
            strcpy(source_name, "objs/head.obj");
            strcpy(destin_name, "imgs/head_xy.tga");
            axis = XY;
            break;
 
 	case 5:
            width = atoi(argv[4]);
            height = width;
            if (width == 0 || height == 0) {
                fprintf(stderr, "got incorrect width/height\n");
                fprintf(stderr, "correct program call: "
                    "%s [path_to_obj_src] [path_to_tga_destin] "
                    "[xy|xz|yz] [width]\n", argv[0]);
                return 1;
            }

        case 4:
            strcpy(source_name, argv[1]);
            strcpy(destin_name, argv[2]);
            if ((strcmp(argv[3], "XY") == 0) || (strcmp(argv[3], "xy") == 0))
                axis = XY;
            else if ((strcmp(argv[3], "XZ") == 0) || (strcmp(argv[3], "xz") == 0))
                axis = XZ;
            else if ((strcmp(argv[3], "YZ") == 0) || (strcmp(argv[3], "yz") == 0))
                axis = YZ;
            else {
                fprintf(stderr, "wrong argument\n");
                fprintf(stderr, "correct program call: "
                    "%s [path_to_obj_src] [path_to_tga_destin] "
                    "[xy|xz|yz] [width]\n", argv[0]);
                return 1;
            }
            break;

        case 2:
            if ((strcmp(argv[1], "-h") == 0) || (strcmp(argv[1], "--help") == 0)) {
                printf("correct program call: "
                    "%s [path_to_obj_src] [path_to_tga_destin] "
                    "[xy|xz|yz] [width]\n", argv[0]);
                return 0;
            }
	    
        default:
            fprintf(stderr, "incorrect number of arguments\n");
            fprintf(stderr, "correct program call: "
                    "%s [path_to_obj_src] [path_to_tga_destin] "
                    "[xy|xz|yz] [width]\n", argv[0]);
            return 1;
    }

    tga_image image;

    mk_empty_tga_image(&image, width, height, RGB);

    draw_wireframe(&image, source_name, axis, width, height);

    write_tga_image(&image, destin_name);

    free_tga_image(&image);

    return 0;
}
