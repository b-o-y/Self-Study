// Travis Henderson
// Last Modified: 16/08/30
// -----------------------------------------------------------
// K&R Exercise 3-3
// Write a function expand(s1,s2) that expands shorthand
// notations like a-z in the string s1 into the equivalent
// complete list abc...xyz in s2 . Allow for letters of either
// case and digits, and be prepared to handle cases like a-b-c
// and a-z0-9 and -a-z . Arrange that a leading or trailing -
// is taken literally.
//
// NOTES:
// - I have no idea what it means in asking how to handle
// -a-z.
// -----------------------------------------------------------

#include <stdio.h>
#define LEN 1000

void expand(char s1[], char s2[])
{
  int i = 0;
  int j = 0;
  int c;
  while ((c=s1[i++]) != '\0')
    {
      if (s1[i] == '-' && s1[i+1] >= c) // 2nd conditional makes sure to count up
	{
	  i++; // This avoids putting '-' into the set.
	  while (c < s1[i])
	    s2[j++] = c++; // Expand the set into the other array.
	}
      else // Put the characters into the array.
	s2[j++] = c;
    }
  s2[j] = '\0';
}
	  
int main()
{
  int c;
  int i = 0;
  char s[LEN];
  char x[LEN];
  
  while ((c=getchar()) != EOF && i <= LEN)
    {
      if (c == '\n')
	{
	  s[i] = '\0';
	  expand(s, x);
	  printf("%s\n", x);
	  i = 0;
	}
      // All these extra conditionals to make sure proper input.
      else if (c >= 'a' && c <= 'z')
	s[i++] = c;
      else if (c >= '0' && c <= '9')
	s[i++] = c;
      else if (c == '-')
	s[i++] = c;
      else
	printf("Invalid input.\n");
    }
}
