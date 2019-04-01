// Travis Henderson
// Last Modified: 16/09/03
// -----------------------------------------------------------
// K&R Exercise 4-2
// Extend atof to handle scientific notation of the form.
//
// NOTES:
// - Because I'm using math.h, I had to compile as:
// gcc exercise4-2.c -lm
// This probably isn't notheworthy, but I'm still not sure
// why not using -lm DOES cause a linking error when all the
// other headers I've used so far don't require it.
// -----------------------------------------------------------

#include <stdio.h>
#include <ctype.h>
#include <math.h>

// Converts string s to double.
double atof(char s[])
{
  double val, power, retVal;
  int i, sign;

  for (i = 0; isspace(s[i]); i++)
    ; // Skip white spaces.
  sign = (s[i] == '-') ? -1 : 1;
  if (s[i] == '+' || s[i] == '-')
    i++;
  for (val = 0.0; isdigit(s[i]); i++)
      val = 10.0 * val + (s[i] - '0');
  if (s[i] == '.')
    i++;
  for (power = 1.0; isdigit(s[i]); i++)
    {
      val = 10.0 * val+ (s[i] - '0');
      power *= 10;
    }
  
  retVal = sign * val / power; // Base number
 
  if (s[i] == 'e') // Sceintific notation.
    i++;
  if (s[i] == '-') // This will determine if decimal goes left/right.
    {
      i++;
      val = 0;
      for (power = 1.0; isdigit(s[i]); i++)
	  val = 10.0 * val + (s[i] - '0');
      return retVal / pow(10, val);
    }
  else if (s[i] == '+')
    {
      i++;
      val = 0;
      for (power = 1.0; isdigit(s[i]); i++)
	  val = 10.0 * val + (s[i] - '0');
      return retVal * pow(10, val);
    }
  else
    {
      val = 0;
      for (power = 1.0; isdigit(s[i]); i++)
	  val = 10.0 * val + (s[i] - '0');
      return retVal * pow(10, val);
    }
  
  return retVal; // If all else just return retVal as is.
}

int main()
{
  char a[] = {'-', '1', '0', '.', '3', 'e', '-', '4'};
  printf("%f\n", atof(a));
}
