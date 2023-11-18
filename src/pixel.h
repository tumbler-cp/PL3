//
// Created by Abdujalol on 18.11.2023.
//

#ifndef PIXEL_H
#define PIXEL_H
#define PIXEL struct pixel
#define PIXEL_MATRIX struct pixel_matrix
#define PIXEL_SIZE sizeof(PIXEL)
#include <stdint.h>
#include <stdbool.h>

struct pixel {
    uint8_t b, g, r;
};

struct pixel_matrix {
    uint64_t width, height;
    PIXEL** matrix;
};

PIXEL_MATRIX* allocate_pixel_matrix(uint64_t, uint64_t);
PIXEL* allocate_pixel_array(uint64_t, uint64_t);
void free_pixel_matrix(PIXEL_MATRIX*);

PIXEL_MATRIX* rotate_pixel_matrix(PIXEL_MATRIX, bool);
PIXEL_MATRIX* pixel_array_to_matrix(PIXEL[], uint64_t, uint64_t);
PIXEL* pixel_matrix_to_array(PIXEL_MATRIX);


#endif //PIXEL_H
