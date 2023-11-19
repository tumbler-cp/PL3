//
// Created by Abdujalol on 19.11.2023.
//

#include "image.h"

#include <stdlib.h>


IMAGE allocate_image(const uint64_t width, const uint64_t height) {
    return (IMAGE){.width = width, .height = height, .data = allocate_pixel_array(width, height)};
}

IMAGE reallocate_image(IMAGE* image, const uint64_t width, const uint64_t height) {
    free_image_data(image);
    return allocate_image(width, height);
}

void free_image_data(IMAGE* image) {
    free(image->data);
}

void rotate_90_image(IMAGE* image, const bool anticlockwise) {
    PIXEL_MATRIX buffer_matrix = pixel_array_to_matrix(image->data, image->width, image->height);
    buffer_matrix = rotated_pixel_matrix(buffer_matrix, anticlockwise);
    *image = reallocate_image(image, buffer_matrix.width, buffer_matrix.height);
    image->data = pixel_matrix_to_array(buffer_matrix);
    free_pixel_matrix(&buffer_matrix);
}

void rotate(IMAGE* image, const int angle) {
    const bool anticlock = angle < 0;
    for (int i = 0; i < abs(angle) / 90; i++) {
        rotate_90_image(image, anticlock);
    }
}
