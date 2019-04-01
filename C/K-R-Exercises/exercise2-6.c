// Travis Henderson
// Last Modified: 16/08/28
// -----------------------------------------------------------
// K&R Exercise 2-6
// Write a function setbits(x,p,n,y) that returns x with the
// n bits that begin at position p set to the rightmost n bits
// of y , leaving the other bits unchanged.
//
// -->>THE FOLLOWING IS AN EXPLANATION OF WHAT I DID, MORE FOR
// MYSELF THAN OTHERS.
// -->> EXPLANATION IS LONG WINDED, AND REASONING FOR ACTIONS
// ONLY APPEARS AT THE END RESULT.
//
// NOTES:
// - This is another one I had to go to the internet for help.
// I didn't quite understand what was being asked.
// - I think it's saying if I have
// x=0011 1100 (60)
// y=0000 1101 (13)
// Then if p=2, I would be looking at the third digit from
// right in x which is a 1.
// If n=3, that would then encompass three 1s in x. That
// is the third, fourth, and fifth digits from right.
// Then in y I would be looking at the first three digits from
// right: 010.  010 is going to replace 111 in x.
// The result would be:
// x=0010 1000 (40)
// - That's how I interpreted this problem at least.
// ------------------------------------------------------------
// So I'll work through my example.
// What I want to first accomplish is setting the chosen bits
// in x to zero, I can do that by & it like so:
// 0011 1100 & 1110 0011 = 0010 0000
//
// 1)  ~0 << n
// I thought would make a string of bits of all
// 1s of n length, instead it gives a negative number. -16
// Solution to that is:
// ~(~0 << n).
// As to why, I don't quite understand two complements right
// now and how negatives are represented in C, that's beyond
// the scope of what I'm trying to learn right now.  All I
// I know is it's a convenient of way counting for computers.
// So now we have 7 or 0111.
//
// 2) ~(~0 << n) << p
// This step then adds p amount of zeroes to the right side.
// So 0111 becomes 0001 1100.
//
// 3) ~(~(~0 << n) << p)
// Recall I need 1110 0011, which is the inverse of 0001 1100.
// 0010 0000 has been achieved now.
//
// 4) x & ~(~(~0 << n) << p)
// 0011 1100 & 1110 0011 = 0010 0000
// I have masked the selected bits in x now.
//
// What comes next is getting right most n digits of y, so
// I can "copy+paste" them into x, where I just masked.
//
// y =  0000 1101
// From this I want (n=3), 101.  If I OR them into the blank
// spot in x, I can do this.  So I need:
// 0001 0100
//
// 4) ~(~0 << n)
// Same step again, my end goal is to clear all bits in y
// except the n rightmost bits.
// My result of this step is 0111.
//
// 5) y & ~(~0 << n)
// 0000 1101 & 0000 0111 = 0000 0101
// Almost there.
//
// 6) (y & ~(~0 << n)) << n
// Recall n = 3.  So I'm going to shift 101 over 3 places,
// putting THREE 0s to the right of it.  The result:
// 0010 1000
//
// 7) (x & ~(~(~0 << n) << p)) | ((y & ~(~0 << n)) << n)
// This big mess says:
// 0010 0000 | 0010 1000 = 0010 1000
// -----------------------------------------------------------

#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y)
{
  return (x & ~(~(~0 << n) << p)) | ((y & ~(~0 << n)) << n);
}

int main()
{
  printf("%d\n", setbits(60, 2, 3, 13));
}
