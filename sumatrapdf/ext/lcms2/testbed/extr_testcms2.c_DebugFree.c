#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  scalar_t__ cmsContext ;
struct TYPE_3__ {scalar_t__ WhoAllocated; int /*<<< orphan*/  DontCheck; scalar_t__ KeepSize; } ;
typedef  TYPE_1__ _cmsMemoryBlock ;

/* Variables and functions */
 int /*<<< orphan*/  Die (char*) ; 
 int /*<<< orphan*/ * SIZE_OF_MEM_HEADER ; 
 int /*<<< orphan*/  TotalMemory ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

__attribute__((used)) static
void  DebugFree(cmsContext ContextID, void *Ptr)
{
    _cmsMemoryBlock* blk;

    if (Ptr == NULL) {
        Die("NULL free (which is a no-op in C, but may be an clue of something going wrong)");
    }

    blk = (_cmsMemoryBlock*) (((cmsUInt8Number*) Ptr) - SIZE_OF_MEM_HEADER);
    TotalMemory -= blk ->KeepSize;

    if (blk ->WhoAllocated != ContextID && !blk->DontCheck) {
        Die("Trying to free memory allocated by a different thread");
    }

    free(blk);
}