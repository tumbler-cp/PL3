//
// Created by Abdujalol on 17.11.2023.
//

#ifndef IMG_H
#define IMG_H
#define IMAGE struct image
#define PIXEL struct pixel
#include <stdint.h>


struct pixel {
    uint8_t b, g, r;
};

struct image {
    uint64_t* width;
    uint64_t* height;
    struct pixel* data;
};

enum read_status {
    READ_OK = 0,
    READ_INVALID_SIGNATURE,
    READ_INVALID_BITS,
    READ_INVALID_HEADER
};

enum write_status {
    WRITE_OK = 0,
    WRITE_ERROR
};

void free_img(IMAGE*);



#endif //IMG_H
