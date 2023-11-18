//
// Created by Abdujalol on 17.11.2023.
//

#ifndef CUSTOMBMP_H
#define CUSTOMBMP_H
#define BMP_HEADERS struct bmp_header
#include <stdint.h>
#include <stdio.h>

#include "img.h"

struct bmp_header {
    uint16_t bfType;
    uint32_t bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t biHeight;
    uint16_t biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t biClrImportant;
} __attribute__((packed));

struct bmp_header open_bmp_headers(FILE* input);
void print_headers (BMP_HEADERS);

enum read_status from_bmp(FILE*, struct image*);
enum write_status to_bmp(FILE*, struct image const*);


#endif //CUSTOMBMP_H
