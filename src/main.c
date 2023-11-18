#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "custombmp.h"

void pwd() {
    char str[PATH_MAX];
    getcwd(str, sizeof(str));
    printf("%s", str);
}

int main(const int argc, char** argv) {
    (void)argc;
    (void)argv;

    if (argc < 4) {
        perror("Not enough parameters (need 4)");
        return -1;
    }

    if (argc > 4) {
        perror("Too much parameters (need 4)");
        return -2;
    }
    FILE* in = fopen("input.bmp", "rb");
    IMAGE* img = malloc(sizeof(IMAGE));
    FILE* out = fopen("output.bmp", "wb");
    from_bmp(in, img);
    to_bmp(out, img);
    free(img);
    fclose(in);
    fclose(out);
    return 0;
}
