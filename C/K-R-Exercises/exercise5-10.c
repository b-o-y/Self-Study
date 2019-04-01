// Travis Henderson
// Last Modified: 16/09/11
// -----------------------------------------------------------
// K&R Exercise 5-10
// Write the program expr , which evaluates a reverse Polish
// expression from the command line, where each operator or
// operand is a separate argument. For example:
// expr 2 3 4 + *
// evaluates 2 * (3+4)
//
// NOTES:
// - This is based off the implementation from exercise  4-3
// and 4-something.
// - I was not clever enough to come up with this solution.
// - I THINK I understand the implementation, though. My
// explanation is given in the comments where the new lines
// were added, only main was changed.
// - This calculator has a lot of functionality, but was only
// tested for the exercise problem.
// - IMPORTANT: It must be inputted in terminal as
// 2 3 4 + '*'
// Without the apostrophes, it recognizes it as some other
// character and kind of goes crazy and fills up the buffer.
// -----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> // For atof().
#include <ctype.h>
#include <math.h>
#include <string.h>

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

// Pushes a whole string on the stack.
void ungets(char s[])
{
  int length = strlen(s);

  while (length > 0)
    ungetch(s[--length]);
  /* By using ungetch the whole string is pushed onto the buffer, then
when getop is called it should draw all it's characters from the buffer
until the buffer is empty. */
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
int main(int argc, char *argv[])
{
  //int type;
  double op2;
  char s[MAX];

  while (--argc > 0) // For the length of the string.
    {
      ungets(" "); /* Why this line, though...? When removed, I have to hit enter twice 
in terminal for a calculation. Must have to do with an escape sequence? */
      ungets(*++argv); // Push string to the buffer.
      switch (getop(s)) // Then essentially draw all the chars out to be evaluated.
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
	default:
	  printf("Error: unknown command %s\n", s);
	  break;
	}
    }
  printf("\t%.8g\n", pop());
  return 0;
}
