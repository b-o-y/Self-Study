// Travis Henderson
// Last Modified: 16/08/22
// -----------------------------------------------------------
// K&R Exercise 1-20
// Write a program detab that replaces tabs in the input with
// the proper number of blanks to space to the next tab stop.
// Assume a fixed set of tab stops, say every n columns.
// Should n be a variable or a symbolic parameter?
// -----------------------------------------------------------

#include <stdio.h>
#define NUMSP 10 // Number of spaces, width of columns/tabs.

int main()
{
  int c, i;
  i = 0; // i keeps track of what column the character is at.
  while ((c=getchar()) != EOF)
    {
      if (i>=NUMSP || c=='\n')  // Reset the increment for every new word and 10th space.
	i = 0;
      if (c==' ' || c=='\t')
	while(i <= NUMSP)
	  {
	    putchar(' ');  // Insert the tab stops.
	    ++i;
	  }
      else
	{
	  putchar(c);
	  ++i;
	}
    }
}
