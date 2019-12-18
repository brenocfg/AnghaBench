#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct _cmsContext_struct {int /*<<< orphan*/  MemPool; scalar_t__* chunks; } ;
struct TYPE_4__ {struct TYPE_4__* TagTypes; struct TYPE_4__* Next; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ _cmsTagTypePluginChunkType ;
typedef  TYPE_1__ _cmsTagTypeLinkedList ;

/* Variables and functions */
 scalar_t__ _cmsSubAllocDup (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static
void DupTagTypeList(struct _cmsContext_struct* ctx,
                    const struct _cmsContext_struct* src,
                    int loc)
{
   _cmsTagTypePluginChunkType newHead = { NULL };
   _cmsTagTypeLinkedList*  entry;
   _cmsTagTypeLinkedList*  Anterior = NULL;
   _cmsTagTypePluginChunkType* head = (_cmsTagTypePluginChunkType*) src->chunks[loc];

   // Walk the list copying all nodes
   for (entry = head->TagTypes;
       entry != NULL;
       entry = entry ->Next) {

           _cmsTagTypeLinkedList *newEntry = ( _cmsTagTypeLinkedList *) _cmsSubAllocDup(ctx ->MemPool, entry, sizeof(_cmsTagTypeLinkedList));

           if (newEntry == NULL)
               return;

           // We want to keep the linked list order, so this is a little bit tricky
           newEntry -> Next = NULL;
           if (Anterior)
               Anterior -> Next = newEntry;

           Anterior = newEntry;

           if (newHead.TagTypes == NULL)
               newHead.TagTypes = newEntry;
   }

   ctx ->chunks[loc] = _cmsSubAllocDup(ctx->MemPool, &newHead, sizeof(_cmsTagTypePluginChunkType));
}