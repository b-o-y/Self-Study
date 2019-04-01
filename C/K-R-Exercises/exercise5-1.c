// Travis Henderson
// Last Modified: 16/09/05
// -----------------------------------------------------------
// K&R Exercise 5-1
// As written, getint treats a + or - not followed by a digit
// as a valid representation of zero. Fix it to push such a
// character back on the input.
//
// NOTES:
// - The for loop in getint works by terminating when c is
// no longer a char.  That is one could input a number
// 5 \n
// \n would terminate that for loop. Or
// 5 4 3 2 1 \n
// Would fill the array with those numbers in that order.
//
// - Now addressing the actual question, I have no idea what
// the authors statement means.  + or - NOT followed by a digit
// is treated as a valid representation of zero....
// When I input '-g', it so happens that the first digits are
// stored as zero and the rest are gibberish numbers, but
// I don't think -g is being stored as zero and this is more
// of a reflection of the undefined behavior.
// - What I've implemented does:
//               -h \n
// This prints an error, forgets h, and puts '-' into the
// buffer, so if one were to input 5, then the entry in the
// array would end up being -5.
// - To accomodate my implementation, I had to change the
// for loop in main to decrement if the return value from
// get int is ever 'e'.  This is so the array gets filled
// in sequence {1, 2, ...5}
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
int getint(int *pn)
{
  int c, sign, other;

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

  for (*pn = 0; isdigit(c); c = getch())
    *pn = 10 * *pn + (c - '0');
  *pn *= sign;

  if (c != EOF)
    ungetch(c);
  
  return c;
}

int main()
{
  int n, array[MAX], retVal;
  
  for (n = 0; n < MAX && (retVal = getint(&array[n])) != EOF; n++)
    if (retVal == 'e')
      n--;

  for (int i = 0; i < n; i++)
    printf("%d ", array[i]);
  printf("\n");
}
