/*
* Simple testing to verify my library works.
* Uncomment whichever funtion one wants to test.
*/

#include <stdio.h>
#include <string.h>
#include "tjhcore.h"

int main()
{
    // Test TJH_ASSERT.
    /*TJH_ASSERT(3 > 1);
    printf("TJH_ASSERT is working.\n");*/
    
    // Test TJH_SIZEOF.
    /*int a[3];
    printf("%ld\n", TJH_SIZEOF(a));*/

    // Test of TJH_new, verified in valgrind.
    /*int *ptr;
    ptr = TJH_new(sizeof(int));
    *ptr = 23;
    printf("%d\n", *ptr);*/
    
    // Test of TJH_free, verified in valgrind.
    //TJH_free(ptr);
    
    // Test of TJH_new_str and TJH_NEW_STR_IF, verified in valgrind.
    /*char* a = "yes";
    char* b;
    b = TJH_NEW_STR_IF(a);
    printf("%s\n", b);
    TJH_free(b);*/
    char* a = "yes";
    printf("%d\n", strlen(a));
    
    return 0;
}
