//I pledge my honor that I have abided by the stenes honor pledge 
#include <stdio.h>
#include <stdlib.h>

void display(int8_t bit) {
    putchar(bit + 48);
}

void display_32(int32_t num) {
    printf("%d\n", num);
    for(int i = 32; i > 0 ; i--){
        display((num >> i) & 1);
    }
}

int main(int argc, char const *argv[]) {
    
    const char *c = argv[1];
    int num = atoi(c);
    
    int32_t x = 382;
    display_32(num);

    return 0;
}
// ./a.out
