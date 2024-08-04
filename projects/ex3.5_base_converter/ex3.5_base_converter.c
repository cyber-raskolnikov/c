/*
Exercise 3-5. Write the function itob(n,s,b) that converts the integer n into a base b
character representation in the string s. In particular, itob(n,s,16) formats s as a
hexadecimal integer in s.
*/
#include <stdio.h>
#include <string.h>

#define N_DIGITS 32
#define MAX_LEN_DIGIT 4

void itos(int n, int b, char *s) {
   printf("printf called for %d\n", n);
   int i = 0;
   
   // Handle 0 as a special case
   if (n == 0) {
      s[0] = '0';
      s[1] = '\0';
      return;
   }
   
   // Convert each digit to a character
   while (n > 0 && i < MAX_LEN_DIGIT - 1) {
      int digit = n % 10;
      s[i++] = digit + '0';
      n /= 10;
   }
   
   // Null-terminate the string
   s[i] = '\0';
   
   // Reverse the string
   for (int j = 0; j < i / 2; j++) {
      char temp = s[j];
      s[j] = s[i - 1 - j];
      s[i - 1 - j] = temp;
   }
}

void itob(unsigned int n, char (*s)[MAX_LEN_DIGIT], int b) {
   int remainder;
   int index_digit = 0;
   char digits[] = "0123456789ABCDEF";  // For bases up to 16

   // build the array of digits
   do {
      remainder = n%b;
      if (remainder < 16) {
         s[index_digit][0] = digits[remainder];
         s[index_digit][1] = '\0';
      }
      else
         itos(remainder, b, s[index_digit]);

      index_digit++;
      n /= b;

   } while (n > 0 && n <= N_DIGITS);

   // Reverse the order of digits in the array
   for (int i = 0; i < index_digit / 2; i++) {
      char temp[MAX_LEN_DIGIT];
      strcpy(temp, s[i]);
      strcpy(s[i], s[index_digit - 1 - i]);
      strcpy(s[index_digit - 1 - i], temp);
   }

   // Null-terminate the remaining elements
   for (int i = index_digit; i < N_DIGITS; i++) {
      s[i][0] = '\0';
   }
}

void print_arbitrary_base(const char (*s)[MAX_LEN_DIGIT]) {
   int index_digit, index_base;

   for (index_digit=0; index_digit < N_DIGITS && s[index_digit][0] != '\0'; index_digit++) {
      for (index_base=0; index_base < MAX_LEN_DIGIT && s[index_digit][index_base] != '\0'; index_base++) {
         printf("%c", s[index_digit][index_base]);
      }
      printf(" ");
   }
   printf("\n");
}

int main() {
   // test arbitrary print
   // char s[N_DIGITS][MAX_LEN_DIGIT] = {"1", "15", "0", "0",'\0'};
   // print_arbitrary_base(s);

   char s[N_DIGITS][MAX_LEN_DIGIT];

   itob(15, s, 16);
   print_arbitrary_base(s);

   itob(15, s, 10);
   print_arbitrary_base(s);

   itob(15, s, 2);
   print_arbitrary_base(s);

   itob(40, s, 36);
   print_arbitrary_base(s);

   itob(20, s, 22);
   print_arbitrary_base(s);

   return 0;
}