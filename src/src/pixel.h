//
// Created by Abdujalol on 19.11.2023.
//

#ifndef PIXEL_H
#define PIXEL_H
#define PIXEL struct pixel
#define PIXEL_MATRIX struct pixel_matrix

#include <stdint.h>
#include <stdbool.h>

PIXEL {
    uint8_t b, g, r;
};

PIXEL_MATRIX {
    uint64_t width, height;
    PIXEL** matrix;
};

PIXEL_MATRIX allocate_pixel_matrix(uint64_t width, uint64_t height);

PIXEL* allocate_pixel_array(uint64_t width, uint64_t height);

void free_pixel_matrix(PIXEL_MATRIX*);

PIXEL_MATRIX rotated_pixel_matrix(PIXEL_MATRIX src, bool anticlockwise);

PIXEL_MATRIX pixel_array_to_matrix(PIXEL* src, uint64_t width, uint64_t height);

PIXEL* pixel_matrix_to_array(PIXEL_MATRIX);

#endif //PIXEL_H
