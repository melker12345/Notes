#include "stdio.h"

void simple() {
  float a = 1.0;
  printf("%.2f\n", a);
}

void arithmetic() {
  float a = 1.1;
  float b = 2.2;

  printf("\nAddition\n%.2f + %.2f = %.2f\n", a, b, a + b);

  printf("\nSubtraction\n%.2f - %.2f = %.2f\n", a, b, a - b);
  printf("\nMultiplication\n%.2f * %.2f = %.2f\n", a, b, a * b);
  printf("\nDivition\n%.2f / %.2f = %.2f\n", a, b, a / b);
}
int main() {
  simple();
  arithmetic();
  return 0;
}
