#include <stdio.h>

int main() {
  int matrix[3][2] = {10, 20, 30, 40, 50, 60};  // 3 rows, 2 columns

  for (int r = 0; r < 3; r++) {
    for (int c = 0; c < 2; c++) {
      printf("matrix[%d][%d] = %d (%p)\n", r, c, matrix[r][c], &matrix[r][c]);
    }
  }

  return 0;
}
