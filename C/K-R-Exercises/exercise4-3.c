// Travis Henderson
// Last Modified: 16/09/03
// -----------------------------------------------------------
// K&R Exercise 4-3
// Given the basic framework, it's straightforward to extend
// the calculator. Add the modulus (%) operator and provisions
// for negative numbers.
//
// NOTES:
// - Input must be separated by ' '.  For example:
// 8 9 * (enter)
// 89* is not 72.
// - Not  sure if the author expected to cast doubles to ints
// or not, but I just used fmod for modulo.
// -----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> // For atof().
#include <ctype.h>
#include <math.h>

#define MAX 100 // Max size of operand or operator, val stack, and buffer.
#define NUMBER '0' // Singal that a number was found.

int sp = 0; // Next free stack position.
double val[MAX]; // Value stack.
char buf[MAX]; // Buffer for ungetch.
int bufp = 0; // Next free position in buf. External so the value is shared between getch+ungethc.

int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c)
{
  if (bufp >= MAX)
    printf("ungetch: too many characters\n");
  else
    buf[bufp++] = c;
}

int getop(char s[])
{
  int i, c;

  while((s[0] = c = getch()) == ' ' || c == '\t')
    ; // Skip any blanks/tabs.
  s[1] = '\0';
  
  if (!isdigit(c) && c != '.' && c != '-')
    return c; // Then it is not a number, return operator to be used.

  i = 0;
  if (c == '-')
    if(isdigit(c=getch()) || c == '.')
      s[++i] = c; // Then it is a negative number.
    else
      {
	if (c != EOF)
	  ungetch(c); // Put it back, it was an operator.
	return '-'; // Subtraction.
      }
  if (isdigit(c)) // While the char is numbers push it on the stack.
    while (isdigit(s[++i] = c = getch()))
      ;
  if (c == '.') // A distinction of a decimal, what follows should be fractional numbers.
    while (isdigit(s[++i] = c = getch()))
      ;
  s[i] = '\0';
  
  if (c != EOF)
    ungetch(c);
  /* At this point, the calculator read something that wasn't a number. 
Throw it in the buffer so that it can be recalled later.  */
  
  return NUMBER;
}

// push f onto value stack.
void push(double f)
{
  if (sp < MAX)
    val[sp++] = f;
  else
    printf("Error: stack is full, cannot push %g\n", f);
}

// pop and return TOP value from stack.
double pop(void)
{
  if (sp > 0)
    return val[--sp];
  else
    {
      printf("Error: stack empty\n");
      return 0.0;
    }
}

// Reverse Polish calculator.
int main()
{
  int type;
  double op2;
  char s[MAX];

  while ((type=getop(s)) != EOF)
    {
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
	case '-': // It's a stack, respect the order.
	  op2 = pop();
	  push(pop() - op2);
	  break;
	case '/':
	  op2 = pop();
	  if (op2 != 0.0)
	    push(pop() / op2);
	  else
	    printf("Error: zero divisor\n");
	  break;
	case '%':
	  op2 = pop();
	  if (op2 != 0.0)
	    push(fmod(pop(), op2));
	  else
	    printf("Error: zero modulo divisor\n");
	  break;
	case '\n':
	  printf("\t%.8g\n", pop());
	  break;
	default:
	  printf("Error: unknown command %s\n", s);
	  break;
	}
    }
  return 0;
}
