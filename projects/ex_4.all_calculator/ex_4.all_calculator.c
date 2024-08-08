/*
Exercise 4-3. Given the basic framework, it's straightforward to extend the calculator. Add
the modulus (%) operator and provisions for negative numbers.
Exercise 4-4. Add the commands to print the top elements of the stack without popping, to
duplicate it, and to swap the top two elements. Add a command to clear the stack.
*/

#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>

#define MAXOP 100  /* max size of operand or operator */
#define NUMBER '0' /* signal that a number was found */
#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */
char buf[BUFSIZE]; /* buffer for ungetch */
int bufp = 0;      /* next free position in buf */

int getop(char[]);
void push(double);
double pop(void);
int getch(void);
void ungetch(int);

void print_value_stack() {
   for (int i=0; i<sp; i++) {
      printf("%f ", val[i]);
   }
   printf("\n");
}

int is_parseable_num(char c) {
   int next_char_lookup = getch();
   ungetch(next_char_lookup);

   char is_negative_num = (c == '-' && isdigit(next_char_lookup)) ? 1 : 0;

   return (isdigit(c) || c == '.' || is_negative_num);
}

/* getop: get next character or numeric operand */
int getop(char s[]) {
   // print_value_stack();
   int i, c;

   while ((s[0] = c = getch()) == ' ' || c == '\t')
      ;

   if (!is_parseable_num(c)) {
      s[1] = '\0';
      return c; /* not a number */
   }

   i = 0;
   /* collect negative sign */
   if (c == '-') {
      s[0] = c;
   }

   while (isdigit(s[++i] = c = getch()))
         ;
   
   if (c == '.') /* collect fraction part */
      while (isdigit(s[++i] = c = getch()))
         ;
   
   s[i] = '\0'; 

   if (c != EOF) {
      ungetch(c);
   }
   return NUMBER;
}

/* get a (possibly pushed-back) character */
int getch(void) {
   return (bufp > 0) ? buf[--bufp] : getchar();
}

/* push character back on input */
void ungetch(int c) { 
   if (bufp >= BUFSIZE)
      printf("ungetch: too many characters\n");
   else
      buf[bufp++] = c;
}

/* push: push f onto value stack */
void push(double f)
{
   if (sp < MAXVAL)
      val[sp++] = f;
   else
      printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
   if (sp > 0)
      return val[--sp];
   else
   {
      printf("error: stack is empty\n");
      return 0.0;
   }
}

/* reverse Polish calculator */
int main() {
   int type;
   double op2;
   char s[MAXOP];
   while ((type = getop(s)) != EOF)
   {
      if (sp > 5) return 0;
      switch (type)
      {
      case NUMBER:
         push(atof(s));
         break;
      case '+':
         push(pop() + pop());
         break;
      case '*':
         push(pop() * pop());
         break;
      case '-':
         op2 = pop();
         push(pop() - op2);
         break;
      case '/':
         op2 = pop();
         if (op2 != 0.0)
            push(pop() / op2);
         else
            printf("error: zero divisor\n");
         break;
      case '%':
         op2 = pop();
         if (op2 != 0.0)
            push((int) pop() % (int) op2);
         else
            printf("error: zero divisor in modulo op\n");
         break;
      case '\n':
         printf("\t%.8g\n", pop());
         break;
      default:
         printf("error: unknown command %s\n", s);
         break;
      }
   }
   return 0;
}