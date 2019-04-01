// Travis Henderson
// Last Modified: 16/09/08
// -----------------------------------------------------------
// K&R Exercise 5-5
// Write versions of the library functions strncpy , strncat ,
// and strncmp , which operate on at most the first n characters
// of their argument strings. For example, strncpy(s,t,n) copies
// at most n characters of t to s .
//
// NOTES:
// - Description of methods from the appendix:
// char *strncpy(s, ct, n) copy at most n characters of string
// ct to s; return s.  Pad with '\0''s if ct has fewer than
// n characters.
//
// char *strncat(s, ct, n) concatenate at most n characters
// of string ct to string s, terminate s with '\0'; return s.
//
// int strncmp(cs, ct, n) compare at most n characters of
// string cs to string ct: return <0 if cs<ct, 0 if cs ==ct.
// or >0 if cs>ct.
// -----------------------------------------------------------

#include <stdio.h>
#include <string.h>

// ----------- strnCmp ---------------
// Compares the first n chars of cs
// to ct to see which has a higher
// decimal/ascii value.
// -----------------------------------
int strnCmp(char *cs, char *ct, int n)
{
  int i = 0;
  while (i < n && *cs == *ct)
    {
      if (*cs == '\0' || *ct == '\0') // This could have gone in the while conditional, but I feel this is more readable.
	break;
      else
	{
	  *++cs;
	  *++ct;
	}
    }
  if (*cs < *ct)
    return -1;
  else if (*ct < *cs)
    return 1;
  else
    return 0;
}

// -------- strnCat --------------
// Adds first n chars of ct to
// s.  If n>ct, nothing happens.
// It just appends all of ct.
// -------------------------------
char *strnCat(char *s, char *ct, int n)
{
  int i = 0;
  char *beginS = s, *beginCt = ct;

  while (*++beginS)
    ; // Get to the end of s.
  while (i < n)
    {
      if (*beginCt) // As long as it doesn't point to '\0' it is true.
	  *beginS++ = *beginCt++;
      else
	break;
      ++i;
    }
  *beginS = '\0'; // End the string.

  return s;
}
  

// ----------------------- strnCpy ----------------------------
// Copies the first n letters of ct to the beginning of
// s, replacing all letters in s up to n.
// I feel that having copies of the pointers is necessary so
// that the pointers in the argument never change what they're
// pointing at. Therfore the pointers called in main won't point
// to something else after the method call.
//
// "Pad with '\0''s if ct has fewer than n characters." To me
// this means that s just becomes ct then.
// ------------------------------------------------------------
char *strnCpy(char *s, char *ct, int n)
{
  int i = 0;
  char *beginS = s, *beginCt = ct; // Mark beginning of strings.
  while(i < n)
    {
      if (*beginCt) // True until *beginCt == '\0'.
	*beginS++ = *beginCt++;
      else
	break;
      ++i;
    }
  
  return s;
}

int main()
{
  char a[] = "fried";
  char b[] = "boiled";
  char c[] = "rice";
  char d[] = "boiedrize";
  
  printf("%s\n", strnCpy(a, b, 3));
  printf("%s\n", strnCat(a, c, 20));
  printf("%d\n", strnCmp(a, d, 8));
}
