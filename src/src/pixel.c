//
// Created by Abdujalol on 19.11.2023.
//

#include "pixel.h"

#include <stdlib.h>

PIXEL** allocate_array_array(const uint64_t width, const uint64_t height) {
    PIXEL** array_array = malloc(sizeof(PIXEL *) * height);
    for (uint64_t i = 0; i < height; i++) {
        array_array[i] = malloc(sizeof(PIXEL) * width);
    }
    return array_array;
}

PIXEL_MATRIX allocate_pixel_matrix(const uint64_t width, const uint64_t height) {
    return (PIXEL_MATRIX){.width = width, .height = height, .matrix = allocate_array_array(width, height)};
}

PIXEL* allocate_pixel_array(const uint64_t width, const uint64_t height) {
    return (PIXEL*) malloc(sizeof(PIXEL) * width * height);
}

void free_pixel_matrix(PIXEL_MATRIX* matrix) {
    for (uint64_t i = 0; i < matrix->height; i++) {
        free(matrix->matrix[i]);
    }
    free(matrix->matrix);
}

PIXEL_MATRIX rotated_pixel_matrix(PIXEL_MATRIX src, const bool anticlockwise) {
    PIXEL_MATRIX matrix = allocate_pixel_matrix(src.height, src.width);
    for (uint64_t i = 0; i < src.height; i++) {
        for (uint64_t j = 0; j < src.width; j++) {
            if (anticlockwise) matrix.matrix[j][i] = src.matrix[src.height - i - 1][j];
            else matrix.matrix[j][i] = src.matrix[i][src.width - j - 1];
        }
    }
    free_pixel_matrix(&src);
    return (PIXEL_MATRIX){.width = src.height, .height = src.width, .matrix = matrix.matrix};
}

PIXEL_MATRIX pixel_array_to_matrix(PIXEL* src, const uint64_t width, const uint64_t height) {
    PIXEL_MATRIX matrix = allocate_pixel_matrix(width, height);
    for (uint64_t i = 0; i < height; i++) {
        for (uint64_t j = 0; j < width; j++) {
            matrix.matrix[i][j] = src[i * width + j];
        }
    }
    return (PIXEL_MATRIX){.width = width, .height = height, .matrix = matrix.matrix};
}

PIXEL* pixel_matrix_to_array(const PIXEL_MATRIX matrix) {
    PIXEL* array = malloc(sizeof(PIXEL) * matrix.width * matrix.height);
    for (uint64_t i = 0; i < matrix.height; i++) {
        for (uint64_t j = 0; j < matrix.width; j++) {
            array[i * matrix.width + j] = matrix.matrix[i][j];
        }
    }
    return array;
}
