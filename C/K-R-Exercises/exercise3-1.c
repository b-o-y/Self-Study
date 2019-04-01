// Travis Henderson
// Last Modified: 16/08/30
// -----------------------------------------------------------
// K&R Exercise 3-1
// Our binary search makes two tests inside the loop, when
// one would suffice (at the price of more tests outside.)
// Write a version with only one test inside the loop and
// measure the difference in run-time.
//
// NOTES:
// - When I change len to any number above 30, everything
// just gets hung up in terminal.  I have no idea why.
// Especially since binsearch is provided in the book.
// - I see no difference in run time.
// -----------------------------------------------------------

#include <stdio.h>
#include <time.h>

/* Finds x in array v.  Array must
be sorted. Returns the index that
x is found at. */
int binsearch(int x, int v[], int n)
{
  int low, mid, high;
  low = 0;
  high = n-1;
  while (low <= high)
    {
      mid = (low+high)/2;
      if (x < v[mid])
	high = mid-1;
      else if (x > v[mid])
	low = mid+1;
      else // Found value.
	return mid;
    }
  return -1; // No match found.
}

// Alternative to binary search.
int otherBinSearch(int x, int v[], int n)
{
  int low = 0;
  int high = n-1;
  int mid = (low+high)/2;
  // Array keeps getting smaller until only value left is the "middle."
  // Hence the extra conditional in the while.
  while (low <= high && x != v[mid])
    {
      if (x < v[mid]) // The value must be in the lower half of array.
	high = mid-1;
      else // Otherwise, it's in the upper half.
	low = mid+1;
      mid = (high+low)/2; // Change mid to reflect the bounds of the search.
    }
  if (x == v[mid]) // Found a match.
    return mid;
  else // No match.
    return -1;
}

int main()
{
  int a = 6458;
  int len = 10000;
  int b[len];
  for(int i = 0; i < len; i++)
    b[i] = i;

  clock_t start, end;
  start = clock();
  binsearch(a, b, len);
  end = clock();
  double cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("binsearch took %f seconds.\n", cpuTimeUsed);

  start = clock();
  otherBinSearch(a, b, len);
  end = clock();
  cpuTimeUsed = ((double) (end - start)) / CLOCKS_PER_SEC;
  printf("otherBinSearch took %f seconds.\n", cpuTimeUsed);
}
