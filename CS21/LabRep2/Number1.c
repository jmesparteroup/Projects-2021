#include <stdio.h>
#include <stdint.h>


int main() {
    int *a, *b, A = 25, B= 25;
    a = &A; b = &B;
    printf("%p %d", *(a+=1), (*b) += 1);
}