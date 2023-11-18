#include "custombmp.h"

#include <complex.h>
#include <inttypes.h>
#include <stdlib.h>

#define ASCII_BITMAP 0x4D42

struct bmp_header open_bmp_headers(FILE* input) {
    struct bmp_header ret;
    fread(&ret, sizeof(struct bmp_header), 1, input);
    return ret;
}

size_t padding_for_w(const uint64_t width) {
    size_t padding = 0;
    if (width % 4 != 0) {
        uint64_t t = width;
        while (t % 4 != 0) t++;
        padding = sizeof(uint8_t) * (t - width);
    }
    return padding;
}

enum read_status from_bmp(FILE* file, struct image* img) {
    const BMP_HEADERS headers = open_bmp_headers(file);
    img->height = malloc(sizeof(uint64_t));
    img->width = malloc(sizeof(uint64_t));
    *img->height = headers.biHeight;
    *img->width = headers.biWidth;
    const uint64_t S = *img->width * *img->height;
    img->data = malloc(sizeof(PIXEL) * S);

    const size_t padding = padding_for_w(*img->width);

    for (uint64_t y = 0; y < *img->height; y++) {
        for (uint64_t x = 0; x < *img->width; x++) {
            PIXEL pix = {.r = 0, .g = 0, .b = 0};
            fread(&pix, sizeof(PIXEL), 1, file);
            img->data[*img->width * y + x] = pix;
        }
        fread(NULL, padding, 1, file);
    }
    return READ_OK;
}

enum write_status to_bmp(FILE* file, struct image const* img) {
    BMP_HEADERS heads = {
        .bfType = ASCII_BITMAP,
        .bfileSize = sizeof(BMP_HEADERS) + *img->width * *img->height * 3,
        .bfReserved = 0,
        .bOffBits = sizeof(BMP_HEADERS),
        .biSize = sizeof(uint32_t) * 9 + sizeof(uint16_t) * 2,
        .biWidth = *img->width,
        .biHeight = *img->height,
        .biPlanes = 1,
        .biBitCount = 24,
        .biCompression = 0,
        .biSizeImage = *img->width * *img->height * 3,
        .biXPelsPerMeter = 0,
        .biYPelsPerMeter = 0,
        .biClrUsed = 0,
        .biClrImportant = 0
    };

    fwrite(&heads, sizeof(BMP_HEADERS), 1, file);
    const size_t padding = padding_for_w(*img->width);

    for (uint64_t y = 0; y < *img->height; y++) {
        for (uint64_t x = 0; x < *img->width; x++) {
            fwrite(&(img->data[*img->width * y + x]), sizeof(PIXEL), 1, file);
        }
        fwrite(&padding, sizeof(uint8_t), padding, file);
    }

    return WRITE_OK;
}

void print_headers (BMP_HEADERS h) {
    printf("\n%" PRId16, h.bfType);
    printf("\n%" PRId32,  h.bfileSize);
    printf("\n%" PRId32,  h.bfReserved);
    printf("\n%" PRId32,  h.bOffBits);
    printf("\n%" PRId32,  h.biSize);
    printf("\n%" PRId32,  h.biWidth);
    printf("\n%" PRId32,  h.biHeight);
    printf("\n%" PRId16,  h.biPlanes);
    printf("\n%" PRId16,  h.biBitCount);
    printf("\n%" PRId32,  h.biCompression);
    printf("\n%" PRId32,  h.biSizeImage);
    printf("\n%" PRId32,  h.biXPelsPerMeter);
    printf("\n%" PRId32,  h.biYPelsPerMeter);
    printf("\n%" PRId32,  h.biClrUsed);
    printf("\n%" PRId32,  h.biClrImportant);
}