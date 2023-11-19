//
// Created by Abdujalol on 19.11.2023.
//

#include "helpers.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int str_size(const char* str) {
    int ret = 0;
    while (str[ret]) {
        ret++;
    }
    return ret;
}

int parse_int_from_string(const char* str) {
    const int sign = str[0] == '-' ? -1 : 1;
    int num = 0;
    const int len = str_size(str);
    for (int i = len - 1; i > (sign == 1 ? -1 : 0); i--) {
        if ((int)str[i] - 48 > -1 && (int)str[i] - 48 < 10) {
            num += ((int)str[i] - 48) * pow(10, len - i - 1);
        }
        else {
            perror("Parsing error. Check if the angle is numeric");
            exit(0);
        }
    }
    return sign * num;
}
