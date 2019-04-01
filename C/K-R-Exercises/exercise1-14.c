// -----------------------------------------------------------
// Travis Henderson
// Last Modified: 16/08/20
// -----------------------------------------------------------
// K&R Exercise 1-14
// Write a program to print a histogram of the frequencies of
// different characters in its input.
//
// NOTE: I didn't do EVERY single character.  Instead I did
// ASCII characters that correspond to decimal 33-127, hence
// my MAX and LOW values.  That's 0x21 to 0x7E, or ! to ~.
// I don't think casting is supposed to be used, but I know
// little programming, and it makes sense to me.
// -----------------------------------------------------------

#include <stdio.h>
#define MAX 127
#define LOW 33

main()
{
  int c;
  int arr[MAX];
  
  for(int i = 0; i < MAX; ++i) // Initialize array with all zeroes.
    arr[i] = 0;
  
  while((c = getchar()) != EOF)
  {
    ++arr[c]; // Increment corresponding index of char to reflect frequency.
  }
  printf("\n");
  
  for (int i = LOW; i < MAX; ++i) // LOW-MAX, the character span I specified.
  {
    printf("|%c| ", (char)i);
    for (int j = 0; j < arr[i]; ++j)
      printf("*");
    printf("\n");
  }
}
