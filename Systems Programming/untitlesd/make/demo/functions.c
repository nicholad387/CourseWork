#include "utils.h"
#include "functions.h"

int calculate_length(char* str) {
    int i = 0;
    while (str && str[i] != 0) {
        i ++;
    }
    if (strlen(str) == i) return i;
    else return -1;
}
