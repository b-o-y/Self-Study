// Travis Henderson
// Last Modified: 16/08/25
// -----------------------------------------------------------
// K&R Exercise 1-24
// Write a program to determine the ranges of char , short ,
// int , and long variables, both signed and unsigned , by
// printing appropriate values from standard headers and by
// direct computation. Harder if you compute them: determine
// the ranges of the various floating-point types.
// -----------------------------------------------------------

#include <stdio.h>
#include <limits.h> // Contains max values of dataypes as contants.
#include <float.h> // Float maxes.

int main()
{
  printf("----------------------------------------\n");
  printf("Max/min values of signed data types\n");
  printf("char: %d / %d\n", CHAR_MAX, CHAR_MIN);
  printf("short: %d / %d\n", SHRT_MAX, SHRT_MIN);
  printf("int: %d / % d\n", INT_MAX, INT_MIN); // d = signed int
  printf("long: %ld / %ld\n", LONG_MAX, LONG_MIN); // ld = long signed
  printf("----------------------------------------\n");

  printf("----------------------------------------\n");
  printf("Max values of unsigned data types\n");
  printf("char: %d\n", UCHAR_MAX);
  printf("short: %d\n", USHRT_MAX);
  printf("int: %u\n", UINT_MAX); // u = unsigned
  printf("long %lu\n", ULONG_MAX); // lu = long unsigned
  printf("----------------------------------------\n");

  printf("----------------------------------------\n");
  printf("Max/min mavlues of float data types.\n");
  printf("float: %f / %f\n", FLT_MAX, FLT_MIN);
  printf("double: %g / %g\n", DBL_MAX, DBL_MIN);
  printf("----------------------------------------\n");

  printf("Computationally:\n");
  printf("Max unsigned char: %d\n", ((unsigned char) ~0));
  /*  I had to look this up, and could not find it out on my own.
Using the complement operator on zero changes all bits to 1 which 
would be a maximum value. */
  
  printf("Max signed char: %d\n", (char)((unsigned char) ~0 >> 1));
  /* Then in this instance, after changing every bit to a 1, the
following bit operation clears the sign bit.  Then the unsigned
 is cast to a signed char. */

  printf("Min signed char: %d\n", ~(char)((unsigned char) ~0 >> 1));
  /* Following the same steps/logic already in place, use the complement
     operator on the max to get the min. */
  /* The same applies for all the other data types, except float, hence
why I left them out.  Not sure how to computationally find the max/min
of floats, though. */
}

