// Travis Henderson
// Last Modified: 16/08/25
// -----------------------------------------------------------
// K&R Exercise 1-23
// Write a program to remove all comments from a C program.
// Don't forget to handle quoted strings and character
// constants properly. C comments don't nest.
//
// NOTES:
// - This probably sounds stupid, I'm assuming this exercise
// isn't literal.  So, what I've written is a program that
// looks for any // and discards all input until it reaches
// a new line.  Then if there is /* it discards everything
// until it reaches a */
// - I also decided to make the character '`' to be the end
// of a C program, because \n wouldn't do since C programs
// have a lot of new lines.
// - Not that I think this is particularly important, but for
// the sake of clarity, the int returned from getLine does
// NOT count comments and backslashes
// -----------------------------------------------------------

#include <stdio.h>
#define MAX 1000 // Length of array.

// --------- getLine ---------
// Returns a char arrray of
// an input while neglecting
// any input using the C
// commenting convention.
// ---------------------------
int getLine(char s[])
{
  int c = 0;
  int d = 0;
  int i = 0;
  while ((i < MAX-1) && ((c=getchar()) != EOF) && (c != '`'))
    {
      if (c == '/')
	{
	  c = getchar(); // Get the next character to see what kind of comment it is.
	  if (c  == '*') // It's a block comment.
	    {
	      while (0 == 0) // INFINITE LOOP, sounds bad, but it SHOULD break.
		{             // so everything in the block comment can be discarded.
		  if ((c=getchar()) == '*')
		    if((c=getchar()) == '/')
		      break;
		}
	    }
	  else if (c == '/') // It's an inline comment.
	    {
	      while ((c=getchar()) != '\n')
		{
		  // Do nothing, cycle through comment till new line.
		}
	      // End of comment was reached insert c.
	      s[i++] = c;
	    }
	  else
	    s[i++] = c;
	}
      
      else
	{
	  s[i++] = c;
	}
    }
  s[i] = '\0';

  return i;
}

int main()
{
  int len = 0;
  char line[MAX];

  while ((len = getLine(line)) > 0) // Just doing CTRL+d twice will terminate program.
    {
      printf("%s", line);
    }
}
