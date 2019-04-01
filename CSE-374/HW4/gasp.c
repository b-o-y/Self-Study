/*
* Travis Henderson
* Date Last Modified: 18/07/31
* HW4 for CSE374
*
* Description: Basically grep, but simpler and cannot
* process regular expressions.
*
* Resources:
* - https://www.geeksforgeeks.org/c-program-print-contents-file/
*
* Notes:
* --> This program assumes the options/flags are past first, word to match second,
* then text files after that.
* --> Flags need to be given as separate arguments: -n -i OKAY!, -ni NO!
* --> Not sure why the compiler thinks strcasestr is an implicit declaration.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#define MAX 500
#define NAMEOP "-n"
#define IGNCASE "-i"

void find_string(char *argv[], int argc);
char *strlwr(char *str);
int is_print_name(char *str[]);
int is_case_sens(char *str[]);


int main(int argc, char *argv[])
{
	if (argc == 1)
	{
		fprintf(stderr, "No command-line arguments, program terminating.\n");
		return EXIT_FAILURE;
	}
	else
	{
		find_string(argv, argc);
	}
	return EXIT_SUCCESS;
}

// Opens a file(s) and prints every line with a specified string.
void find_string(char *argv[], int argc)
{
	int i = 1;
	
	int printName = is_print_name(argv);
	if (printName)
		++i; // Then increment on argv.
	
	int caseSensitive = is_case_sens(argv);
	if (caseSensitive)
		++i; // Then increment on argv.
	
	char *strToMatch = argv[i++];	
	while (i < argc)
	{
		FILE *fptr;
		char str[MAX];
		char *nameOfFile = argv[i++];
		fptr = fopen(nameOfFile, "r");
		if (fptr)
		{
			while (fgets(str, MAX, fptr))
			{
				if (caseSensitive)
				{
					if (strcasestr(str, strToMatch) != 0)
					{
						if (printName)
							printf("%s: ", nameOfFile);
						printf("%s\n", str);
					}
			
				}
				else
				{
					if (strstr(str, strToMatch) != NULL)
					{
						if (printName)
							printf("%s: ", nameOfFile);
						printf("%s\n", str);
					}

				}
			}
			fclose(fptr);
		}
		else
		{
			fprintf(stderr, "Could not open file: %s\n", nameOfFile);
		}
	}
}

// Converts a string to all lowercase letters.
// This function is from stack exchange, I forgot
// to link it in this program.
char *strlwr(char *str)
{
  unsigned char *p = (unsigned char *)str;

  while (*p) {
     *p = tolower((unsigned char)*p);
      p++;
  }

  return str;
}

// Checks if the name of file option was passed.
int is_print_name(char *str[])
{
	if (!strcmp(strlwr(str[1]), NAMEOP) || !strcmp(strlwr(str[2]), NAMEOP))
		return 1;
	else
		return 0;
}

// Checks if the ignore case option was passed.
int is_case_sens(char *str[])
{
	if (!strcmp(strlwr(str[1]), IGNCASE) || !strcmp(strlwr(str[2]), IGNCASE))
		return 1;
	else
		return 0;	
}
