// -----------------------------------------------------------
// Travis Henderson
// Last Modified: 16/08/21
// -----------------------------------------------------------
// K&R Exercise 1-15
// Rewrite the temperature conversion program of Section 1.2
// to use a function for conversion.
// -----------------------------------------------------------

#include <stdio.h>

double convertCtoF(double temp)
{
  temp = (5.0/9.0) * (temp - 32);
  return temp;
}

int main()
{
  printf("64.2 farenheit is %.2f in celsisus\n", convertCtoF(64.2));
}
