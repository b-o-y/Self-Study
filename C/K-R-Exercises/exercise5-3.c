// Travis Henderson
// Last Modified: 16/09/06
// -----------------------------------------------------------
// K&R Exercise 5-3
// Write a pointer version of the function strcat that we
// showed in Chapter 2: strcat(s,t) copies the string t to
// the end of s.
//
// NOTES:
// - while (*++s != '\0') == while (*++s)  That is it is true
// until it reaches the end of the string.
// - Same can be said for the second while loop.
// - For the first while loop I was getting tripped up,
// because I was thinking *s should be compared to '\0'
// THEN incremented.  Therfore it should be *s++, but this is
// wrong because once *s++ == '\0', it increments again after
// that.  So the appended string ends up being "abc\0xyz"
// which is all wrong.  Then the reason for the prefix
// increment becomes clear.
// -----------------------------------------------------------

#include <stdio.h>

// Pointer version of stcat.
void strCatPtr(char *s, char *t)
{
  while (*++s) // Find the end of the string.
    ;
  while (*s++ = *t++) // Append the string.
    ;
}

// Concatenate t to the end of s; s must be big enough.
void strCat(char s[], char t[])
{
  int i, j;
  i = j = 0;
  while (s[++i] != '\0') // Find end of s.
    ;
  while ((s[i++] = t[j++]) != '\0') // Append t.
    ;
}

int main()
{
  char a[10] =  {'a', 'b', 'c', '\0'};
  char b[] = "xyz";

  strCatPtr(a, b);
  printf("%s\n", a);
}
