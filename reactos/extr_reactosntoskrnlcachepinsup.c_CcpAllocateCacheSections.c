#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ULONG ;
struct TYPE_8__ {TYPE_1__* SectionObjectPointer; } ;
struct TYPE_7__ {int RefCount; } ;
struct TYPE_6__ {scalar_t__ SharedCacheMap; } ;
typedef  int /*<<< orphan*/  PROS_SECTION_OBJECT ;
typedef  scalar_t__ PNOCC_CACHE_MAP ;
typedef  TYPE_2__* PNOCC_BCB ;
typedef  TYPE_3__* PFILE_OBJECT ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int CACHE_NUM_SECTIONS ; 
 int /*<<< orphan*/  CcCacheBitmap ; 
 int CcCacheClockHand ; 
 TYPE_2__* CcCacheSections ; 
 int /*<<< orphan*/  CcpDereferenceCache (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DPRINT (char*,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*,...) ; 
 int /*<<< orphan*/  FALSE ; 
 int INVALID_CACHE ; 
 int RtlFindClearBitsAndSet (int /*<<< orphan*/ ,int,int) ; 
 int RtlTestBit (int /*<<< orphan*/ ,int) ; 

ULONG
CcpAllocateCacheSections(PFILE_OBJECT FileObject,
                         PROS_SECTION_OBJECT SectionObject)
{
    ULONG i = INVALID_CACHE;
    PNOCC_CACHE_MAP Map;
    PNOCC_BCB Bcb;

    DPRINT("AllocateCacheSections: FileObject %x\n", FileObject);

    if (!FileObject->SectionObjectPointer)
        return INVALID_CACHE;

    Map = (PNOCC_CACHE_MAP)FileObject->SectionObjectPointer->SharedCacheMap;

    if (!Map)
        return INVALID_CACHE;

    DPRINT("Allocating Cache Section\n");

    i = RtlFindClearBitsAndSet(CcCacheBitmap, 1, CcCacheClockHand);
    CcCacheClockHand = (i + 1) % CACHE_NUM_SECTIONS;

    if (i != INVALID_CACHE)
    {
        DPRINT("Setting up Bcb #%x\n", i);

        Bcb = &CcCacheSections[i];

        ASSERT(Bcb->RefCount < 2);

        if (Bcb->RefCount > 0)
        {
            CcpDereferenceCache(i, FALSE);
        }

        ASSERT(!Bcb->RefCount);
        Bcb->RefCount = 1;

        DPRINT("Bcb #%x RefCount %d\n", Bcb - CcCacheSections, Bcb->RefCount);

        if (!RtlTestBit(CcCacheBitmap, i))
        {
            DPRINT1("Somebody stoeled BCB #%x\n", i);
        }
        ASSERT(RtlTestBit(CcCacheBitmap, i));

        DPRINT("Allocated #%x\n", i);
        ASSERT(CcCacheSections[i].RefCount);
    }
    else
    {
        DPRINT1("Failed to allocate cache segment\n");
    }
    return i;
}