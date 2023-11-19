#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
#include "helpers.h"

int main( int argc, char** argv ) {
    if (argc != 4) {
        perror("Expected 3 arguments: <\"inputfile\"> <\"outputfile\"> <\"angle\">");
        return -1;
    }

    FILE* in = fopen(argv[1], "rb");
    FILE* out = fopen(argv[2], "wb");
    IMAGE image = allocate_image(0, 0);

    const int angle = parse_int_from_string(argv[3]);
    if (angle % 90 != 0) {
        perror("Angle should be multiple of 90");
    }

    from_bmp(in, &image);
    rotate(&image, angle);
    to_bmp(out, &image);
    return 0;
}
