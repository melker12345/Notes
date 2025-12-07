#include <stdio.h>

int main(void) {
  // TODO: Cover the following topics for "conditional (ternary) operator":
  // - Syntax: condition ? expression_if_true : expression_if_false
  // - When to prefer ternary over if-else (simple expressions)
  // - Operator precedence and need for parentheses in complex expressions
  // - Return value and type rules (both branches should be compatible)
  // - Nested ternaries (readability concerns)
  // - Using ternary to initialize variables or inline return values
  // - Common bugs: side effects inside branches, missing parentheses
  // - Comparing ternary with macros or inline functions for clarity

  int a = 0;
  int b = 1;

  // This is a simple example of how to produce one true and one false ternary
  // expression.#warning
  a > b ? printf("True!") : printf("False!");
  a < b ? printf("True!") : printf("False!");

  return 0;
}
