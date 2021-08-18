#include <stdio.h>
#define N 1

int main() {
    int x = N;
    switch (x) {
    case -1:
        printf("N is negative one\n");
        break;
    case 0:
        printf("N is zero\n");
        break;
    case 1:
        printf("N is one\n");
        break;
    default:
        printf("N is not -1, 0, or 1\n");
        break;
    }
    return 0;
}