#include "stdio.h"

/*
 * assume i got a 8 by 16 display.
 * make some text move across it
 * */

int main() {
  for (int i = 0; i <= 16; i++) {
    for (int j = 0; j <= 8; j++) {
      printf("O\n");
    }
  }

  return 0;
}
