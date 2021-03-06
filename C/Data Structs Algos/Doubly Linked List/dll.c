#include "dll.h"
/*
* NOTES ON TERMINOLOGY:
* Item 1 > flink > Item 2 > flink > Item 3.....
* Item 1 < blink < Item 2 < blink < Item 3.....
* 
* If Item 1 and Item 3 were connected, and I inserted Item 2 between
* them, then: BEFORE is Item 1, AFTER is Item 3. (I read left to right!).
*/

/*
* Returns: 
*       The address of the list.
* Notes:
* 1) The caller is responsible for freeing the memory occupied
*    by the list by calling ENQ_destroy_list.
* 2) The list name is copied into a private buffer which is
*    freed when the list is destroyed.
*/
ENQ_ANCHOR_p_t ENQ_create_list( const char *name )
{
    ENQ_ANCHOR_p_t list = TJH_NEW( ENQ_ANCHOR_t );
    
    list->flink = list;
    list->blink = list;
    list->name  = TJH_NEW_STR_IF( name );
    
    return list;
}

/*
* Where:
*       name -> the name of the item.
        size == size of item required.
* Returns: 
*       The address of the item.
* Notes:
* 1) The caller is responsible for freeing the memory occupied
*    by the item by calling ENQ_destroy_item.
* 2) The item name is copied into a private buffer which is
*    freed when the item is destroyed.
* 3) For the parameter "size", I pass sizeof(ENQ_ITEM_t). I feel
*    like this is wrong, because I can just get rid of that parameter
*    and instead have TJH_malloc directly work on sizeof(ENQ_ITEM_t).
*    I'll have to think on what's going on here.
*/
ENQ_ITEM_p_t ENQ_create_item( const char *name, size_t size )
{
    ENQ_ITEM_p_t item = (ENQ_ITEM_p_t)TJH_malloc( size );
    
    TJH_ASSERT( size >= sizeof(ENQ_ITEM_t) );
    item->flink = item;
    item->blink = item;
    item->name  = TJH_NEW_STR_IF( name );
    
    return item;
}

/*
* Where:
*       item -> item to test.
* Returns: 
*       TJH_TRUE if the item is enqueued, TJH_FALSE otherwise.
*/
TJH_BOOL_t ENQ_is_item_enqed( ENQ_ITEM_p_t item )
{
    TJH_BOOL_t retVal = (item->flink == item ? TJH_false : TJH_true);
    return retVal;
}

/*
* Where:
*       list -> list to test.
* Returns: CDA_TRUE if the list is empty, CDA_FALSE otherwise.
*/
TJH_BOOL_t ENQ_is_list_empty( ENQ_ANCHOR_p_t list )
{
    TJH_BOOL_t retVal = (list->flink == list ? TJH_true : TJH_false);
    return retVal;
}

/*
* Where:
*       list -> list in which to enqueue.
*       item -> item to enqueue.
* Returns: 
*       address of enqueued item
*/
ENQ_ITEM_p_t ENQ_add_head( ENQ_ANCHOR_p_t list, ENQ_ITEM_p_t item )
{
    TJH_ASSERT( !ENQ_is_item_enqed( item ) );
    if ( ENQ_is_list_empty(list) ) // Empty list.
    {
        list->flink = item;        // Set the head to point to the item.
        list->blink = item; 
        item->flink = list;        // Set the item to point to the head.
        item->blink = list;      
    }
    else                           // List is not empty.
    {
        list->flink->blink = item; // Previous item points to new item.
        item->flink = list->flink; // New item points to previous item.
        list->flink = item;        // Head points to new item.
        item->blink = list;        // New item points to head.
    }
    return item;    
}

/*
* Where:
*       list -> list in which to enqueue.
*       item -> item to enqueue.
* Returns: 
*       address of enqueued item
*/
ENQ_ITEM_p_t ENQ_add_tail( ENQ_ANCHOR_p_t list, ENQ_ITEM_p_t item )
{
    TJH_ASSERT( !ENQ_is_item_enqed( item ) );
    if ( ENQ_is_list_empty(list) ) // Empty list.
    {
        list->flink = item;        // Set the head to point to the item.
        list->blink = item; 
        item->flink = list;        // Set the item to point to the head.
        item->blink = list;      
    }
    else                           // List is not empty.
    {
        list->blink->flink = item; // Previous item points to new item.
        item->blink = list->blink; // New item points to previous item.
        list->blink = item;        // Head points to new item.
        item->flink = list;        // New item points to head.
    }
    return item;    
}

