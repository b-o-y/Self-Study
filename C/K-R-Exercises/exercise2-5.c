// Travis Henderson
// Last Modified: 16/08/28
// -----------------------------------------------------------
// K&R Exercise 2-5
// Write the function any(s1,s2) , which returns the first
// location in a string s1 where any character from the string
// s2 occurs, or -1 if s1 contains no characters from s2 .
// (The standard library function strpbrk does the same job
// but returns a pointer to the location.)
// -----------------------------------------------------------

#include <stdio.h>

// ---------- any ----------
// Returns the index of s1
// where the first matching
// character occurs between
// s1 and s2.
// -------------------------
int any(char s1[], char s2[])
{
  int i, j;
  int characterFound = 0;  // My "boolean" for if a match was found.
  
  for(i = 0; s2[i] != '\0'; ++i)
    {
      if(characterFound) // A match was already found, job done.
	break;
      for(j = 0; s1[j] != '\0'; ++j)
	if(s1[j] == s2[i])
	  {
	    characterFound = 1;
	    break; // Match was found break out of most inner for loop.
	  }
    }
  if (!characterFound) // No match was found.
    j = -1;
  
  return j; // j is what iterates through s1.
}

int main()
{
  char a[] = "aikatsu";
  char b[] = "krist";

  printf("%d\n", any(a, b));
}
