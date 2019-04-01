// Travis Henderson
// Last Modified: 16/08/24
// -----------------------------------------------------------
// K&R Exercise 1-22
// Write a program to ``fold'' long input lines into two or
// more shorter lines after the last non-blank character that
// occurs before the n -th column of input. Make sure your
// program does something intelligent with very long lines,
// and if there are no blanks or tabs before the specified
// column.
//
// NOTE:
// -New lines are made after the 20th character/column.
// -If there are no spaces or tabs, then the next line is
// made with a trailing '-'.
// -I tried experimenting with external variables, not really
// sure if I did it correctly/appropriately.
// -----------------------------------------------------------

#include <stdio.h>
#define MAX 1000 // Length of array.
#define NL 20 // Length of a line.

char other[MAX];
char line[MAX];

// -------- fold --------
// Gives a string with a
// newline every 20,
// characters. Gives a
// hyphen if it doesn't
// end in space or tab.
//-----------------------
void fold(char s[])
{
  extern char other[];
  int i = 0; // Iterates through s.
  int j = 0; // Iterates through other.
  int colCount = 0; // Column count.

  while ((s[i] != '\0') && (j < MAX-1))
    {
      if (colCount == NL)
	{
	  if (s[i] == ' ' || s[i] == '\t') // Then there will be a natural newLine.
	    other[j++] = '\n';
	  else // Otherwise a hyphen is needed too show continuity.
	    {
	      other[j++] = '-';
	      other[j++] = '\n';
	    }
	  colCount = 0; // Reset colCount for new line.
	}
      
      if (s[i] == '\t') // Tabs are worth more characters.
	{
	  colCount += 8;
	  other[j++] = s[i];
	}
      else if(s[i] == '\n')
	{
	  colCount = 0; // Reset colCount, because new line.
	  other[j++] = s[i];
	}
      else
	{
	  ++colCount;
	  other[j++] = s[i];
	}
      ++i;
    }
  other[j] = '\0';
}
	         
// -------- getLine --------
// Makes a char array/string
// of user input.
// -------------------------
int getLine(char s[])
{
  int c, i;
  for (i = 0; (i < MAX-1) && ((c=getchar()) != EOF) && (c != '\n'); ++i)
    s[i] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';

  return i;
}

int main()
{
  int len = 0;
  extern char line[], other[];
  while ((len = getLine(line)) > 0) // Stings of length 0 terminate program.
    {
      fold(line); // Fold the line.
      printf("%s", other); // And print the result.
    }
}
