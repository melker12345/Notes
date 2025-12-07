#include <stdio.h>

int main(void) {
  // TODO: Cover the following topics for "if-else":
  // - Basic if-else syntax and control flow
  // - else-if ladder for multiple conditions
  // - Ordering of conditions (most specific first)
  // - Using return/continue/break inside if-else
  // - Readability (indentation, braces, avoiding deeply nested logic)
  // - Common bugs: missing else causing unexpected fall-through logic
  // - Using enums or constants to make conditions clearer
  // - Testing strategy: cover each branch with separate inputs
  int a = 0;
  int b = 1;

  if (a) {
    printf("a");
  }
  if (b) {
    printf("b");
  } else {
    printf("no a nor b");
  }
  return 0;
}
