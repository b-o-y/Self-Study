// Travis Henderson
// Last Modified: 16/08/29
// -----------------------------------------------------------
// K&R Exercise 2-9
// In a two's complement number system, x &= (x-1) deletes the
// rightmost 1-bit in x . Explain why. Use this observation
// to write a faster version of bitcount.
//
// NOTES:
// - To answer the previous question, I'll work through an
// example.
// - Say x = 9.  In binary this is 0000 1001. The statement
// x &= (x-1) becomes
// 9 &= 8 or 0000 1001 &= 0000 1000
// This means I'm & x and reassigning it which results in:
// 0000 1000.  Just like the question stated, it deleted the
// rightmost bit.
//
// - Another example: 96 = 0110 0000, 95 = 0101 1111
// 0110 0000 &= 0101 1111 becomes 0100 0000
//
// - I wish I could state it more rigourously as a mathematical
// proof or something, but it appears that the difference
// between x and x-1, is the right most bit is always the
// opposite value, hence why it gets deleted when &.
// -----------------------------------------------------------

#include <stdio.h>

/* Changed bitcount by decrementing x by 1 everytime.
Slightly more efficient with one less conditional.  */
// -------- bitcount ---------
// counts 1 bits in x.
// ---------------------------
int bitcount(unsigned x)
{
  int b;

  for (b = 0; x != 0; x &= x-1)
      b++;
  return b;
}

int main()
{
  printf("%d\n", bitcount(9));
}
