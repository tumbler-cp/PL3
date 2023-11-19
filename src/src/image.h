//
// Created by Abdujalol on 19.11.2023.
//

#ifndef IMAGE_H
#define IMAGE_H
#define IMAGE struct image
#include "pixel.h"

IMAGE {
    uint64_t width, height;
    PIXEL* data;
};

IMAGE allocate_image(uint64_t width, uint64_t height);

IMAGE reallocate_image(IMAGE* image, uint64_t width, uint64_t height);

void free_image_data(IMAGE*);

void rotate_90_image(IMAGE*, bool anticlockwise);

void rotate(IMAGE*, int angle);

#endif //IMAGE_H
