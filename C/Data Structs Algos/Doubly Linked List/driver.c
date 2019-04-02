#include "dll.h"

int main()
{
    ENQ_ANCHOR_p_t one = ENQ_create_list("asdf");
    printf("%s\n", one->name);
    printf("%d\n", ENQ_is_list_empty(one));
    char *e = "zzzzz";
    ENQ_ITEM_p_t a = ENQ_create_item(e, sizeof(ENQ_ITEM_t));
    printf("%s\n", a->name);
    printf("%d\n", ENQ_is_item_enqed(a));
    
    return 0;
}
