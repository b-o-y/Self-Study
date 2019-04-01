// Travis Henderson
// Last Modified: 16/08/21
// -----------------------------------------------------------
// K&R Exercise 1-17
// Write a program to print all input lines that are longer
// than 80 characters.
//
// NOTE: I didn't do anything that different from 1-16. Just
// added a conditionaly to check if the length of the chars
// is more than 80.  I put the conditional later in the
// program so it doesn't immediately terminate if user inputs
// less than 80 characters.
// -----------------------------------------------------------

#include <stdio.h>
#define MAXLINE 1000 // Maximum input.

// ------------------- copy -------------------
// Copy just copies the current char array to
// the array that will contain the longest
// line of chars.
// -------------------------------------------
void copy(char to[], char from[])
{
  int i = 0;
  while ((to[i] = from[i]) != '\0')
    ++i;
}

// ------------------- getLine -------------------
// This method reads in chars to be put into an
// array to make a string. EOF and \n are the
// delimiters on the chars, then \0 is the
// delimiter for the string itself.
//-----------------------------------------------
int getLine(char s[], int lim)
{
  int c, i;
  // c is the individual chars, and i is for indices of the array.
  for (i = 0; i < lim - 1 && (c=getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;

  if (c == '\n')
    {
      s[i] = c;
      ++i;
    }
  s[i] = '\0';
  
  if (i == (MAXLINE-1)) // If 'i' is the max amount, then it's possible not the whole line was recorded.
    while ((c=getchar()) != '\n')
      ++i; // Increment 'i' until end of the string for full lenght, full string is not saved in array, though.

  return i;
}

int main()
{
  int len; // Current line length.
  int max; // Maximum length thus far.
  char line[MAXLINE]; // Current input line.
  char longest[MAXLINE]; // Longest line.

  max = 0;
  while ((len = getLine(line, MAXLINE)) > 0)  // If len is  zero, then there is no line to recored.
    {
      if (len > max)  // A new max was found.
	{
	  max = len;
	  if (max > 80) // Only makes a string if it has more than 80 characters.
	    copy(longest, line); // Copy that new longest line to a char array/string.
	}
    }
  if (max > 80) // The longest string/char array is then printed.
    printf("Longest string was: %s\n", longest);
  else
    printf("None of the strings was over 80.  Max was %d.\n", max);

  return 0;
}
