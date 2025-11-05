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
  int a = 3;
  int b = 10;

  float c = b / a;
  printf("\nDivition float by int:\n%f\n", c);

  float d = 3;
  float e = 10;
  float f = e / d;
  printf("Divition float by float:\n%f", f);
}

int main() {
  simple();
  arithmetic();

  div();
  return 0;
}
