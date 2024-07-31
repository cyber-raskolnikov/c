#include <stdio.h>
#include <limits.h>

void reverse_array(int arr[], int size)
{
    for (int i = 0; i < size/2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[size - 1 - i];
        arr[size - 1 - i] = temp;
    }
}

void print_bit_repr(unsigned int x) {
   int buff[1200];
   int i = 0;

   // generate reversed representation
   while (x > 0) {
      if (x & 1) {
         buff[i] = '1';
      }
      else {
         buff[i] = '0';
      }
      x >>= 1;
      ++i;
   }
   buff[i] = '\0';

   // reverse array
   reverse_array(buff, i);

   // printing the obtained representation
   for(i = 0; buff[i] != '\0'; ++i) {
      printf("%c", buff[i]);
   }
   printf("\n");
}

/* getbits: get n bits from position p */
unsigned int getbits(unsigned int x, int p, int n) {
   return (x >> (p+1-n)) & ~(~0 << n);
}

/* Write a function invert(x,p,n) that returns x with the n bits that begin at
position p inverted (i.e., 1 changed into 0 and vice versa), leaving the others unchanged. */
unsigned int bit_switcher(x, p, n) {
   printf("Running bit_switcher for number %d\n", x);
   unsigned int upper_mask, lower_mask, mask, reverse_mask, outer_res, inner_res;

   upper_mask = (~0U) >> (8*sizeof(int) - (p+1));//(p+1-n);
   lower_mask = (~0U) << (p-n+1);
   mask = upper_mask & lower_mask; /* 0000 1111 0000*/
   reverse_mask = ~mask; /* 1111 0000 1111 */

   outer_res = x & reverse_mask; /* xxxx 0000 xxxx */
   inner_res = ~x & mask; /* 0000 iiii 0000 */

   print_bit_repr(x);

   printf("upper mask\n");
   print_bit_repr(upper_mask);
   printf("lower mask\n");
   print_bit_repr(lower_mask);
   printf("mask\n");
   print_bit_repr(mask);
   printf("reverse mask\n");
   print_bit_repr(reverse_mask);
   printf("outer_res\n");
   print_bit_repr(outer_res);
   printf("inner_res\n");
   print_bit_repr(inner_res);
   printf("result\n");
   print_bit_repr((outer_res | inner_res));

   return outer_res | inner_res;
}

int main() {

   // printf("%lu\n", sizeof(int));
   // printf("%d\n", INT_MAX);
   // printf("%u\n", getbits(7, 2, 2));
   
   printf("%u\n\n", bit_switcher(31, 3, 3));
   printf("%u\n", bit_switcher(15, 2, 2));
   printf("%u\n", bit_switcher(10, 2, 2));

   return 0;
}