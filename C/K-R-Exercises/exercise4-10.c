// Travis Henderson
// Last Modified: 16/09/04
// -----------------------------------------------------------
// K&R Exercise 4-10
// An alternate organization uses getline to read an entire
// input line; this makes getch and ungetch unnecessary.
// Revise the calculator to use this approach.
//
// NOTES:
// - Pretty much where ever there was a getch, repalce with
// a line[index++] and wherever there is ungetch I replaced
// with a line[index--]
// - HOWEVER, it does not compile.  I'm running into problems
// with calling getline(line, MAX) as those variables are
// external to all functions, so I'm getting some error
// with mismatch of pointers which I don't understand,
// because I feel like a char array should be of that type
// no matter where it's allocated.
// - Next chapter is about pointers, so maybe I'll get this
// working once I read that chapter.
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
int buf[MAX]; // Buffer for ungetch.
int bufp = 0; // Next free position in buf. External so the value is shared between getch+ungethc.
char line[MAX]; // For getline.
int indexL; // Index for input line.

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
  if (line[indexL] == '\0')
    {
      if (getline(line, MAX) == 0)
      return EOF;
    }
  else
    indexL = 0;

  while((s[0] = c = line[indexL++]) == ' ' || c == '\t')
    ; // Skip any blanks/tabs.
  s[1] = '\0';

  i = 0;
  if (islower(c))
    {
      while (islower(s[++i] = c = line[indexL++]))
	; // See what letters are there.
      s[i] = '\0';
      if (c != EOF)
	line[indexL--]; // Read too far.
      if (strlen(s) > 1)
	return FXN; // Assume that it's a math function, since consecutive letters.
      else
	return c; // It's something else.
    }
  
  if (!isdigit(c) && c != '.' && c != '-')
    return c; // Then it is not a number, return whatever character it may be.

  if (c == '-')
    if(isdigit(c=line[indexL++]) || c == '.')
      s[++i] = c; // Then it is a negative number.
    else
      {
	if (c != EOF)
	  line[indexL--]; // Put it back, it was an operator.
	return '-'; // Subtraction.
      }
  if (isdigit(c)) // While the char is numbers push it on the stack.
    while (isdigit(s[++i] = c = line[indexL++]))
      ;
  if (c == '.') // A distinction of a decimal, what follows should be fractional numbers.
    while (isdigit(s[++i] = c = line[indexL++]))
      ;
  s[i] = '\0';
  
  if (c != EOF)
    line[indexL--];
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

// Makes an array of the input.
int getline(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim-1 && (c=getchar()) != EOF && i != '\n'; ++i)
    s[i] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';
  return i;
}

// Reverse Polish calculator.
int main()
{
  int type, var = 0;
  double op2, op, v;
  char s[MAX];
  double variable[26]; // For the letters of the alphabet.

  for (int i = 0; i < 26; i++)
    variable[i] = 0.0; // Fill it with all zeroes so later can convert the value
  
  while ((type=getop(s)) != EOF)
    {
      switch (type)
	{
	case '=': // Variable letter.
	  pop();
	  if (var >= 'A' && var <= 'Z')
	    variable[var - 'A'] = pop();
	  else
	    printf("Error: variable not recognized\n");
	  break;
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
	  v = pop(); // The most recently printed value.
	  printf("\t%.8g\n", v);
	  break;
	default:
	  if (type >= 'A' && type <= 'Z')
	    push(variable[type - 'A']);
	  else if (type == 'v')
	    push(v);
	  else
	    printf("Error: unknown command %s\n", s);
	  break;
	}
      var = type;
    }
  return 0;
}
