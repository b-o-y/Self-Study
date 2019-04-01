/*
* This is meant to be a core library that makes
* traditional C methods more "safe" and implements
* commonly used functions.
*
* The methods and ideas are based off of Jack Straub's
* lecture notes from the University of Washington, which I used
* for my own self study.
* http://faculty.washington.edu/jstraub/
*
* Some common functions are defined as macros, so as to keep the
* variable types generic.
*/

#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Safer version of malloc that makes sure memory gets allocated.
void* TJH_malloc(size_t size)
{
    void *retMem = malloc(size);
    if (retMem == NULL && size > 0)
    {
        printf("ERROR: tjh_malloc failed, aborting.\n");
        abort();
    }
    return retMem;
}

void TJH_free(void *mem)
{
    if (mem != NULL)
        free(mem);
}

void* TJH_new(size_t var)
{
    return (void*)TJH_malloc(sizeof(var));
}

char* TJH_new_str(char* str)
{
    return strcpy((char*)TJH_malloc(strlen((str))+ 1),(str));
}
