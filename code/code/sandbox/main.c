#include "stdio.h"
#include <string.h>

/*
 * assume i got a 8 by 16 display.
 * make some text move across it
 *
 **/
const int CHARACTER_WIDTH = 8;
const int CHARACTER_HEIGHT = 8;

const int FONT_A[8] = {
    0b01111110, 0b10000001, 0b10000001, 0b10000001,
    0b11111111, 0b10000001, 0b10000001, 0b10000001,
};
const int FONT_B[8] = {
    0b11111110, 0b10000001, 0b10000001, 0b11111110,
    0b10000001, 0b10000001, 0b10000001, 0b11111110,
};
const int FONT_H[8] = {
    0b10000001, 0b10000001, 0b10000001, 0b11111111,
    0b10000001, 0b10000001, 0b10000001, 0b00000000,
};

enum Font {
  FONT_A_INDEX,
  FONT_B_INDEX,
  FONT_H_INDEX,
};
const *int fonts[FONT_COUNT]{FONT_A, FONT_B, FONT_H};

void printFont(int FONT[8]) {
  for (int y = 0; y < CHARACTER_HEIGHT; y++) {
    int row_pattern = FONT[y];

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

int main() {
  // Move FONTS into a enum and then loop through all.
  for (int i = 0; i < 2; i++) {
    printFont(FONT_A);
  }

  return 0;
}
