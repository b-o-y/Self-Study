// Travis Henderson
// Last Modified: 16/09/07
// -----------------------------------------------------------
// K&R Exercise 5-4
// Write the function strend(s,t) , which returns 1 if the
// string t occurs at the end of the string s , and zero
// otherwise.
//
// NOTES:
// - I interpreted this to mean:
// char a[] = "fried"
// char b[] = "ed"
// This would return 1 because ed is the last part of string
// a.
// -----------------------------------------------------------

#include <stdio.h>

// Assumes s is always bigger than t.
int strEnd(char *s, char *t)
{
  char *startS = s, *startT = t; // Mark the beginning of the strings.
  int i = 0, j = 0, retVal = 1,  difference;

  while (*++startT) // Find how many indexes t has.
    ++i;
  while (*++startS) // Find how many indexes s has.
    ++j;

  difference = j - i; // Length difference between two strings.
  i = 0;
  while (i < difference) // Get s to start at the length of t.
    {
      *++s;
      ++i;
    }
  
  while(*s)
    {
      if (*s++ != *t++)
      {
	retVal = 0;
	break;
      }
    }
  
  return retVal;
}

int main()
{
  char a[] = "fried";
  char b[] = "ed";
  char c[] = "rief";
  
  printf("%d\n", strEnd(a, b));
  printf("%d\n", strEnd(a, c));
}
