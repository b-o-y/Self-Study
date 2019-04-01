// Travis Henderson
// Last Modified: 16/09/06
// -----------------------------------------------------------
// K&R Exercise 5-2
// Write getfloat , the floating-point analog of getint . What
// type does getfloat return as its function value?
//
// NOTES:
// - I didn't change much, just added a part for decimal
// places, and in the for loops changed 10 to 10.0.
// - What type does getfloat return? I believe it's just
// int, unless I am misunderstanding something here. Because
// it'll either return EOF or whatever that last ASCII
// character was which are ints.
// -----------------------------------------------------------

#include <stdio.h>
#include <ctype.h>
#define MAX 6

char buf[MAX]; // Buffer for ungetch.
int bufp = 0; // Next free poistion in buf.

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

// Get next integer from input into *pn.
int getint(double *pn)
{
  int c, sign, other;
  double magnitude;

  while (isspace(c=getch())) // Skip white spaces.
    ;

  if(!isdigit(c) && c != EOF && c != '+' && c != '-')
    {
      ungetch(c); // It is not a number.
      return 0;
    }

  sign = (c == '-') ? -1 : 1;
  
  if (c == '+' || c == '-') // If char was a sign, get next one.
    {
      other = c;
      if(!(isdigit(c=getch()))) // Now I'll check if next char is digit.
	{
	  if (c != '\n') // This might be a cheap fix, but without it it prints two times, because '\n' is always the next char.
	    printf("error: not digit, returning 'e'.\n");
	  ungetch(other); // c gets ignored, and other goes to the buffer for next char.
	  return 'e';
	}
    }

  for (*pn = 0; isdigit(c); c = getch()) // This is for the integer part.
    *pn = 10.0 * *pn + (c - '0');
  *pn *= sign;

  if (c == '.') // Fractional part of the number.
    c = getch();
  for (magnitude = 1.0; isdigit(c); c = getch())
    {
      *pn = 10.0 * *pn + (c - '0');
      magnitude *= 10;
    }
  *pn /= magnitude; // Give it the correct magnitude.

  if (c != EOF)
    ungetch(c);
  
  return c;
}

int main()
{
  int n, retVal;
  double array[MAX];
  
  for (n = 0; n < MAX && (retVal = getint(&array[n])) != EOF; n++)
    if (retVal == 'e')
      n--;

  for (int i = 0; i < n; i++)
    printf("%.2f ", array[i]);
  printf("\n");
}
