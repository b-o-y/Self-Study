// Travis Henderson
// Last Modified: 16/09/08
// -----------------------------------------------------------
// K&R Exercise 4-1
// Write the function strindex(s,t) which returns the position
// of the rightmost occurrence of t in s , or -1 if there is
// none.
// -----------------------------------------------------------

#include <stdio.h>

int strindex(char s[], char t[])
{
  int i = 0; // Index for t.
  int j = 0; // Index for s.
  int k = -1; // Index where t occurs in s.
  
  while (t[i] != '\0')
    {
      while (s[j] != '\0')
	{
	  if (t[i] == s[j])
	    if (k < j) // Only want the right most index, the greatest one.
	      k = j;
	  ++j;
	}
      j = 0; // Reset j for the nested while.
      ++i;
    }
  return k;
}

int main()
{
  char a[] = "piano";
  char b[] = "violin";
  char c[] = "flute";
  
  printf("%d\n", strindex(a, b));
  printf("%d\n", strindex(a, c));
}
