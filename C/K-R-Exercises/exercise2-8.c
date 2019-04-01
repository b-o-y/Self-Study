// Travis Henderson
// Last Modified: 16/08/29
// -----------------------------------------------------------
// K&R Exercise 2-8
// Write a function rightrot(x,n) that returns the value of
// the integer x rotated to the right by n positions.
//
// NOTES:
// - I'm led to believe that rotating is just shifting bits,
// but when they fall off the edge, they show up on the other
// side.
//
// - Example:
// 0101 1110 (94), n = 3.
// 1st shift) 0010 1111
// 2nd shift) 1001 0111
// 3rd shift) 1100 1011 (203)
//
// - I have to explain everything to myself again:
//
// 1) x >> n
// - In my example 0101 1110 becomes 0000 1011 with the above
// statement.
// - I need 1100 1011, though.
// - I can do this by  0000 1011 ^ 1100 0000.
//
// 2) Making 1100 0000
// - I can make the statement:
// ~(~0 << n)
// - I've used this in previous examples. With n = 3, I end up
// with 0000 0111.
// - Still trying to get 0000 0110. I can do this with x and &.
// 0101 1110 & 0000 0111 = 0000 0110
// x & (~(~0 << n))
// - Now, 0000 0110 needs to be shifted to 1100 0000
// (x & (~(~0 << n))) << (8- n)
// I chose 8-n as the shift because I in this example a shift
// of 5 gives the correct answer. 8-3 = 5.  Then I did
// 0d111, n = 6, and this statement held true.
//
// 3) (x >> n) ^ (x & (~(~0 << n))) << (8 - n)
// 0000 1011 ^ 1100 0000 = 1100 1011
// -----------------------------------------------------------

#include <stdio.h>

// I'm really not sure how to handle moving
// bits if n is greater than 8. 
// So here's my incomplete answer for now.
unsigned rightrot(unsigned x, int n)
{
  if (n < 0)
    {
      printf("Negative input, returning -1.");
      return -1;
    }
  else if (n <= 8)
    return (x >> n) | (x & (~(~0 << n))) << (8 - n);
  else
    return (x >> n) | (x & (~(~0 << n))) << (n - 8);
}

int main()
{
  printf("%d\n", rightrot(94, 3));
}
