// Travis Henderson
// Last Modified: 16/09/09
// -----------------------------------------------------------
// K&R Exercise 5-9
// Rewrite the routines day_of_year and month_day with
// pointers instead of indexing.
//
// NOTES:
// - I took out the error checking from the previous exercise.
// -----------------------------------------------------------

#include <stdio.h>

static char dayTab[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

// Set day of year from month & day.
int dayOfYear(int year, int month, int day)
{
  int i, leap;
  char *dayPtr;

  leap = (year%4 == 0 && year%100 != 0) || (year%400 == 0);
  dayPtr = dayTab[leap]; // I have now entered the proper row.
  for (i = 1; i < month; i++)
    day += *++dayPtr; // Prefix because of index 0.
  return day;
}

// Set month, day from day of year.
void monthDay(int year, int yearDay, int *pMonth, int *pDay)
{
  int i = 1, leap;
  char *dayPtr;

  leap = (year%4 == 0 && year%100 != 0) || (year%400 == 0);
  dayPtr = dayTab[leap];
  while (yearDay > *dayPtr)
    {
      yearDay -= *++dayPtr;
      ++i;
    }
  *pMonth = i;
  *pDay = yearDay;
}

int main()
{
  printf("62/12/24: %d\n", dayOfYear(2015, 12, 24));
  int a, b;
  monthDay(1982, 300, &a, &b); // Need to use & operator, POINTERS POINT TO ADDRESSES!
  printf("The 300th day in 1982 is %d month and %d day\n", a, b);
  return 0;
}
