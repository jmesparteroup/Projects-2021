#include <stdio.h>

int my_pow(int base, unsigned int n) {
  int ret = 1;

  while (n--) {
    ret *= base;
  }

  return ret;
}

int main() {
  printf("2^3 = %d\n", my_pow(2, 3));

  return 0;
}
