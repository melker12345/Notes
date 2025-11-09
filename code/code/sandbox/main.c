#include "stdio.h"

/*
 * assume i got a 8 by 16 display.
 * make some text move across it
 * */

int main() {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 16; j++) {
      printf("*");
    }
    printf("\n");
  }

  return 0;
}
