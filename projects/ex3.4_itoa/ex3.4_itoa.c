#include <stdio.h>
#include <limits.h>

/* reverse: reverses a null-terminated ('\0') string (char[]) in-place. [temporal: O(n), spatial: O(1) (in-place)] */
void reverse(char s[]) {
   int i, len;
   int start, end;

   // calculate length of null-terminated char 'string'
   len = 0;
   for (i=0; s[i] != '\0'; i++) {
      len++;
   }

   // reverse string using two indices as pointers moving towards each other
   start = 0;
   end = len-1;

   while(start < end) {
      // swap chars using aux char variable
      char aux = s[end];
      s[end] = s[start];
      s[start] = aux;

      // move pointers towards each other
      ++start;
      --end;
   }
}

/* 
   itoa: convert n to characters in s
   n is an integer, allows for negatives
   copied from chapter 3
 */
void itoa(int n, char s[]) {
   int i, sign;

   if ((sign = n) < 0) /* record sign */
      n = -n; /* make n positive */

   i = 0;
   do { /* generate digits in reverse order */
      s[i++] = n % 10 + '0'; /* get next digit */
   } while ((n /= 10) > 0); /* delete it */

   if (sign < 0)
      s[i++] = '-';
   s[i] = '\0';

   reverse(s);
}

/* 
   itoa: convert n to characters in s
   n is an integer, allows for negatives
 */
void mod_itoa(int n, char s[]) {
   int i, sign;
   char is_edge_case;

   if (n == INT_MIN)
      is_edge_case = 1;
   else
      is_edge_case = 0;

   if ((sign = n) < 0) /* record sign */
      if (is_edge_case)
         n = -(n+1);
      else
         n = -n; /* make n positive */

   i = 0;
   do { /* generate digits in reverse order */
      s[i++] = n % 10 + '0'; /* get next digit */
   } while ((n /= 10) > 0); /* delete it */

   if (sign < 0)
      if (is_edge_case)
         //this is safe because since 2**n is never divisible by 5 -> it cannot be divisible by 10.
         s[0] += 1;
      s[i++] = '-';

   s[i] = '\0';
   reverse(s);
}

int main() {
   // char s[] = "HeLLo";
   // printf("%s\n", s);
   // reverse(s);
   // printf("%s\n", s);
   char buff[128];

   printf("max integer number: %d\n", INT_MAX);
   itoa(INT_MAX, buff);
   printf("max integer to array func: %s\n", buff);

   printf("min integer number: %d\n", INT_MIN);
   itoa(INT_MIN, buff);
   printf("min integer to array func (has a bug): %s\n", buff);

   printf("\n\tin a two complement machine (most of them),\n\
    the range of numbers that can be expressed in a n-bits integer\n\
    is [2**(n-1) , 2**(n-1) - 1], so we cannot 'n = -n;' with\n\
    the most negative number of the range\n\n");

   printf("min integer number: %d\n", INT_MIN);
   mod_itoa(INT_MIN, buff);
   printf("min integer to array modified func (solved): %s\n", buff);

   return 0;
}