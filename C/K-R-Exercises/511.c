/*
* Travis Henderson
* C Exercises
* Date Last Modified: 17/08/20
*
* 5-11:
* Modify entab and detab to accept a list of tab stops as arguments.  Use the default
* if there are no arguments.
* 
* NOTES:
* -Kind of messy, but I'll trust what I did a year ago, seems to work okay.
*/

#include <stdio.h>
#include <stdlib.h>
#define TAB '_'
#define SPACE '-'
#define MAX 1000


void reSpace(char s[]); // Takes the read in char array and respaces it accordingly.
int getLine(char s[]); // Reads input from terminal to make an char array string.
void entab();
void detab();

int numsp;

int main(int argc, char *argv[])
{
	if (argc == 1)
		numsp = 10;
	else
		numsp = atoi(argv[--argc]);
	printf("type for entab\n");
	entab();
	printf("now type spaces/tabs for detab\n");
	detab();
	
	return 0;
}

void entab()
{
	int c, i;
	i = 0; // i keeps track of what column the character is at.
	while ((c=getchar()) != EOF)
	{
		if (i >= numsp || c=='\n')  // Reset the increment for every new word and 10th space.
			i = 0;
		if (c==' ' || c=='\t')
			while(i <= numsp)
			{
				putchar(' ');  // Insert the tab stops.
				++i;
			}
		else
		{
			putchar(c);
			++i;
		}
    }
}


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
	if (spaces >= numsp) // This means a column consisting of a tab can be made.
	  {
	    for (int k = 0; k <= 8; ++k) // 8 is the width of a tab, insert a tab.
		other[j++] = TAB;
	    spaces -= 8;
	    for(int k = 0; k <= 2; ++k) // Each line is 10 characters. 10-tab = 2 spaces.
	      other[j++] = SPACE;
	    spaces -= 2;
	    for (int k = 0; k <= numsp; ++k) // Creates a new column/tabstop.
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

void detab()
{
  int len;
  char line[MAX];
  
  while ((len=getLine(line)) > 0)
    {
      reSpace(line);
    }
}
