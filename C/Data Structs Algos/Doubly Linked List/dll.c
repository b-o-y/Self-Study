#include "dll.h"
/*
* Returns: The address of the list.
* Notes:
* 1) The caller is responsible for freeing the memory occupied
*    by the list by calling ENQ_destroy_list.
* 2) The list name is copied into a private buffer which is
*    freed when the list is destroyed.
*/
ENQ_ANCHOR_p_t ENQ_create_list( const char *name )
{
    ENQ_ANCHOR_p_t list = TJH_new( sizeof(ENQ_ANCHOR_t) );
    
    list->flink = list;
    list->blink = list;
    list->name = TJH_NEW_STR_IF( name );
    
    return list;
}

/*
* Returns: The address of the item.
* Notes:
* 1) The caller is responsible for freeing the memory occupied
*    by the item by calling ENQ_destroy_item.
* 2) The item name is copied into a private buffer which is
*    freed when the item is destroyed.
*/
ENQ_ITEM_p_t ENQ_create_item( const char *name, size_t size )
{
    ENQ_ITEM_p_t item = (ENQ_ITEM_p_t)TJH_malloc( size );
    
    TJH_ASSERT( size >= sizeof(ENQ_ITEM_t) );
    item->flink = item;
    item->blink = item;
    item->name = TJH_NEW_STR_IF( name );
    
    return item;
}

/*
* Returns: TJH_TRUE if the item is enqueued, TJH_FALSE otherwise.
*/
TJH_BOOL_t ENQ_is_item_enqed( ENQ_ITEM_p_t item )
{
    TJH_BOOL_t retVal = (item->flink == item ? TJH_FALSE : TJH_TRUE);
    return retVal;
}

/*
* Returns: CDA_TRUE if the list is empty, CDA_FALSE otherwise
*/
TJH_BOOL_t ENQ_is_list_empty( ENQ_ANCHOR_p_t list )
{
    TJH_BOOL_t retVal = (list->flink == list ? TJH_FALSE : TJH_TRUE);
    return retVal;
}

/*
* Returns: address of enqueued item
*/
//ENQ_ITEM_p_t ENQ_add_head( ENQ_ANCHOR_p_t list, ENQ_ITEM_p_t item );
