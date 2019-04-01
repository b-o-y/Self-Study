// Travis Henderson
// Last Modified: 16/09/04
// -----------------------------------------------------------
// K&R Exercise 4-12
// Adapt the ideas of printd to write a recursive version of
// itoa; that is, convert an integer into a string by calling
// a recursive routine.
//
// NOTES:
// - Pretty cool how it turns out recusrsively, don't even
// need reverse.
// - How it works:
// -->itoa(34, s)
// 34/10 = 3
// -->itoa(3, s)
// Go to else, not negative so nothing is done.
// Add to the array '3', terminate the array: '3' '\0', i = 1.
// -->iota(34, s)
// Go back to where the function was last called which is
// the following argument inside the first if.
// Now move outside the conditional to add '4' at index 1.
// i gets incremented, terminate string: '3' '4' '\0'
// - abs is used when pushing into the array because with
// chars, it's negative representation is just a '-' so it's
// sign is trivial till the end as exhibited with the else
// that is only entered when the integer division == 0.
// -----------------------------------------------------------

#include <stdio.h>
#include <stdlib.h> // Not math.h because we're working on ints.
#define MAX 1000

// Converts n to characters in s.
void itoa(int n, char s[])
{
  static int i;
  if (n / 10)
    itoa(n / 10, s);
  else
    {
      i = 0;
      if (n < 0)
	s[i++] = '-';
    }
  s[i++] = abs(n) % 10 + '0';
  s[i] = '\0';
}

int main()
{
  char a[MAX];
  int b = 34;

  itoa(b, a);
  printf("%s\n", a);
}
