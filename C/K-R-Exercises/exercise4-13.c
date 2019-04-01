// Travis Henderson
// Last Modified: 16/09/04
// -----------------------------------------------------------
// K&R Exercise 4-13
// Write a recursive version of the function reverse(s) , which
// reverses the string s in place.
//
// NOTES:
// - Just replaced the while loop with a function call with
// changing argument.
// -----------------------------------------------------------

#include <stdio.h>

void reverse(char s[], int begin, int end)
{
  int toSwap;

  if (begin <= end)
    {
      toSwap = s[begin];
      s[begin] = s[end];
      s[end] = toSwap;
      reverse(s, ++begin, --end);
    }
}

int main()
{
  char s[] = "piano";
  reverse(s, 0, 4);
  printf("%s\n", s);
}
