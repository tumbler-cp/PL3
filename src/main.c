#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(const int argc, char** argv) {
    (void)argc;
    (void)argv;

    if (argc < 4) {
        perror("Not enough parameters (need 4)");
        return -1;
    }

    if (argc > 4) {
        perror("Too many parameters (need 4)");
        return -2;
    }

    FILE* in = fopen("input.bmp", "rb");
    FILE* out = fopen("output.bmp", "wb");
    IMAGE *buffer = malloc(sizeof(IMAGE));
    from_bmp(in, buffer);
    IMAGE* result = rotate_image_90(buffer, true);
    to_bmp(out, result);
    free_image(buffer);
    free_image(result);

    /*
    PIXEL* arr = allocate_pixel_array(3, 3);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            arr[3*i + j].b = i;
            arr[3*i + j].g = j;
            arr[3*i + j].r = i + j;
            printf(" %d%d%d ", arr[3*i + j].b, arr[3*i + j].g, arr[3*i + j].r);
        }
        printf("\n");
    }
    printf("\n_____________\n");
    PIXEL_MATRIX* matrix = pixel_array_to_matrix(arr, 3, 3);
    matrix = rotate_pixel_matrix(*matrix, true);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            printf(" %d%d%d ", matrix->matrix[i][j].b, matrix->matrix[i][j].g, matrix->matrix[i][j].r);
        }
        printf("\n");
    }
    free_pixel_matrix(matrix);
    return 0;
    */
}
