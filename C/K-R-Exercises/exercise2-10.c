// Travis Henderson
// Last Modified: 16/08/29
// -----------------------------------------------------------
// K&R Exercise 2-10
// Rewrite the function lower , which converts upper case
// letters to lower case, with a conditional expression
// instead of if-else.
//
// NOTES:
// - (conditions) ? T : F;
// That's basically all there is to it, I think.
// -----------------------------------------------------------

#include <stdio.h>

// -------- lower --------
// converts letters to
// lower case.
// -----------------------
int lower(int c)
{
  /*  if (c >= 'A' && c <= 'Z')
    return c + 'a' - 'A';
  else
    return c;*/
  return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}

int main()
{
  int a = 'g';
  printf("%c\n", lower(a));
}
