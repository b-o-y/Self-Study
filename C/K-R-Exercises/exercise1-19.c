// Travis Henderson
// Last Modified: 16/08/21
// -----------------------------------------------------------
// K&R Exercise 1-19
// Write a function reverse(s) that reverses the character
// string s . Use it to write a program that reverses its
// input a line at a time.
// -----------------------------------------------------------

#include <stdio.h>
#define MAXLINE 1000 // Maximum input.

// ----------------- reverseLine -----------------
// This method reads in chars to be put into an
// array to make a string. EOF and \n are the
// delimiters on the chars, then \0 is the
// delimiter for the string itself. Then the
// array is swapped in place to give the reverse
// of the string.
//------------------------------------------------
int reverseLine(char s[], int lim)
{
  int c, i, newL;
  newL = 0;
  // c is the individual chars, and i is for indices of the array.
  for (i = 0; i < lim - 1 && (c=getchar()) != EOF && c != '\n'; ++i)
    {
      s[i] = c;
    }

  if (c == '\n') // This lets me know if the text ended in a new line.
    {
      newL = 1;
    }

  // REVERSE
  int toSwap;
  int end = i-1;
  int begin = 0;
  while(begin <= end) // Swap the array in place starting from both ends.
    {
      toSwap = s[begin];
      s[begin] = s[end];
      s[end] = toSwap;

      --end;
      ++begin;
    }
  
  if (newL == 1) // Add the new line if it's there.
    {
      s[i] = '\n';
      ++i;
    }

  s[i] = '\0'; // Terminate the string.  

  return i;
}

int main()
{
  int len;
  char line[MAXLINE];

  while ((len = reverseLine(line, MAXLINE)) > 0)  // If len is  zero, then there is no line to recored.
    {
      printf("%s", line);
    }

  return 0;
}
