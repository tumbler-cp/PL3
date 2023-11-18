//
// Created by Abdujalol on 17.11.2023.
//

#include "img.h"

#include <inttypes.h>
#include <malloc.h>
#include <stdio.h>

void free_img(IMAGE* img) {
    free(img->data);
    free(img->height);
    free(img->width);
}