/*
* Where:
*       item  -> item to enqueue.
        after -> item after which to enqueue.
* Returns: 
*       Address of enqueued itme.
*/
ENQ_ITEM_p_t ENQ_add_after( ENQ_ITEM_p_t item, ENQ_ITEM_p_t after )
{
    TJH_ASSERT( !ENQ_is_item_enqed( item ) );
    after->blink->flink = item;  // Item BEFORE points to NEW item.
    item->blink  = after->blink; // NEW item points to BEFORE.   
    item->flink  = after;        // NEW item points to AFTER.
    after->blink = item;         // AFTER points to NEW item. 

    return item;
}

/*
* Where:
*       item  -> item to enqueue.
        after -> item before which to enqueue.
* Returns: 
*       Address of enqueued itme.
*/
ENQ_ITEM_p_t ENQ_add_before( ENQ_ITEM_p_t item, ENQ_ITEM_p_t before )
{
    TJH_ASSERT( !ENQ_is_item_enqed( item ) );
    before->flink->blink = item;   // Item AFTER points to NEW item.
    item->flink   = before->flink; // NEW item points to AFTER.   
    item->blink   = before;        // NEW item points to BEFORE.
    before->flink = item;          // BEFORE points to NEW item. 

    return item;
}

/*
* Where:
*       item -> item to dequeue.
* Returns:
*       address of dequeued item.
*/
ENQ_ITEM_p_t ENQ_deq_item( ENQ_ITEM_p_t item )
{
    ENQ_ITEM_p_t placeholder = item->flink; // Placeholder is AFTER item.
    placeholder->blink = item->blink;       // AFTER points to BEFORE.
    item->blink->flink = placeholder;       // BEFORE points to AFTER.

    item->flink = item; // Return item to it's default state.
    item->blink = item;
    
    return item;
}

/*
* Where:
*       list -> list from which to dequeue
* Returns:
*       If queue is nonempty, the address of the dequeued item;
*       Otherwise the address of the list.
*/
ENQ_ITEM_p_t ENQ_deq_tail( ENQ_ANCHOR_p_t list )
{
    if ( ENQ_is_list_empty(list) )
        return list;
    else
    {
        ENQ_ITEM_p_t placeholder  = list->blink;        // Placeholder points to tail.
        list->blink               = placeholder->blink; // Head points to 2nd to last item.
        placeholder->blink->flink = list;               // 2nd to last item points to head.

        placeholder->flink = placeholder; // Return tail item to it's default state.
        placeholder->blink = placeholder;
        
        return placeholder;
    }
}

/*
* Where:
*       item -> item to destroy
* Returns:
*       NULL
* Notes:
*       The item to destroy may be enqueued or unenqueued. If enqueued, it will 
*       be dequeued prior to destruction.
*/
ENQ_ITEM_p_t ENQ_destroy_item( ENQ_ITEM_p_t item )
{
    ENQ_deq_item(item);
    TJH_free(item->name);
    TJH_free(item);

    return NULL;
}

/*
* Where:
*       list -> list to empty
* Returns:
*       The address of the list.
* Notes:
*       All items enqueued in the list will be destroyed.
*/
ENQ_ANCHOR_p_t ENQ_empty_list( ENQ_ANCHOR_p_t list )
{
    while ( !ENQ_is_list_empty(list) )
        ENQ_destroy_item(list->flink);
    
    return list;
}

/*
* Where:
*       list -> list to destroy
* Returns:
*       NULL
* Notes:
*       All items enqueued in the list will be destroyed.
*/
ENQ_ANCHOR_p_t ENQ_destroy_list( ENQ_ANCHOR_p_t list )
{
    ENQ_empty_list(list);
    TJH_free(list->name);
    TJH_free(list);
    
    return NULL;
}
