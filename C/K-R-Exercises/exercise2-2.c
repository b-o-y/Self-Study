// Travis Henderson
// Last Modified: 16/08/26
// -----------------------------------------------------------
// K&R Exercise 2-2
// Write a loop equivalent to the for loop above without
// using && or || .
//
// NOTES:
// - I think it's referring to this:
// i < lim-1 && (c=getchar()) != '\n' && c != EOF
// - I can't remember if 'break' has come up yet or not in
// the text, so hopefully this is the solution the author was
// looking for.
// -----------------------------------------------------------

#include <stdio.h>
#define MAX 1000

int getLine(char s[])
{
  int i, c;
  for (i = 0; i < MAX-1; ++i)
    {
      /* I check these conditionals within the loop, rather
than within the argument of the for loop. */
      if ((c=getchar()) == EOF)
	break;
      if (c == '\n')
	break;
      s[i] = c;
    }

  if (c == '\n')
      s[i++] = c;
  s[i] = '\0';

  return i;
}

int main()
{
  int len; // Current line length.
  char line[MAX]; // String.
  while ((len = getLine(line)) > 0) // A string of length zero terminaztes.
    {
      printf("%s", line);
    }
}

