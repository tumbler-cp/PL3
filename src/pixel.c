//
// Created by Abdujalol on 18.11.2023.
//

#include "pixel.h"
#include <malloc.h>

PIXEL_MATRIX* allocate_pixel_matrix(const uint64_t width, const uint64_t height) {
    PIXEL_MATRIX* matrix = malloc(sizeof(PIXEL_MATRIX));
    matrix->height = height;
    matrix->width = width;
    matrix->matrix = malloc(sizeof(PIXEL*) * height);
    for (uint64_t i = 0; i < height; i++) {
        matrix->matrix[i] = malloc(PIXEL_SIZE * width);
    }
    return matrix;
}

PIXEL* allocate_pixel_array(const uint64_t width, const uint64_t height) {
    return malloc(PIXEL_SIZE * width * height);
}

void free_pixel_matrix(PIXEL_MATRIX* matrix) {
    for (uint64_t i = 0; i < matrix->height; i++) {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
    free(matrix);
}

PIXEL_MATRIX* rotate_pixel_matrix(const PIXEL_MATRIX src, const bool clockwise) {
    PIXEL_MATRIX* matrix = allocate_pixel_matrix(src.height, src.width);
    for (uint64_t i = 0; i < src.height; i++) {
        for (uint64_t j = 0; j < src.width; j++) {
            if (clockwise) matrix->matrix[j][i] = src.matrix[src.height - i - 1][j];
            else matrix->matrix[j][i] = src.matrix[i][src.width - j - 1];
        }
    }
    return matrix;
}

PIXEL_MATRIX* pixel_array_to_matrix(PIXEL* array, const uint64_t width, const uint64_t height) {
    PIXEL_MATRIX* matrix = allocate_pixel_matrix(width, height);
    for (uint64_t i = 0; i < height; i++) {
        for (uint64_t j = 0; j < width; j++) {
            matrix->matrix[i][j] = array[i * width + j];
        }
    }
    return matrix;
}

PIXEL* pixel_matrix_to_array(const PIXEL_MATRIX matrix) {
    PIXEL* array = malloc(PIXEL_SIZE * matrix.width * matrix.height);
    for (uint64_t i = 0; i < matrix.height; i++) {
        for (uint64_t j = 0; j < matrix.width; j++) {
            array[i * matrix.width + j] = matrix.matrix[i][j];
        }
    }
    return array;
}
