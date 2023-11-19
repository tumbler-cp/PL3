//
// Created by Abdujalol on 19.11.2023.
//

#include "bmp.h"
#define BM 0x4D42
#include <inttypes.h>

void print_headers (const BMP_HEADERS h) {
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

unsigned padding(const uint64_t width) {
    return(4 - 3 * width % 4) % 4;
}

BMP_HEADERS read_headers(FILE* input) {
    BMP_HEADERS ret;
    fread(&ret, sizeof(BMP_HEADERS), 1, input);
    return ret;
}

BMP_HEADERS generate_headers(const IMAGE image) {
    const unsigned pad = padding(image.width);
    return (BMP_HEADERS) {
        .bfType = BM,
        .bfileSize = sizeof(BMP_HEADERS) + (image.width * sizeof(PIXEL) + pad) * image.height,
        .bfReserved = 0,
        .bOffBits = sizeof(BMP_HEADERS),
        .biSize = sizeof(uint32_t) * 9 + sizeof(uint16_t) * 2,
        .biWidth = image.width,
        .biHeight = image.height,
        .biPlanes = 1,
        .biBitCount = 24,
        .biCompression = 0,
        .biSizeImage = (image.width * sizeof(PIXEL) + pad) * image.height,
        .biXPelsPerMeter = 0,
        .biYPelsPerMeter = 0,
        .biClrUsed = 0,
        .biClrImportant = 0
    };
}

enum read_status from_bmp(FILE* input, IMAGE* image) {
    const BMP_HEADERS headers = read_headers(input);
    *image = reallocate_image(image, headers.biWidth, headers.biHeight);
    const unsigned pad = padding(image->width);
    for (uint64_t i = 0; i < image->height; i++) {
        for (uint64_t j = 0; j < image->width; j++) {
            fread(&image->data[i * image->width + j], sizeof(PIXEL), 1, input);
        }
        char musor[pad];
        fread(&musor, sizeof(uint8_t), pad, input);
    }
    print_headers(headers);
    return READ_OK;
}

enum write_status to_bmp(FILE* output, IMAGE const* image) {
    const unsigned pad = padding(image->width);
    const BMP_HEADERS headers = generate_headers(*image);
    fwrite(&headers, sizeof(BMP_HEADERS), 1, output);
    for (uint64_t i = 0; i < image->height; i++) {
        for (uint64_t j = 0; j < image->width; j++) {
            fwrite(&image->data[i * image->width + j], sizeof(PIXEL), 1, output);
        }
        char musor[pad];
        fwrite(&musor, sizeof(uint8_t), pad, output);
    }
    print_headers(headers);
    return WRITE_OK;
}
