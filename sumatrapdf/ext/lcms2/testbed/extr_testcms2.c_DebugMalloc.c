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
typedef  scalar_t__ cmsUInt32Number ;
typedef  int /*<<< orphan*/  cmsContext ;
struct TYPE_2__ {scalar_t__ DontCheck; int /*<<< orphan*/  WhoAllocated; scalar_t__ KeepSize; } ;
typedef  TYPE_1__ _cmsMemoryBlock ;

/* Variables and functions */
 int /*<<< orphan*/  Die (char*) ; 
 scalar_t__ MaxAllocated ; 
 scalar_t__ SIZE_OF_MEM_HEADER ; 
 scalar_t__ SingleHit ; 
 scalar_t__ TotalMemory ; 
 scalar_t__ malloc (scalar_t__) ; 

__attribute__((used)) static
void* DebugMalloc(cmsContext ContextID, cmsUInt32Number size)
{
    _cmsMemoryBlock* blk;

    if (size <= 0) {
       Die("malloc requested with zero bytes");
    }

    TotalMemory += size;

    if (TotalMemory > MaxAllocated)
        MaxAllocated = TotalMemory;

    if (size > SingleHit)
        SingleHit = size;

    blk = (_cmsMemoryBlock*) malloc(size + SIZE_OF_MEM_HEADER);
    if (blk == NULL) return NULL;

    blk ->KeepSize = size;
    blk ->WhoAllocated = ContextID;
    blk ->DontCheck = 0;

    return (void*) ((cmsUInt8Number*) blk + SIZE_OF_MEM_HEADER);
}