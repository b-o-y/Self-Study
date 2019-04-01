// Travis Henderson
// Last Modified: 16/08/30
// -----------------------------------------------------------
// K&R Exercise 3-2
// Write a function escape(s,t) that converts characters like
// newline and tab into visible escape sequences like \n and
// \t as it copies the string t to s . Use a switch . Write
// a function for the other direction as well, converting
// escape sequences into the real characters.
// -----------------------------------------------------------

#include <stdio.h>
#define LEN 1000

/* Turns tabs and escape sequences into visible
   characters */
void escape(char s[], char t[])
{
  int i = 0;
  int j = 0;
  
  while (t[i] != '\0' && j <= LEN)
    {
      switch  (t[i])
	{
	case '\n':
	  s[j++] = '\\';
	  s[j++] = 'n';
	  break;
	case '\t':
	  s[j++] = '\\';
	  s[j++] = 't';
	  break;
	default:
	  s[j++] = t[i];
	  break;
	}
      ++i;
    }
  s[j] = '\0';
}

/* Turns '\\n' and '\\t' into \t and \n */
void otherEscape(char s[], char t[])
{
  int i = 0;
  int j = 0;
  
  while (t[i] != '\0' && j <= LEN)
    {
      switch (t[i])
	{
	case '\\':
	  switch (t[++i])
	    {
	    case 't':
	      s[j++] = '\t';
	      break;
	    case 'n':
	      s[j++] = '\n';
	      break;
	    default:
	      s[j++] = '\\';
	      s[j++] = t[i];
	      break;
	    }
	default:
	  s[j++] = t[i];
	  break;
	}
      ++i;
    }
  s[j] = '\0';
}

int main()
{
  int c;
  char str[LEN];
  char other[LEN];
  char x[LEN];
  int i = 0;
  
  while ((c=getchar()) != EOF)
    {
      if (c == '`') // I arbitarily chose this to end a string.
	{
	  str[i] = '\0';
	  escape(other, str);
	  otherEscape(x, other);
	  printf("%s\n", other); // Prints \n and \t as characters
	  printf("%s\n", x); // Prints \n \t as tabs and escapes.
	  i = 0;
	}
      else
	str[i++] = c;
    }
}
