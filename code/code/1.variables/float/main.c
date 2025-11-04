#include "stdio.h"

void simple() {
  float a = 1.0;
  printf("%.2f\n", a);
}

// simple arithmetic
void arithmetic() {
  float a = 1.1;
  float b = 2.2;

  printf("\nAddition\n%.2f + %.2f = %.2f\n", a, b, a + b);

  printf("\nSubtraction\n%.2f - %.2f = %.2f\n", a, b, a - b);
  printf("\nMultiplication\n%.2f * %.2f = %.2f\n", a, b, a * b);
  printf("\nDivition\n%.2f / %.2f = %.2f\n", a, b, a / b);
}

void div() {
  int a = 2;
  float b = 3.3;

  float c = a / b;
  printf("%f", c);
}

int main() {
  simple();
  arithmetic();

  div();
  return 0;
}
