// Travis Henderson
// Last Modified: 16/09/08
// -----------------------------------------------------------
// K&R Exercise 5-6
// Rewrite appropriate programs from earlier chapters and
// exercises with pointers instead of array indexing. Good
// possibilities include getline (Chapters 1 and 4), atoi,
// itoa, and their variants (Chapters 2, 3, and 4), reverse
// (Chapter 3), and strindex and getop (Chapter 4).
//
// NOTES:
// - I'm only doing the exercesies explicitly stated, going
// to pass on getop because there's a lot of associated code
// that I don't want to deal with and it appears (I could
// be wrong) to be more just replacing s[i++] with *s++.
//
// - For getLine, I do not need to make a copy of s because
// C is pass by value, I can do anything I want to s, and
// line will still point to the same address.
//
// - If 'b' is a pointer, there seems to be no difference
// between *++b vs ++b.  At least, in the context of the fxn
// reverse, I assume I'd see no difference used elsewhere.
// I just wanted to note that, because it surprised me.
// Actually, I thought about it, if there's an assignment,
// then a dereference has to be used.
// *++b = c will work, ++b = c will NOT work.
//
// - strlen works on pointers.
// -----------------------------------------------------------

#include <stdio.h>
#include <string.h>
#define MAXLINE 1000

// Read a line into s, return length.
int getLine(char *s, int lim)
{
  int c, i = 0;

  while (i < lim-1 && (c=getchar()) != EOF && c != '\n')
    {
      *s++ = c;
      ++i;
    }
  if (c == '\n')
    {
      *s++ = c;
      ++i;
    }
  *s = '\0';
  
  return i;
}

// Convert s to integer. I didn't get that creative with this one,
// just replaced all instances of s[i] with *s.
int atoi(char *s)
{
  int i, n = 0;
  for (i = 0; *s >= '0' && *s <= '9'; *++s)
      n = 10 * n + (*s - '0');
  return n;
}

// Revese a string in place.
void reverse(char s[])
{
  int c;
  char *endS = s + strlen(s) - 1; // This gives the end of the string.

  while (s < endS)
    {
      c = *s;
      *s = *endS;
      *endS = c;

      ++s;
      --endS;
    }
}

// Convert n to characters in s.
void itoa(int n, char *s)
{
  int sign;
  char *copyS = s; /* IMPORTANT: by the end of all this s points to the end of it's string, 
but reverse fxn assumes it points at the beginning!  Hence the need for this copy. */
  if ((sign = n) < 0)
    n = -n;
  do
    {
      *s++ = n % 10 + '0'; // Get next digit.
    } while ((n /= 10) > 0); // Delete it.
  if (sign < 0)
    *s++ = '-';
  *s = '\0';
  reverse(copyS);
}

// Returns the position of the rightmost occurence of
// t in s, or -1 if there is none.
int strindex(char *s, char *t)
{
  int i = 0; // Index for t.
  int occurence = -1; // Index where t occurs in s.
  char *beginS = s; // Pointer for beginning of string s.
  
  while (*t != '\0')
    {
      while (*s != '\0')
	{
	  if (*t == *s)
	      occurence = i;
	  ++s;
	}
      s = beginS; // Have s point to it's beginning again.
      ++t; // Move onto the next index of t.
      ++i; // Keep track of what index t is at.
    }
  
  return occurence;
}

int main()
{
  int len;
  char line[MAXLINE];

  while ((len = getLine(line, MAXLINE)) > 0)
      printf("%s", line);

  char num[] = "644";
  printf("%d\n", atoi(num));

  char a[MAXLINE];
  itoa(-326, a);
  printf("%s\n", a);

  char b[] = "onna";
  char c[] = "otoko";
  printf("%d\n", strindex(b, c));
}
