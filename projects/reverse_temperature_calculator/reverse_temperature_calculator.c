#include <stdio.h>

#define LOWER 0
#define UPPER 300
#define STEP 20

int main() {
   int fahr;

   printf("\nCONVERSION TABLE FAHRENHEIT -> CELSIUS\n\n");

   for (fahr = UPPER; fahr >= LOWER; fahr -= STEP) {
      printf("\t%3d  ->  %6.1f\n", fahr, 5.0/9.0 * (fahr - 32.0));
   }
}