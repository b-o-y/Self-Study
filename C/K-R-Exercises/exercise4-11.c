// Travis Henderson
// Last Modified: 16/09/04
// -----------------------------------------------------------
// K&R Exercise 4-11
// Modify getop so that it doesn't need to use ungetch. Hint:
// use an internal static variable.
//
// NOTES:
// - Working on the assumption that the buffer will never
// need to store more than 1 letter.
// - Replaced all ungetch with lastChar = c, since it's
// static the that last character will always be there
// the next time the function it's called, it doesn't go away
// after being called.
// - ngetch shouldn't ever be used for how this is implemented
// because the buffer should always be zero since I'm using
// lastChar as a buffer rather than an array.
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
  static int lastChar = 0;

  if (lastChar == 0) // See if there's anything in buffer, otherwise move on.
    c = getch();
  else
    {
      c = lastChar;
      lastChar = 0;
    }
  
  while((s[0] = c)  == ' ' || c == '\t')
    c = getch(); // Skip any blanks/tabs, DISTINCTION have to get a char each time.
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
	  lastChar = c; // Put it back, it was an operator.
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
    lastChar = c;
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
