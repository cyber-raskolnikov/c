#include <stdio.h>
#include <limits.h>

/* Write a function invert(x,p,n) that returns x with the n bits that begin at
position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged. */
int bit_switcher(x, p, n) {
   return 0;
}

int main() {
   int n, n_switched;
   
   n = 7;
   n_switched = bit_switcher(n);

   // printf("%d", n_switched);
   printf("%d\n", sizeof(int));
   printf("%d\n", INT_MAX);

   return 0;
}