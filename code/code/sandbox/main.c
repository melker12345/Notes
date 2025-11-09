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
  const int FONT_H[8] = {
      0b10000001, 0b10000001, 0b10000001, 0b11111111,
      0b10000001, 0b10000001, 0b10000001, 0b00000000,
  };

  for (int y = 0; y < CHARACTER_HEIGHT; y++) {

    int row_pattern = FONT_H[y];

    for (int x = 0; x < CHARACTER_WIDTH; x++) {
      printf("*");
    }
    printf("\n");
  }

  return 0;
}
