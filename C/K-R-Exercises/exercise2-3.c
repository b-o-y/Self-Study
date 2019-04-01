// Travis Henderson
// Last Modified: 16/08/27
// -----------------------------------------------------------
// K&R Exercise 2-3
// Write a function htoi(s) , which converts a string of
// hexadecimal digits (including an optional 0x or 0X ) into
// its equivalent integer value. The allowable digits are 0
// through 9 , a through f , and A through F.
//
// NOTES:
// - Internet actually gave me the idea of converting the
// chars to decimal through subtraction.  I originally made
// two arrays: one with alpha, the other with the corresponding
// decimal value.  And I was going to try to find matches that
// way, but it became too gross for me.
// - All the hex[i]-'char' convert the char to a decimal
// number.
// - Given an invalid input, nothing is done with it. It gets
// skipped.
// - I get, what I think is, a linking error with pow/math.h.
// So I have to compile as: gcc exercise2-3.c -lm
// Not really sure if that's something unique, I'm still
// pretty new to compiling through terminal and using C.
// -----------------------------------------------------------

#include <stdio.h>
#include <math.h> // Contains pow
#define MAX 1000

int htoi(char hex[], int length)
{
  int i, j;
  if (hex[1] == 'x' || hex[1] == 'X')
    {
      i = 2; // The assumption is then the string starts with 0x, skip those.
      j = length-3; // -3 as opposed to -2 because string ends with \n.
    }
  else
    {
      i = 0;
      j = length-1;
    }
  
  int total = 0; // The result of conversion.
  while (i < length)
    {
      if (hex[i] >= 'a' && hex[i] <= 'f')
	{
	  total += (hex[i]-'W') * (pow(16, j));
	  --j;
	  ++i;
	}
      else if (hex[i] >= 'A' && hex[i] <= 'F')
	{
	  total += (hex[i]-'7') * (pow(16, j));
	  --j;
	  ++i;
	}
      else if (hex[i] >= '0' && hex[i] <= '9')
	{
	  if (j != 0) // Pow doesn't do powers of 0.
	    {
	      total += (hex[i]-'0') * (pow(16, j));
	      --j;
	      ++i;
	    }
	  else
	    {
	      total += hex[i]-'0';
	      --j;
	      ++i;
	    }
	}
      else // ERROR.
	{
	  printf("Invalid input. Returning -1\n");
	  total = -1;
	  break;
	}
    }

  return total;
}

int main()
{
  int c, decimal;
  char s[MAX];
  int len = 0;

  while ((c=getchar()) != EOF) // CTRL+d ends program.
    {
      if (c == '\n') // Escape ends input.
	{
	  s[len] = '\n';
	  s[len+1] = '\0';
	  decimal = htoi(s, len);
	  printf("%d\n", decimal);
	  len = 0;
	}
      else
	{
	  s[len++] = c;
	}
    }
}
