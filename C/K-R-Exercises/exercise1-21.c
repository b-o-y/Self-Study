// Travis Henderson
// Last Modified: 16/08/23
// -----------------------------------------------------------
// K&R Exercise 1-21
// Write a program entab that replaces strings of blanks by
// the minimum number of tabs and blanks to achieve the same
// spacing. Use the same tab stops as for detab. When either
// a tab or a single blank would suffice to reach a tab stop,
// which should be given preference?
//
// NOTE:
// -Not sure if I'm understanding this correctly, but I
// wrote a program that replaces any inputted spaces/tabs with
// the minimum amount of tabs and spaces. So on my terminal a
// tab looks like 8 spaces, so if I enter 10 spaces that would
// be replaced by a tab and 2 spaces.
// -This implementation only works with spaces and tabs as
// input and reformats them in columns represented with
// underscores as tabs and dashes as spaces.
// -----------------------------------------------------------

#include <stdio.h>
#define NUMSP 10 // Number of spaces, width of columns/tabs.
#define TAB '_'
#define SPACE '-'
#define MAX 1000

// ---------- reSpace ----------
// Takes the read in char array
// and respaces it accordingly.
// -----------------------------
void reSpace(char s[])
{
  int spaces = 0; // Counts how many spaces are read in.
  int i = 0; // Increments through s.
  int isThereEndL = 0; // "boolean" for if there wasn \n.
  int t = 0; // Keeps track of how many tabs there are.
  while((s[i] != '\0') && (s[i] != '\n')) // This loop finds how many spaces and tabs there are.
    {
      if (s[i] == ' ')
	{
	  ++spaces;
	  ++i;
	}
      else if (s[i] == '\n')
	isThereEndL = 1;
      else // Then it is a tab.
	{
	  ++t;
	  ++i;
	}
    }

    t *= 8; // A tab is worth 8 spaces.
    spaces += t; // Now I have an absolute total of characters.
    char other[MAX]; // The reformatted string.
    int j = 0; // To iterate through other.
    while (spaces > 0 && j < MAX-1)
      {
	if (spaces >= NUMSP) // This means a column consisting of a tab can be made.
	  {
	    for (int k = 0; k <= 8; ++k) // 8 is the width of a tab, insert a tab.
		other[j++] = TAB;
	    spaces -= 8;
	    for(int k = 0; k <= 2; ++k) // Each line is 10 characters. 10-tab = 2 spaces.
	      other[j++] = SPACE;
	    spaces -= 2;
	    for (int k = 0; k <= NUMSP; ++k) // Creates a new column/tabstop.
	      other[j++] = ' ';
	  }
	else // There is no more room for tabs, the rest has to be filled with SPACE.
	  {
	    while (spaces > 0)
	      {
		other[j++] = SPACE;
		  --spaces;
	      }
	  }
      }
    if(isThereEndL) // Add the new line, if there.
      other[j++] = '\n';
    other[j] = '\0';
    printf("%s\n", other);
}

// ---------- getLine ----------
// Reads input from terminal to
// make an char array string.
// -----------------------------
int getLine(char s[])
{
  int c, i;
  // If input is anything other than a space or tab, program terminates.
  for(i = 0; (i < MAX-1) && ((c=getchar()) !=EOF) && (c!= '\n') && (c==' ' || c=='\t'); ++i)
    s[i] = c;
  if (c == '\n')
    {
      s[i] = c;
      ++i;
    }
  s[i] = '\0';
  return i;
}

int main()
{
  int len;
  char line[MAX];
  
  while ((len=getLine(line)) > 0)
    {
      reSpace(line);
    }
}
