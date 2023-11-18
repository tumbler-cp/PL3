//
// Created by Abdujalol on 18.11.2023.
//

#include "bmp.h"

#include <inttypes.h>
#include <stdlib.h>

unsigned padding(uint64_t width) {
    unsigned ret = 0;
    if (width % 4 != 0) {
        while (width % 4 != 0) {
            ret++;
            width++;
        }
    }
    return ret;
}

void print_headers (const HEADERS h) {
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

HEADERS* read_headers(FILE* input) {
    HEADERS* headers = malloc(sizeof(HEADERS));
    fread(headers, sizeof(HEADERS), 1, input);
    return headers;
}

enum read_status from_bmp(FILE* input, struct image* src) {
    HEADERS* headers = read_headers(input);
    expand_image(src, headers->biWidth, headers->biHeight);
    fseek(input, headers->bOffBits, SEEK_SET);
    const unsigned pad = padding(*src->width);
    for (uint64_t i = 0; i < *src->height; i++) {
        for (uint64_t j = 0; j < *src->width; j++) {
            fread(&src->data[i * *src->width + j], sizeof(PIXEL), 1, input);
        }
        char musor[pad];
        fread(musor, 1, pad, input);
    }
    print_headers(*headers);
    free(headers);
    return READ_OK;
}

enum write_status to_bmp(FILE* output, struct image const* src) {
    printf("%" PRId64, *src->width);
    const unsigned pad = padding(*src->width);
    const HEADERS header = {
        .bfType = 0x4D42,
        .bfileSize = sizeof(HEADERS) + (*src->width * PIXEL_SIZE + pad) * *src->height,
        .bfReserved = 0,
        .bOffBits = sizeof(HEADERS),
        .biSize = sizeof(uint32_t) * 9 + sizeof(uint16_t) * 2,
        .biWidth = *src->width,
        .biHeight = *src->height,
        .biPlanes = 1,
        .biBitCount = 24,
        .biCompression = 0,
        .biSizeImage =  (*src->width * PIXEL_SIZE + pad) * *src->height,
        .biXPelsPerMeter = 0,
        .biYPelsPerMeter = 0,
        .biClrUsed = 0,
        .biClrImportant = 0
    };
    printf("\n_______________________\n");
    print_headers(header);
    fwrite(&header, sizeof(HEADERS), 1, output);
    for (uint64_t i = 0; i < *src->height; i++) {
        char musor[pad];
        for (uint64_t j = 0; j < *src->width; j++) {
            fwrite(&src->data[i * *src->width + j], PIXEL_SIZE, 1, output);
        }
        fwrite(musor, 1, pad, output);
    }
    return WRITE_OK;
}
