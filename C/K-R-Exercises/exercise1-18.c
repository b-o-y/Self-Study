// Travis Henderson
// Last Modified: 16/08/21
// -----------------------------------------------------------
// K&R Exercise 1-18
// Write a program to remove trailing blanks and tabs from
// each line of input, and to delete entirely blank lines.
//
// NOTE: Not sure what it means by deleting entirely blank
// lines.  Once again, I just added a conditional. The spaces
// and tabs count as characters, for whatever that is worth
// in this implementation.
// -----------------------------------------------------------

#include <stdio.h>
#define MAXLINE 1000 // Maximum input.

// ------------------- getLine -------------------
// This method reads in chars to be put into an
// array to make a string. EOF and \n are the
// delimiters on the chars, then \0 is the
// delimiter for the string itself.
//-----------------------------------------------
int getLine(char s[], int lim)
{
  int c, i;
  i = 0;
  // c is the individual chars, and i is for indices of the array.
  for (int j = 0; i < lim - 1 && (c=getchar()) != EOF && c != '\n'; ++j)
    if (c != ' ' && c != '\t') // If it's a space or tab, don't enter it.
      {
	s[i] = c;
	++i;
      }

  if (c == '\n')
    {
      s[i] = c;
      ++i;
    }
  s[i] = '\0';

  return i;
}

int main()
{
  int len; // Current line length.
  char line[MAXLINE]; // Current input line.

  while ((len = getLine(line, MAXLINE)) > 0)  // If len is  zero, then there is no line to recored.
    {
      printf("%s", line); // Prints the line with no spaces of any kind.
    }

  return 0;
}
