#include <stdio.h>

// - Basic syntax: switch(expression) { case value: ...; break; }
void simple() {
  int day = 3;
  switch (day) {
  case 1:
    printf("Monday");
    break;
  case 2:
    printf("Thusday");
    break;
  case 3:
    printf("Wednesday");
    break;
  case 4:
    printf("Thursday");
    break;
  case 5:
    printf("Friday");
    break;
  case 6:
    printf("Saturday");
    break;
  case 7:
    printf("Sunday");
    break;
  default:
    printf("Day must be an int 1 - 7");
  }
}

int main(void) {
  // TODO: Cover the following topics for "switch statement":

  // - Valid types for switch expression (integral types, enum)

  // - Importance of break statements to prevent fall-through

  // - Intentional fall-through (and adding comments to clarify)

  // - default case for unmatched values

  // - Using enums with switch for readability

  // - Limitations vs if-else (no ranges, only discrete values)

  // - Common bugs: missing break, duplicate case labels, unreachable code

  // - Nested switch vs nested if trade-offs

  return 0;
}
