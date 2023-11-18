//
// Created by Abdujalol on 18.11.2023.
//

#include "image.h"

#include <stdlib.h>

IMAGE* allocate_image(const uint64_t width, const uint64_t height) {
    IMAGE* image = malloc(sizeof(IMAGE));
    image->width = malloc(sizeof(uint64_t));
    image->height = malloc(sizeof(uint64_t));
    *image->width = width;
    *image->height = height;
    image->data = allocate_pixel_array(width, height);
    return image;
}

void expand_image(IMAGE* image, const uint64_t width, const uint64_t height) {
    image->width = malloc(sizeof(uint64_t));
    image->height = malloc(sizeof(uint64_t));
    *image->width = width;
    *image->height = height;
    image->data = allocate_pixel_array(width, height);
}

void free_image(IMAGE* image) {
    free(image->data);
    free(image->height);
    free(image->width);
    free(image);
}

IMAGE* rotate_image_90(IMAGE* src, const bool clockwise) {
    IMAGE* image = allocate_image(*src->height, *src->width);
    PIXEL_MATRIX* buffer_matrix = pixel_array_to_matrix(src->data, *src->width, *src->height);
    PIXEL_MATRIX* rotated_matrix = rotate_pixel_matrix(*buffer_matrix, clockwise); // Исправление здесь
    PIXEL* buffer_array = pixel_matrix_to_array(*rotated_matrix); // Исправление здесь
    image->data = buffer_array;
    free_pixel_matrix(buffer_matrix);
    free_pixel_matrix(rotated_matrix);
    return image;
}
