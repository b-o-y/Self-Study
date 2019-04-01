// Travis Henderson
// Last Modified: 16/08/29
// -----------------------------------------------------------
// K&R Exercise 2-7
// Write a function invert(x,p,n) that returns x with the n
// bits that begin at position p inverted (i.e., 1 changed
// into 0 and vice versa), leaving the others unchanged.
//
// NOTES:
// - I need to run myself through an example again:
// x = 0011 0101 (53)
//
// If p = 1, then I'd start at the second digit from right
// which is a zero.
//
// If n = 3, then this would encompass, from right to left,
// the second, third, and fourth digit.  This would be 010.
//
// Then 010 inverted is 101.
// x is now equal to 0011 1011 (59)
//
// - I believe a similar method used in 2-6 can be used here.
// x = 0011 0101
// And I want to get to:
// 0011 1010
//
// To accomplish this I can XOR:
// 0011 0101 ^ 0000 1110
//
// 1) Making 0000 1110
// - ~(~0 << n)
// In my example this will give 0000 0111. So I just need to
// shift this over n bytes.
//
// - (~(~0 << n)) << p
// This gives 0000 1110
//
// 2) Now just need to XOR.
// x ^ ((~(~0 << n)) << p)
// -----------------------------------------------------------

#include <stdio.h>

unsigned invert(unsigned x, int p, int n)
{
  return x ^ ((~(~0 << n)) << p);
}

int main()
{
  printf("%d\n", invert(53, 1, 3));
}
