//
// Created by Abdujalol on 18.11.2023.
//

#ifndef IMAGE_H
#define IMAGE_H
#define IMAGE struct image
#include "pixel.h"

struct image {
    uint64_t* width;
    uint64_t* height;
    PIXEL* data;
};

IMAGE* allocate_image(uint64_t,uint64_t);
void expand_image(IMAGE*, uint64_t, uint64_t);
void free_image(IMAGE*);
IMAGE* rotate_image_90(IMAGE*, bool);

#endif //IMAGE_H
