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

#include "tjhcore.h"

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
