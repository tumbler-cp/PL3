//
// Created by Abdujalol on 18.11.2023.
//

#ifndef BMP_H
#define BMP_H
#define HEADERS struct bmp_header
#include "image.h"
#include <stdio.h>

#pragma pack(push, 1)
struct bmp_header {
    uint16_t bfType;
    uint32_t  bfileSize;
    uint32_t bfReserved;
    uint32_t bOffBits;
    uint32_t biSize;
    uint32_t biWidth;
    uint32_t  biHeight;
    uint16_t  biPlanes;
    uint16_t biBitCount;
    uint32_t biCompression;
    uint32_t biSizeImage;
    uint32_t biXPelsPerMeter;
    uint32_t biYPelsPerMeter;
    uint32_t biClrUsed;
    uint32_t  biClrImportant;
};
#pragma pack(pop)

enum read_status {
    READ_OK = 0
};

enum write_status {
    WRITE_OK = 0
};

enum read_status from_bmp(FILE*, struct image*);
enum write_status to_bmp(FILE*, struct image const*);

#endif //BMP_H
