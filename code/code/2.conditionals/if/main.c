#include <stdio.h>

int main(void) {
  // TODO: Cover the following topics for "if":
  // - What is an if statement? (conditional execution when expression is
  // non-zero)
  // - Basic syntax and use of braces (single statement vs block)
  // - Truthiness in C (0 == false, non-zero == true)
  // - Comparing values (relational and logical operators inside if)
  // - Using if with functions returning status codes
  // - Common pitfalls: using assignment (=) instead of equality (==)
  // - Common pitfalls: dangling else ambiguity without braces
  // - Debugging tip: print or log the evaluated condition

  int a = 2;
  int b = 1;

  if (a > b) {
    printf("a is larger then b");
  }
  return 0;
}
