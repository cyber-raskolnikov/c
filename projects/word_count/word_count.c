#include <stdio.h>

# define IN 1 /* inside a word */
# define OUT 0 /* outside a word */

#define BUFFER_SIZE 15

int main() {
   char state;
   int current_char, n_char, n_words, n_lines, word_buffer_idx;

   char word_buffer[BUFFER_SIZE];

   state = OUT;
   n_char = n_words = n_lines = 0;

   while((current_char = getchar()) != EOF) {
      ++n_char;

      if (current_char == '\n') {
         ++n_lines;
      }

      if (current_char == ' ' || current_char == '\t' || current_char == '\n') {
         state = OUT;

         if (word_buffer_idx > 0) {
            for (int i = 0; i < word_buffer_idx; ++i) {
               printf("%c", word_buffer[i]);
            }
               printf("\n");
         }
      }
      else if (state == OUT) {
         state = IN;
         ++n_words;

         word_buffer_idx = 0;
         word_buffer[word_buffer_idx] = current_char;
         ++word_buffer_idx;

      }
      else {
         word_buffer[word_buffer_idx] = current_char;
         ++word_buffer_idx;
      }
   }

   printf("Nº of lines: %d\n", n_lines);
   printf("Nº of words: %d\n", n_words);
   printf("Nº of chars: %d\n", n_char);

}