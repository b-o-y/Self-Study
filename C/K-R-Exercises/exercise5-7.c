// Travis Henderson
// Last Modified: 16/09/09
// -----------------------------------------------------------
// K&R Exercise 5-7
// Rewrite readlines to store lines in an array supplied by
// main, rather than calling alloc to maintain storage. How
// much faster is the program?
//
// NOTES:
// - This ins't a unique solution.  I had to consul the
// internet for help.
// - This line in the improved readLinesII:
// char *storeEnd = storage + MAX;
// I think I know what it means, my explanation in the
// inline comment of the method, but it's kind of throwing
// me.  I'm not too sure.  I see the context of how storeEnd
// is used, I just don't understand why it's initialized
// the way it is.
// -----------------------------------------------------------

#include <stdio.h>
#include <string.h>
#define MAX 1000

static char allocBuf[MAX];
static char *allocP = allocBuf; // Next free position.
char *linePtr[MAX]; // Pointers to text lines.

// Interchange v[i] and v[j].
void swap(char *v[], int i, int j)
{
  char *temp;

  temp = v[i];
  v[i] = v[j];
  v[j] = temp;
}

// Sort v[left]...v[right] into increasing order.
void qSort(char *v[], int left, int right)
{
  int i , last;

  if (left >= right) // Do nothing if array contains <2 elements.
    return;
  swap(v, left, (left + right)/2);
  last = left;
  for (i = left+1; i <= right; i++)
    if (strcmp(v[i], v[left]) < 0)
      swap(v, ++last, i);
  swap(v, left, last);
  qSort(v, left, last-1);
  qSort(v, last+1, right);
}

// Return pointer to n characters.
char *alloc(int n)
{
  if (allocBuf + MAX - allocP >= n) // It fits.
    {
      allocP += n; // Update space taken in allocP
      return allocP - n; // The beginning of the pointer.
    }
  else // No room.
    return 0;
}

// Read a line into s, return length.
int getLine(char s[], int lim)
{
  int c, i;

  for (i = 0; i < lim-1 && (c=getchar()) != EOF && c != '\n'; ++i)
    s[i] = c;
  if (c == '\n')
    s[i++] = c;
  s[i] = '\0';

  return i;
}
  
// Write output lines.
void writeLines(char *linePtr[], int nLines)
{
  while (nLines-- > 0)
    printf("%s\n", *linePtr++);
}

// Read input lines.
int readLines(char *linePtr[], int maxLines)
{
  int len, nLines;
  char *p, line[MAX];

  nLines = 0;
  while ((len = getLine(line, MAX)) > 0)
    if (nLines >= maxLines || (p = alloc(len)) == NULL)
      return -1;
    else
      {
	line[len-1] = '\0'; // Delete newLine.
	strcpy(p, line);
	linePtr[nLines++] = p;
      }

  return nLines;
}

// Reads input lines, stores them in an array without alloc.
// How I understand to this work:
// p points to storage, the array recording the lines read
// in.  As each line is read in, p is incremented by the
// length of the read line.  It always leaves off where
// the last input was recorded.
int readLinesII(char *linePtr[], int maxLines, char *storage)
{
  int len, nLines;
  char line[MAX];
  char *p = storage; // p keeps track of where the last line was stored in  memory.
  char *storeEnd = storage + MAX; // Max amount that can be stored.  The "end" of the allocated sotrage in memory.

  nLines= 0;
  while ((len = getLine(line, MAX)) > 0)
    if (nLines >= maxLines || p + len > storeEnd)
      return -1;
    else
      {
	line[len-1] = '\0';
	strcpy(p, line);
	linePtr[nLines++] = p;
	p += len; // Update the running "total" of storage allocated.
      }

  return nLines;
}

int main()
{
  int nLines; // Number of input lines read.
  char a[MAX];

  if ((nLines = readLinesII(linePtr, MAX, a)) >= 0)
    {
      qSort(linePtr, 0, nLines-1);
      writeLines(linePtr, nLines);
      return 0;
    }
  else
    {
      printf("Error: input too big\n");
      return 1;
    }
}
