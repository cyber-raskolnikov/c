#include <stdio.h>

int main() {
   int lower_bound, upper_bound, step;
   float fahr, celsius;

   lower_bound = 0;
   upper_bound = 300;
   step = 25;

   fahr = lower_bound;

   printf("\nCONVERSION TABLE FAHRENHEIT -> CELSIUS\n\n");

   while (fahr <= upper_bound) {
      celsius = (5.0/9.0) * (fahr - 32.0);
      printf("%3.0f DEG. FAHR.\t->  %4.1f DEG. CELSIUS\n", fahr, celsius);

      fahr += step;
   }
}