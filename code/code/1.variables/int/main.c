#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

int divide() {
  struct winsize ws;

  // Get the terminal size
  ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);

  // Width of the terminal
  int width = ws.ws_col;

  // Print "-" until the line ends
  for (int i = 0; i < width; i++) {
    putchar('-');
  }
  putchar('\n'); // Move to the next line
  putchar('\n'); // Move to the next line

  return 0;
}

void signed_int() {
  printf("\nSigned integers:\n");

  // 2 bytes.
  short int x1 = 32767;
  printf("Short: %d, %lu: bytes\n", x1, sizeof(x1));

  // int is 4 bytes.
  int x = 2147483647;
  printf("int: %d, %lu: bytes\n", x, sizeof(x));

  // 8bytes on 64 bit systems.
  long int x2 = 9223372036854775807L;
  printf("Long: %ld, %lu: bytes\n", x2, sizeof(x2));

  // For 32 bit systems to handle 8byte integers.
  long long int x3 = 9223372036854775807L;
  printf("Long Long: %ld, %lu: bytes\n\n", x3, sizeof(x3));
}

void bases() {
  // In c we integers can have different bases.
  // these are base 2, 8, 10, 16. (binary, octal, decimal, hexadecimal)
  int d = 42;
  int o = 052;
  int x = 0x2a;
  int X = 0X2A;
  int b = 0b101010;

  printf("%d, ", d);
  printf("%d, ", o);
  printf("%d, ", x);
  printf("%d, ", X);
  printf("%d, ", b);
}

void unsigned_int() {
  printf("Unsigned integers:\n");

  // unsigned short 2 bytes
  unsigned short y = 65535;
  printf("unsigned short int: %d, %lu: bytes\n", y, sizeof(y));

  // unsigned int 4 bytes
  unsigned int y2 = 4294967295;
  printf("unsigned int: %u, %lu: bytes\n", y2, sizeof(y2));

  // unsigned long
  unsigned long int y3 = 18446744073709551615UL;
  printf("unsigned long int: %lu, %lu: bytes\n", y3, sizeof(y3));

  // unsigned long long
  unsigned long long int y4 = 18446744073709551615ULL;
  printf("unsigned long long int: %llu, %lu: bytes\n", y4, sizeof(y4));
}

void bugg() {
  printf("This is a bug:\n");
  short int a = 32768;
  printf("short int %d \n", a);
  printf("This is a bug because the size limit of short int is 32767.\n");
  printf("Since a is set to 32768 we get a roll over into the negative.\n");
  printf("This is fixed by decreasing the value of a or using ini instead of "
         "short int.\n");
}

int main() {

  signed_int();
  divide();
  unsigned_int();
  divide();
  bugg();
  bases();
  // TODO: Consider adding examples for:
  // - Integer literals (decimal, octal with 0 prefix, hex with 0x prefix)
  //   Source: https://en.cppreference.com/w/c/language/integer_constant
  // - Integer constants (INT_MAX, INT_MIN, UINT_MAX from limits.h)
  //   Source: https://en.cppreference.com/w/c/header/limits
  // - Integer overflow behavior and undefined behavior
  //   Source: https://en.cppreference.com/w/c/language/behavior
  // - Integer division vs floating point division
  //   Source: https://en.cppreference.com/w/c/language/operator_arithmetic
  // - Integer promotion rules
  //   Source:
  //   https://en.cppreference.com/w/c/language/usual_arithmetic_conversions
  // - Mixing signed and unsigned integers (potential bugs)
  //   Source:
  //   https://en.cppreference.com/w/c/language/conversion#Usual_arithmetic_conversions
  // - Size differences on different platforms (32-bit vs 64-bit)
  //   Source: https://en.cppreference.com/w/c/types/integer#Properties
  // - Using stdint.h types (int8_t, int16_t, uint32_t, etc.) for portability
  //   Source: https://en.cppreference.com/w/c/types/integer

  return 0;
}
