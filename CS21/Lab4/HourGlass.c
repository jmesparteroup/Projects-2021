#include <stdio.h>
int main() {
    int n;
    scanf("%d", &n);
    int size = n * 2 + 3;
    for (int row = 0; row < size; row++) {
        printf("%d", row);
        for (int col = 0; col < size; col++) {
            if (row == 0 || row == size - 1) {
                if (col == 0 || col == size - 1) {
                printf("o");
                } else {
                printf("-");
                }
            } else if (col == row) {
                if (row == n + 1) {
                printf("X");
                } else {
                printf("\\");
                }
            } else if (col == size - row - 1) {
                printf("/");
            } else if (row > n + 1 && (size - row - 1 < col && col < row)) {
                printf(".");
            } else if (col < size - row - 1) {
                printf(" ");
            }
            }
        printf("\n");
    }
    return 0;
}