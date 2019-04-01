// Travis Henderson
// Last Modified: 16/09/02
// -----------------------------------------------------------
// K&R Exercise 3-4
// In a two's complement number representation, our version of
// itoa does not handle the largest negative number, that is,
// the value of n equal to -(2^(wordsize-1)). Explain why not.
// Modify it to print that value correctly, regardless of the
// machine on which it runs.
//
// NOTES:
// - A two's complement represents negative numbers by taking
// the positive binary representation, inverting it, then
// adding one.
// Example:
// 1 = 001, inverted = 110, add one = 111, therefore -1 = 111
// 2 = 010, inverted = 101, add one = 110, therefore -2 = 110
//
// - Additionally a two's complement system only encompasses
// numbers from -(2^(n-1)) to +(2^(n-1)-1).
// So if n = 8, that is -128 to 127.
// - In itoa, the input number is multiplied by -1.  This is
// a problem because if n=8, and the number were -128, then
// multiplying by -1 would be +128, which is out of range.
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
void itoa(int n, char s[])
{
  int i, sign;
  if (n < 0)
    sign = -1;
  else
    sign = 1;
  
  i = 0;
  do
    { // I think by multiplying a smaller # by a negative will allow accuracy.
      s[i++] = sign * (n % 10) + '0';
    } while ((n/=10) != 0);
  
  /*if ((sign = n) < 0)
    n = -n;
  i = 0;
  do
    {
      s[i++] = n % 10 + '0';
      } while ((n /= 10) > 0);*/

  if (sign < 0)
    s[i++] = '-';
  s[i] = '\0';
  reverse(s, i);
}

int main()
{
  int a = -23;
  char b[LEN];
  itoa(a, b);
  printf("%s\n", b);
}
