#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cmsUInt8Number ;
typedef  int /*<<< orphan*/  cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_2__ {int /*<<< orphan*/  KeepSize; } ;
typedef  TYPE_1__ _cmsMemoryBlock ;

/* Variables and functions */
 int /*<<< orphan*/  DebugFree (int /*<<< orphan*/ ,void*) ; 
 void* DebugMalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SIZE_OF_MEM_HEADER ; 
 int /*<<< orphan*/  memmove (void*,void*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static
void * DebugRealloc(cmsContext ContextID, void* Ptr, cmsUInt32Number NewSize)
{
    _cmsMemoryBlock* blk;
    void*  NewPtr;
    cmsUInt32Number max_sz;

    NewPtr = DebugMalloc(ContextID, NewSize);
    if (Ptr == NULL) return NewPtr;

    blk = (_cmsMemoryBlock*) (((cmsUInt8Number*) Ptr) - SIZE_OF_MEM_HEADER);
    max_sz = blk -> KeepSize > NewSize ? NewSize : blk ->KeepSize;
    memmove(NewPtr, Ptr, max_sz);
    DebugFree(ContextID, Ptr);

    return NewPtr;
}