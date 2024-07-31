#include <stdio.h>

void squeeze(char s[], int c) {
   int i, j;

   for (i = j = 0; s[i] != '\0'; i++) {
      if (s[i] != c) {
         s[j++] = s[i];
      }
   }
   s[j] = '\0';
}

void extended_squeeze(char s[], char excl[]) {
   int i, j, x;

   for (i = j = 0; s[i] != '\0'; i++) {
      char found = 0;
      for (x = 0; excl[x] != '\0' && !found; x++) {
         if (s[i] == excl[x]) {
            ++found;
         }
      }
      if (!found) {
         s[j++] = s[i];
      }
   }
   s[j] = '\0';
}

int main() {
   char txt[] = "bazinga eerie pewdiepie";

   printf("%s\n", txt);

   // squeeze(txt, 'a');
   extended_squeeze(txt, "aeiou");

   printf("%s\n", txt);

   return 0;
}