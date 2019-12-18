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
struct TYPE_4__ {struct TYPE_4__* OptimizationCollection; struct TYPE_4__* Next; int /*<<< orphan*/ * member_0; } ;
typedef  TYPE_1__ _cmsOptimizationPluginChunkType ;
typedef  TYPE_1__ _cmsOptimizationCollection ;

/* Variables and functions */
 size_t OptimizationPlugin ; 
 int /*<<< orphan*/  _cmsAssert (int /*<<< orphan*/ ) ; 
 scalar_t__ _cmsSubAllocDup (int /*<<< orphan*/ ,TYPE_1__*,int) ; 

__attribute__((used)) static
void DupPluginOptimizationList(struct _cmsContext_struct* ctx,
                               const struct _cmsContext_struct* src)
{
   _cmsOptimizationPluginChunkType newHead = { NULL };
   _cmsOptimizationCollection*  entry;
   _cmsOptimizationCollection*  Anterior = NULL;
   _cmsOptimizationPluginChunkType* head = (_cmsOptimizationPluginChunkType*) src->chunks[OptimizationPlugin];

    _cmsAssert(ctx != NULL);
    _cmsAssert(head != NULL);

    // Walk the list copying all nodes
   for (entry = head->OptimizationCollection;
        entry != NULL;
        entry = entry ->Next) {

            _cmsOptimizationCollection *newEntry = ( _cmsOptimizationCollection *) _cmsSubAllocDup(ctx ->MemPool, entry, sizeof(_cmsOptimizationCollection));

            if (newEntry == NULL)
                return;

            // We want to keep the linked list order, so this is a little bit tricky
            newEntry -> Next = NULL;
            if (Anterior)
                Anterior -> Next = newEntry;

            Anterior = newEntry;

            if (newHead.OptimizationCollection == NULL)
                newHead.OptimizationCollection = newEntry;
    }

  ctx ->chunks[OptimizationPlugin] = _cmsSubAllocDup(ctx->MemPool, &newHead, sizeof(_cmsOptimizationPluginChunkType));
}