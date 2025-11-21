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
  
  // TODO: Consider adding examples for:
  // - Float precision and representation (IEEE 754)
  // - Precision issues and rounding errors (e.g., 0.1 + 0.2 != 0.3)
  // - Float literals with 'f' suffix (1.0f vs 1.0)
  // - Scientific notation (1.5e3, 2.3E-4)
  // - Special values: NaN (Not a Number), infinity (INFINITY)
  // - Float comparison issues (use epsilon for equality checks)
  // - Float size (typically 4 bytes, 32-bit)
  // - Range limits (FLT_MAX, FLT_MIN from float.h)
  // - Float vs double precision difference
  // - Loss of precision when converting from double to float
  
  return 0;
}
