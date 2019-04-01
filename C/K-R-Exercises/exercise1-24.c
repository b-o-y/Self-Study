// Travis Henderson
// Last Modified: 16/08/25
// -----------------------------------------------------------
// K&R Exercise 1-24
// Write a program to check a C program for rudimentary syntax
// errors like unmatched parentheses, brackets and braces.
// Don't forget about quotes, both single and double, escape
// sequences, and comments. (This program is hard if you do it
// in full generality.)
//
// NOTES:
// - I made this as simple as possible.  Only checks numbers
// of brackets/parentheses, not if they actually match.
// I tested with this sample:
// while()
//  {
//    array[
//	  if ()
//	    whatever))
//	    {}
// Not sure what the question means about comments, like
// watching out that the bracket count doesn't get thrown
// off by stuff in comments?  I just did this problem
// assuming no comments.  Kind of want to move onto more
// interesting exercises, specifically pointers because that's
// something I'm not real knowledgable about yet.
// -----------------------------------------------------------

#include <stdio.h>

int main()
{
  int c = 0;
  int OParenth = 0; // Keep tack of opening parentheses.
  int CParenth= 0; // To keep track of closing parentheses.
  int OBracket = 0; // open/close brakcet.
  int CBracket = 0;
  int OSquig = 0; // Can't remember what { is called.
  int CSquig = 0;
  
  while ((c=getchar()) != EOF)
    {
      putchar(c);
      if(c == '(')
	++OParenth;
      if (c == ')')
	++CParenth;
      if (c == '[')
	++OBracket;
      if (c == ']')
	++CBracket;
      if (c == '{')
	++OSquig;
      if (c == '}')
	++CSquig;
    }
  if (OBracket != CBracket) // If the following don't have the same value, then there is a mismatch.
    printf("Mismatch brackets.\n");
  if (CParenth != OParenth)
    printf("Mismatch in parenthese.\n");
  if (OSquig != CSquig)
    printf("Mismatch in curly brackets.\n");
}

