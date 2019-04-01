// Travis Henderson
// Last Modified: 16/09/04
// -----------------------------------------------------------
// K&R Exercise 4-14
// Define a macro swap(t,x,y) that interchanges two arguments
// of type t. (Block structure will help.)
//
// NOTES:
// - Chapter was kind of vague on how macros work. For example,
// when I change the argument swap(double, a, b) and leave
// a and b as ints...would that ever be a problem? It works
// fine, but I know that necesarily mean that it is okay.
// - I'll have to ask someone and find out.
// -----------------------------------------------------------

#include <stdio.h>
#define swap(t, x, y) \
  {\
    t other; /* Make it of type t */ \
    other = x; \
    x = y; \
    y = other; \
  } \
  
int main()
{
  int a = 5;
  int b = 3;
  swap(int, a, b);
  printf("a: %d, b: %d.\n", a, b);
}
