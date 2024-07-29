#include <stdio.h>

int main() {
   int c;
   long c_counter, l_counter;

   c_counter = l_counter = 0;

   while ((c = getchar()) != EOF) {
      ++c_counter;
      if (c == '\n') {
         ++l_counter;
      }
   }

   printf("Nº of words: %ld\n", c_counter);
   printf("Nº of lines: %ld\n", l_counter);
}