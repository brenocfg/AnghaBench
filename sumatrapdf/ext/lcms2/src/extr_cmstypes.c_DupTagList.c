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
struct TYPE_4__ {struct TYPE_4__* Tag; struct TYPE_4__* Next; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ _cmsTagPluginChunkType ;
typedef  TYPE_1__ _cmsTagLinkedList ;

/* Variables and functions */
 size_t TagPlugin ; 
 scalar_t__ _cmsSubAllocDup (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static
void DupTagList(struct _cmsContext_struct* ctx,
                    const struct _cmsContext_struct* src)
{
   _cmsTagPluginChunkType newHead = { NULL };
   _cmsTagLinkedList*  entry;
   _cmsTagLinkedList*  Anterior = NULL;
   _cmsTagPluginChunkType* head = (_cmsTagPluginChunkType*) src->chunks[TagPlugin];

   // Walk the list copying all nodes
   for (entry = head->Tag;
       entry != NULL;
       entry = entry ->Next) {

           _cmsTagLinkedList *newEntry = ( _cmsTagLinkedList *) _cmsSubAllocDup(ctx ->MemPool, entry, sizeof(_cmsTagLinkedList));

           if (newEntry == NULL)
               return;

           // We want to keep the linked list order, so this is a little bit tricky
           newEntry -> Next = NULL;
           if (Anterior)
               Anterior -> Next = newEntry;

           Anterior = newEntry;

           if (newHead.Tag == NULL)
               newHead.Tag = newEntry;
   }

   ctx ->chunks[TagPlugin] = _cmsSubAllocDup(ctx->MemPool, &newHead, sizeof(_cmsTagPluginChunkType));
}