#include "dll.h"

int main()
{
    // Create list.
    ENQ_ANCHOR_p_t one = ENQ_create_list("First List");
    /*printf("Name of head: %s\n", one->name);
    printf("List should be empty: %d\n", ENQ_is_list_empty(one));*/
    
    // Create item.
    char *e = "a";
    ENQ_ITEM_p_t a = ENQ_create_item(e, sizeof(ENQ_ITEM_t));
    /*printf("Item name: %s\n", a->name);
    printf("Item should not be enqed: %d\n", ENQ_is_item_enqed(a));
    printf("Address of item: %x\n", &(*a));*/

    // Add item to head.
    ENQ_ITEM_p_t check = ENQ_add_head(one, a);
    /*printf("Return address of adding head ");
    printf("should be the same as last address: %x\n", &(*check));
    printf("Item should now be enqed: %d\n", ENQ_is_item_enqed(a));*/
    
    // Adding 2nd item to tail.
    char *jp = "b";
    ENQ_ITEM_p_t b = ENQ_create_item(jp, sizeof(ENQ_ITEM_t));
    printf("Address of 'b' item: %x\n", &(*b));
    check = ENQ_add_tail(one, b);    
    //printf("should be the same as last address: %x\n", &(*check));
    //printf("%s\n", one->flink->flink->flink->name);

    // Adding item in front of AFTER.
    char *cat = "cat";
    ENQ_ITEM_p_t kit = ENQ_create_item(cat, sizeof(ENQ_ITEM_t));
    ENQ_add_after(kit, b);
    //printf("%s\n", one->flink->flink->name);

    // Adding item behind BEFORE.
    char *dog = "dog";
    ENQ_ITEM_p_t dig = ENQ_create_item(dog, sizeof(ENQ_ITEM_t));
    ENQ_add_before(dig, kit);
    //printf("%s\n", one->blink->blink->blink->name);

    // Dequeue item.
    /*ENQ_deq_item(dig);
    //printf("%s\n", one->blink->blink->blink->blink->name);
 
    // Dequeue tail.
    check = ENQ_deq_tail(one);
    printf("Deq'd tail: %x\n", &(*check));
    printf("%s\n", one->flink->flink->flink->blink->name);
    
    // Get lhead/tail.
    printf("%x\n", ENQ_GET_HEAD(one));
    printf("%x\n", ENQ_GET_TAIL(one));*/

    // Macros Testing.
    /*printf("ENQ_GET_HEAD: %x\n", ENQ_GET_HEAD(one));
    printf("ENQ_GET_TAIL: %x\n", ENQ_GET_TAIL(one));
    printf("ENQ_GET_NEXT: %x\n", ENQ_GET_NEXT(dig));
    printf("ENQ_GET_PREV: %x\n", ENQ_GET_PREV(dig));
    printf("ENQ_GET_LIST_NAME: %s\n", ENQ_GET_LIST_NAME(one));
    printf("ENQ_GET_ITEM_NAME: %s\n", ENQ_GET_ITEM_NAME(dig));*/

    // Testing destroy.
    /*ENQ_destroy_item(dig);
    printf("%s\n", one->name);
    printf("%s\n", one->flink->name);
    printf("%s\n", one->flink->flink->name);
    printf("%s\n", one->flink->flink->flink->name);
    printf("%s\n", one->flink->flink->flink->flink->name);*/
    
    //ENQ_empty_list(one);
    one = ENQ_destroy_list(one);
    printf("%x\n", one);
    

    return 0;
}
