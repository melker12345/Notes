#include "stdio.h"
#include <string.h>

/*
 * assume i got a 8 by 16 display.
 * make some text move across it
 *
 **/
int main() {
  const int CHARACTER_WIDTH = 8;
  const int CHARACTER_HEIGHT = 8;
  const int FONT_A[8] = {
      0b01111110, 0b10000001, 0b10000001, 0b11111111,
      0b10000001, 0b10000001, 0b10000001,
  };
  const int FONT_B[8] = {
      0b11111110, 0b10000001, 0b10000001, 0b11111110,
      0b10000001, 0b10000001, 0b10000001, 0b11111110,
  };
  const int FONT_H[8] = {
      0b10000001, 0b10000001, 0b10000001, 0b11111111,
      0b10000001, 0b10000001, 0b10000001, 0b00000000,
  };

  for (int i = 0; i < 2; i++) {
    for (int y = 0; y < CHARACTER_HEIGHT; y++) {
      int row_pattern = FONT_B[y];

      for (int x = 0; x < CHARACTER_WIDTH; x++) {
        int bit_mask = 1 << (CHARACTER_WIDTH - 1 - x);

        if (row_pattern & bit_mask) {
          printf("*");
        } else {
          printf(" ");
        }
      }
      printf("\n");
    }
  }

  return 0;
}
