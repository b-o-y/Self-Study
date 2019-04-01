// Travis Henderson
// Last Modified: 16/09/02
// -----------------------------------------------------------
// K&R Exercise 3-5
// Write the function itob(n,s,b) that converts the integer n
// into a base b character representation in the string s. In
// particular, itob(n,s,16) formats s as a hexadecimal integer
// in s .
//
// NOTES:
// - Originally I took itoa, and just replaced all instances
// of 10 with 'n'.  However, this doesn't work for negative
// numbers or hex.
// - So instead I went back to doing n = -n, which should
// be adequate.  I'm not going to address negative binary
// numbers.
// -----------------------------------------------------------

#include <stdio.h>
#define LEN 1000

// -------- reverse --------
// Reverses an array. n
// is the length of the
// contents of the array.
// -------------------------
void reverse(char s[], int n)
{
  int toSwap;
  int end = n-1;
  int begin = 0;

  while(begin <= end) // Swap the array in place starting from both ends.
    {
      toSwap = s[begin];
      s[begin] = s[end];
      s[end] = toSwap;

      --end;
      ++begin;
    }
}

// Converts an integer to a character string.
void itob(int n, char s[], int b)
{
  int i, sign, j;
  if (n < 0)
    {
      sign = -1;
      n = -n; // Not the most proper, but oh well...
    }
  else
    sign = 1;
  
  i = 0;
  do
    {
      j = n % b;
      if (j <= 9)
	s[i++] = j + '0';
      else
	s[i++] = j + 'a' - 10; // For hex.
    } while ((n/= b) != 0);

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s, i);
}

int main()
{
  int a = -10;
  char b[LEN];
  int c = 16;
  itob(a, b, c);
  printf("%s\n", b);
}
