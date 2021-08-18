#include <stdio.h>

void swap(int x, int y) {
  int temp = x;
  x = y;
  y = x;
}

int main() {
  int x = 1;
  int y = 2;

  printf("x: %d\n", x);
  printf("y: %d\n", y);

  swap(x, y);

  printf("x: %d\n", x);
  printf("y: %d\n", y);

  return 0;
}
