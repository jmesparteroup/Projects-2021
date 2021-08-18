#include <stdio.h>

int x = 1;

void f() {
  int y = 1;
  static int z = 1;

  x += 1;
  y += 1;
  z += 1;

  printf("x: %d\n", x);
  printf("y: %d\n", y);
  printf("z: %d\n", z);
  printf("\n");
}

int main() {
  for (int i = 0; i < 5; i++) {
    f();
  }

  return 0;
}
