// Travis Henderson
// Last Modified: 16/09/02
// -----------------------------------------------------------
// K&R Exercise 3-6
// Write a version of itoa that accepts three arguments
// instead of two. The third argument is a minimum field
// width; the converted number must be padded with blanks on
// the left if necessary to make it wide enough.
//
// NOTES:
// - Both reverse and itoa end in s[i] = '\0', which probably
// isn't needed, but I made the conscious choice to leave
// it for the sake of modularity.  For example if I were
// to remove the reverse function, and didn't have itoa end
// in s[i] '\0' it would cause problems.
// -----------------------------------------------------------

#include <stdio.h>
#define LEN 1000

// -------- reverse --------
// Reverses an array. n
// is the length of the
// contents of the array.
// -------------------------
void reverse(char s[], int n, int blanks)
{
  int toSwap, index;
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
  
  index = n;
  while (blanks > 0) // Add the remaining padding to the string.
    {
      s[index++] = ' ';
      --blanks;
    }

  s[index] = '\0';
}

// Converts an integer to a character string.
void itoa(int n, char s[], int width)
{
  int i, sign, pad, min;
  min = width;
  
  if (n < 0)
    sign = -1;
  else
    sign = 1;
  
  i = 0;
  do
    { // I think by multiplying a smaller # by a negative will allow accuracy.
      s[i++] = sign * (n % 10) + '0';
      --width;
    } while ((n/=10) != 0);

  if (sign < 0)
    {
      s[i++] = '-';
      --width;
    }

  if (i < min) // Check that there is room is for padding.
    { 
      pad = width - (width/2); // The difference of padding remaining.
      width /= 2; // Ideally half of spaces are on the left, the other half on the right.
      while (width > 0)
	{
	  s[i++] = ' ';
	  --width;
	}
      s[i] = '\0';
      reverse(s, i, pad);
    }
  else
    {
      printf("Minimum padding exceeded.\n");
      s[i] = '\0';
      reverse(s, i, -1); // -1, so no blanks can be added, number will be shown as is.
    }
}

int main()
{
  int a = 4562;
  char b[LEN];
  int c = 5;
  itoa(a, b, c);
  printf("%s\n", b);
}
