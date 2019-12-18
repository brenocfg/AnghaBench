#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ USHORT ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_5__ {size_t Handle; int /*<<< orphan*/  Entry; } ;
struct TYPE_4__ {scalar_t__ PageCount; int /*<<< orphan*/  PageList; scalar_t__ Allocated; } ;
typedef  TYPE_1__* PEMS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  AllocBitmap ; 
 int /*<<< orphan*/  EMS_STATUS_INSUFFICIENT_PAGES ; 
 int /*<<< orphan*/  EMS_STATUS_SUCCESS ; 
 size_t EMS_SYSTEM_HANDLE ; 
 int /*<<< orphan*/  EmsFree (size_t) ; 
 TYPE_1__* EmsHandleTable ; 
 TYPE_2__* EmsPageTable ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RtlFindNextForwardRunClear (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  RtlSetBits (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ TRUE ; 

__attribute__((used)) static UCHAR InitSystemHandle(USHORT NumPages)
{
    //
    // FIXME: This is an adapted copy of EmsAlloc!!
    //

    ULONG i, CurrentIndex = 0;
    PEMS_HANDLE HandleEntry = &EmsHandleTable[EMS_SYSTEM_HANDLE];

    /* The system handle must never have been initialized before */
    ASSERT(!HandleEntry->Allocated);

    /* Now allocate it */
    HandleEntry->Allocated = TRUE;

    while (HandleEntry->PageCount < NumPages)
    {
        ULONG RunStart;
        ULONG RunSize = RtlFindNextForwardRunClear(&AllocBitmap, CurrentIndex, &RunStart);

        if (RunSize == 0)
        {
            /* Free what's been allocated already and report failure */
            EmsFree(EMS_SYSTEM_HANDLE);
            // FIXME: For this function (and EmsAlloc as well),
            // use instead an internal function that just uses
            // PEMS_HANDLE pointers instead. It's only in the
            // EMS interrupt handler that we should do the
            // unfolding.
            return EMS_STATUS_INSUFFICIENT_PAGES;
        }
        else if ((HandleEntry->PageCount + RunSize) > NumPages)
        {
            /* We don't need the entire run */
            RunSize = NumPages - HandleEntry->PageCount;
        }

        CurrentIndex = RunStart + RunSize;
        HandleEntry->PageCount += RunSize;
        RtlSetBits(&AllocBitmap, RunStart, RunSize);

        for (i = 0; i < RunSize; i++)
        {
            EmsPageTable[RunStart + i].Handle = EMS_SYSTEM_HANDLE;
            InsertTailList(&HandleEntry->PageList, &EmsPageTable[RunStart + i].Entry);
        }
    }

    return EMS_STATUS_SUCCESS;
}