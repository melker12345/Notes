#include <stdio.h>

void char_as_ascii() {
  // This is how the most basic char is defined:
  //
  char a = 'a';
  printf("%c\n", a);

  // You can define chars as integer by utelizing ASCII.
  char b = -66;
  printf("ascii 66 = %c\n", b);

  char z = 90;
  printf("ascii 90 = %c\n\n", z);

  // This loops through the ascii characters.
  for (int i = 0; i < 255; i++) {
    if (i == 32) {
      printf("--END OF NON PRINTABLE CHARS--\n");
    };
    printf("ascii %d = %c\n", i, i);
  };
  printf("Swedish characters: ÄÅÖ\n\n");

  // You also have signed and unsigned chars.
  // These goes from 0 to 255.
  printf("Unsigned Character:\n\n");
  unsigned char x = 1;
  printf("%c", x);
}

int main() {
  char_as_ascii();
  // TODO: Consider adding examples for:
  // - Char as integer (ASCII values, can be used in arithmetic)
  // - Signed vs unsigned char (implementation-defined, typically -128 to 127 or
  // 0 to 255)
  // - Character literals vs string literals ('a' vs "a")
  // - Escape sequences (\n, \t, \', \", \\, \0, etc.)
  // - Printing char as character (%c) vs as integer (%d)
  // - Character arrays and strings (char arrays with null terminator)
  // - EOF (End of File) constant
  // - Character encoding (ASCII, extended ASCII)
  // - Char arithmetic (e.g., 'a' + 1 = 'b')
  // - Character classification functions (isalpha, isdigit, etc. from ctype.h)
  // - Char size (typically 1 byte, CHAR_BIT from limits.h)

  return 0;
}
