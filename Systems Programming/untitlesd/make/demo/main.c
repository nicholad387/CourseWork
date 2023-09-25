#include "utils.h"
#include "functions.h"
#include "display.h"

int main (int argc, char** argv) {
    char str[100];
    printf("Please type something: \n");
    scanf("%s", str);

    print_str(str);
    printf("The length is:");
    print_num(calculate_length(str));

    return 0;
}
