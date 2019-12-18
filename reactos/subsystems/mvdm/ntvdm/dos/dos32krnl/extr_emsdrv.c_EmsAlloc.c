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
struct TYPE_5__ {int /*<<< orphan*/  Entry; int /*<<< orphan*/  Handle; } ;
struct TYPE_4__ {scalar_t__ PageCount; int /*<<< orphan*/  PageList; } ;
typedef  int /*<<< orphan*/ * PUSHORT ;
typedef  TYPE_1__* PEMS_HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  AllocBitmap ; 
 TYPE_1__* CreateHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EMS_STATUS_INSUFFICIENT_PAGES ; 
 int /*<<< orphan*/  EMS_STATUS_NO_MORE_HANDLES ; 
 int /*<<< orphan*/  EMS_STATUS_SUCCESS ; 
 int /*<<< orphan*/  EMS_STATUS_ZERO_PAGES ; 
 int /*<<< orphan*/  EmsFree (int /*<<< orphan*/ ) ; 
 TYPE_2__* EmsPageTable ; 
 int /*<<< orphan*/  InsertTailList (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ RtlFindNextForwardRunClear (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  RtlSetBits (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 

__attribute__((used)) static UCHAR EmsAlloc(USHORT NumPages, PUSHORT Handle)
{
    ULONG i, CurrentIndex = 0;
    PEMS_HANDLE HandleEntry;

    if (NumPages == 0) return EMS_STATUS_ZERO_PAGES;

    HandleEntry = CreateHandle(Handle);
    if (!HandleEntry)  return EMS_STATUS_NO_MORE_HANDLES;

    while (HandleEntry->PageCount < NumPages)
    {
        ULONG RunStart;
        ULONG RunSize = RtlFindNextForwardRunClear(&AllocBitmap, CurrentIndex, &RunStart);

        if (RunSize == 0)
        {
            /* Free what's been allocated already and report failure */
            EmsFree(*Handle);
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
            EmsPageTable[RunStart + i].Handle = *Handle;
            InsertTailList(&HandleEntry->PageList, &EmsPageTable[RunStart + i].Entry);
        }
    }

    return EMS_STATUS_SUCCESS;
}