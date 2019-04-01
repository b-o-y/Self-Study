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

#ifndef CDA_H
#define CDA_H

#include <assert.h>

// Defining true/false purely for convenience.
#define TJH_TRUE        (1)
#define TJH_FALSE       (0)

/* Functions, wouldn't mind knowing how to get the macros that are 
* commented out to work... */
//#define TJH_NEW(var)    ((var*)TJH_malloc(sizeof(var)))
/*#define TJH_NEW_STR(str)        \
    (strcpy((char*)TJH_malloc(strlen((str))+ 1),(str)))*/
#define TJH_ASSERT(var) (assert(var))
#define TJH_SIZEOF(arr) (sizeof((arr))/sizeof(*(arr))) // TJH_SIZEOF print format is ld.
#define TJH_NEW_STR_IF(str) \
    ((str) == NULL ? NULL : TJH_new_str((str)))

void TJH_malloc(size_t size);
void TJH_free(void *mem);
void* TJH_new(size_t var);
char* TJH_new_str(char* str);
#endif
