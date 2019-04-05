#ifndef DLL_H
#define DLL_H
#include "tjhcore.h"

typedef struct enq_item_s
{
    struct enq_item_s *flink;
    struct enq_item_s *blink;
    char              *name;
} ENQ_ITEM_t, *ENQ_ITEM_p_t;
typedef ENQ_ITEM_t ENQ_ANCHOR_t, *ENQ_ANCHOR_p_t;

ENQ_ANCHOR_p_t ENQ_create_list( const char *name );
ENQ_ITEM_p_t ENQ_create_item( const char *name, size_t size );
TJH_BOOL_t ENQ_is_item_enqed( ENQ_ITEM_p_t item );
TJH_BOOL_t ENQ_is_list_empty( ENQ_ANCHOR_p_t list );
ENQ_ITEM_p_t ENQ_add_head( ENQ_ANCHOR_p_t list, ENQ_ITEM_p_t item );
ENQ_ITEM_p_t ENQ_add_tail( ENQ_ANCHOR_p_t list, ENQ_ITEM_p_t item );
ENQ_ITEM_p_t ENQ_add_after( ENQ_ITEM_p_t item,ENQ_ITEM_p_t after );
ENQ_ITEM_p_t ENQ_add_before( ENQ_ITEM_p_t item,ENQ_ITEM_p_t before );
ENQ_ITEM_p_t ENQ_deq_item( ENQ_ITEM_p_t item );




#endif
