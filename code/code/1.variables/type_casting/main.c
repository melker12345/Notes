#include <stdio.h>

void simple(){
  int a = 0;
  int b = 1;

  // This is a Implicit type casting since we assign a defined value to another type.
  float num = a;
  
  int c = (int)num;

  printf("%f\n", num);
  printf("%d\n", c);
}

int main() {
    // TODO: Cover the following topics:
    // 1. What is type casting? (converting one data type to another)
    // 2. Implicit type conversion (automatic)
    // 3. Explicit type casting (manual, using (type))
    // 4. Casting between numeric types (int to float, etc.)
    // 5. Casting with pointers
    // 6. Loss of precision in casting
    // 7. Common bugs: unsafe casts, loss of data, undefined behavior
   simple(); 
    return 0;
}

