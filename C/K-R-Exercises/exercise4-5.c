// Travis Henderson
// Last Modified: 16/09/03
// -----------------------------------------------------------
// K&R Exercise 4-5
// Add access to library functions like sin , exp , and pow.
//
// NOTE:
// - This one gave me some trouble, and I had to go to the
// internet for some help.  The case handling of FXN was
// something I wasn't able to arrive to on my own.
// -----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> // For atof().
#include <ctype.h>
#include <math.h>
#include <string.h>

#define MAX 100 // Max size of operand or operator, val stack, and buffer.
#define NUMBER '0' // Singal that a number was found.
#define FXN '1' // Signal that a math function was found.

int sp = 0; // Next free stack position.
double val[MAX]; // Value stack.
char buf[MAX]; // Buffer for ungetch.
int bufp = 0; // Next free position in buf. External so the value is shared between getch+ungethc.    

// "Clears" the stack.
void clear(void)
{
  sp = 0;
}

// Gets char unless buffer is NOT full, then get from buffer.
int getch(void)
{
  return (bufp > 0) ? buf[--bufp] : getchar();
}

// Read too far into input, save in buffer for later.
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

  i = 0;
  if (islower(c))
    {
      while (islower(s[++i] = c = getchar()))
	; // See what letters are there.
      s[i] = '\0';
      if (c != EOF)
	ungetch(c); // Read too far.
      if (strlen(s) > 1)
	return FXN; // Assume that it's a math function, since consecutive letters.
      else
	return c; // It's something else.
    }
  
  if (!isdigit(c) && c != '.' && c != '-')
    return c; // Then it is not a number, return operator to be used.

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

// For sin, exponent, etc.
void mathFxn(char s[])
{
  double op2;
  if (strcmp(s, "sin") == 0) // Compare input string with fxn strings.
    push(sin(pop()));
  else if (strcmp(s, "pow") == 0)
    {
      op2 = pop();
      push(pow(pop(), op2));
    }
  else if (strcmp(s, "exp") == 0)
    push(exp(pop()));
  else
    printf("Error: unidentified function");
}

// Reverse Polish calculator.
int main()
{
  int type;
  double op2, op;
  char s[MAX];

  while ((type=getop(s)) != EOF)
    {
      switch (type)
	{
	case FXN:
	  mathFxn(s);
	  break;
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
	case 'c': // Clear the stack.
	  clear();
	  break;
	case 'd': // Duplicate the top element of stack.
	  op2 = pop(); // There's the copy.
	  push(op2); // Push it back.
	  push(op2);
	  break;
	case 's': // Swap the first two elements.
	  op = pop();
	  op2 = pop();
	  push(op);
	  push(op2);
	  break;
	case ',': // Print top element.
	  op2 = pop();
	  printf("\t%.8g\n", op2);
	  push(op2);
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
