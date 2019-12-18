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
struct TYPE_4__ {struct TYPE_4__* FactoryList; struct TYPE_4__* Next; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ cmsFormattersFactoryList ;
typedef  TYPE_1__ _cmsFormattersPluginChunkType ;

/* Variables and functions */
 size_t FormattersPlugin ; 
 int /*<<< orphan*/  _cmsAssert (int /*<<< orphan*/ ) ; 
 scalar_t__ _cmsSubAllocDup (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static
void DupFormatterFactoryList(struct _cmsContext_struct* ctx,
                                               const struct _cmsContext_struct* src)
{
   _cmsFormattersPluginChunkType newHead = { NULL };
   cmsFormattersFactoryList*  entry;
   cmsFormattersFactoryList*  Anterior = NULL;
   _cmsFormattersPluginChunkType* head = (_cmsFormattersPluginChunkType*) src->chunks[FormattersPlugin];

     _cmsAssert(head != NULL);

   // Walk the list copying all nodes
   for (entry = head->FactoryList;
       entry != NULL;
       entry = entry ->Next) {

           cmsFormattersFactoryList *newEntry = ( cmsFormattersFactoryList *) _cmsSubAllocDup(ctx ->MemPool, entry, sizeof(cmsFormattersFactoryList));

           if (newEntry == NULL)
               return;

           // We want to keep the linked list order, so this is a little bit tricky
           newEntry -> Next = NULL;
           if (Anterior)
               Anterior -> Next = newEntry;

           Anterior = newEntry;

           if (newHead.FactoryList == NULL)
               newHead.FactoryList = newEntry;
   }

   ctx ->chunks[FormattersPlugin] = _cmsSubAllocDup(ctx->MemPool, &newHead, sizeof(_cmsFormattersPluginChunkType));
}