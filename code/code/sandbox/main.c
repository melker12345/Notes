#include "stdio.h"
#include <string.h>

/*
 * assume i got a 8 by 16 display.
 * make some text move across it
 *
 **/
int main() {
  char text[] = "HI";
  int textLenght = strlen(text);
  printf("%d", textLenght);

  const int FONT_I[8] = {
      0b10000001, 0b10000001, 0b10000001, 0b11111111,
      0b10000001, 0b10000001, 0b10000001, 0b00000000,
  };

  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 32; j++) {
      printf("*");
    }
    printf("\n");
  }

  return 0;
}
