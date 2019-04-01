// Travis Henderson
// Last Modified: 16/08/28
// -----------------------------------------------------------
// K&R Exercise 2-4
// Write an alternative version of squeeze(s1,s2) that
// deletes each character in s1 that matches any character in
// the string s2 .
//
// NOTES:
// - Originally I had the line
// s1[k] = '\0' ONLY at the end of the altSqueeze method.
// This was clearly wrong, because while letters were being
// deleted in the nested loop for s1, it's physical size in C
// was never shrinking correctly because '\0' was never
// capping the string at the end of each iteration whenever
// the string got shortened.
// -----------------------------------------------------------

#include <stdio.h>

// ---------- altSqueeze ----------
// Deletes all occurences of s2
// in s1.  Uses nested loops to
// iterate and compare through
// each char of each string.
// --------------------------------
void altSqueeze(char s1[], char s2[])
{
  int i, j, k;
  
  for(i = 0; s2[i] != '\0'; ++i)
    {
      for(j = k = 0; s1[j] != '\0'; ++j)
	if(s1[j] != s2[i]) // If it isn't a match...
	  s1[k++] = s1[j]; // Then keep the char in the string.
      /* Must terminate the end of the string after each iteration since
it is potentially shrinking every time a match is found. */
      s1[k] = '\0';
    }
}

int main()
{
  char a[] = "yakisoba";
  char b[] = "sukiyaki";

  altSqueeze(a, b);
  printf("%s\n", a);
}
