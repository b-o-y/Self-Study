// Travis Henderson
// Last Modified: 16/09/09
// -----------------------------------------------------------
// K&R Exercise 5-8
// There is no error checking in day_of_year or month_day.
// Remedy this defect.
//
// NOTES:
// - For error checking, I just use conditionals to see
// if the input is within bounds of the calendar.
// -----------------------------------------------------------

#include <stdio.h>

static char dayTab[2][13] = {{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}, {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}};

// Set day of year from month & day.
int dayOfYear(int year, int month, int day)
{
  int i, leap;

  if (year < 1) // I'm assuming the calendar will hold true.
    return -1;
  leap = (year%4 == 0 && year%100 != 0) || (year%400 == 0);
  if (month < 1 || month > 12)
    return -1;
  if (day < 1 || day > dayTab[leap][month])
    return -1;
  for (i = 1; i < month; i++)
    day += dayTab[leap][i];
  return day;
}

// Set month, day from day of year.
void monthDay(int year, int yearDay, int *pMonth, int *pDay)
{
  int i, leap;

  if (year < 1)
    {
      *pMonth = -1;
      *pDay = -1;
      return;
    }
  leap = (year%4 == 0 && year%100 != 0) || (year%400 == 0);
  for (i = 1; yearDay > dayTab[leap][i]; i++)
      yearDay -= dayTab[leap][i];
  if (i > 12 || yearDay > 31)
    {
      *pMonth = -1;
      *pDay = -1;
    }
  else
    {
      *pMonth = i;
      *pDay = yearDay;
    }
}

int main()
{
  printf("62/12/24: %d\n", dayOfYear(2015, 12, 24));
  int a, b;
  monthDay(1982, 300, &a, &b); // Need to use & operator, POINTERS POINT TO ADDRESSES!
  printf("The 300th day in 1982 is %d month and %d day\n", a, b);
  return 0;
}
