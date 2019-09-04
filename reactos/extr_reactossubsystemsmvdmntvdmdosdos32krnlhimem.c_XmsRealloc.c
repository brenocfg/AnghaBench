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
typedef  scalar_t__ WORD ;
typedef  scalar_t__ ULONG ;
typedef  int /*<<< orphan*/  UCHAR ;
struct TYPE_4__ {scalar_t__ Address; scalar_t__ Size; scalar_t__ LockCount; } ;
typedef  TYPE_1__* PXMS_HANDLE ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  AllocBitmap ; 
 int /*<<< orphan*/  FreeBlocks ; 
 TYPE_1__* GetXmsHandleRecord (scalar_t__) ; 
 scalar_t__ REAL_TO_PHYS (scalar_t__) ; 
 scalar_t__ RtlAreBitsClear (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  RtlClearBits (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 scalar_t__ RtlFindNextForwardRunClear (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/  RtlMoveMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  RtlSetBits (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ValidateXmsHandle (TYPE_1__*) ; 
 scalar_t__ XMS_ADDRESS ; 
 scalar_t__ XMS_BLOCKS ; 
 scalar_t__ XMS_BLOCK_SIZE ; 
 int /*<<< orphan*/  XMS_STATUS_INVALID_HANDLE ; 
 int /*<<< orphan*/  XMS_STATUS_LOCKED ; 
 int /*<<< orphan*/  XMS_STATUS_OUT_OF_MEMORY ; 
 int /*<<< orphan*/  XMS_STATUS_SUCCESS ; 

__attribute__((used)) static UCHAR XmsRealloc(WORD Handle, WORD NewSize)
{
    DWORD BlockNumber;
    PXMS_HANDLE HandleEntry = GetXmsHandleRecord(Handle);
    DWORD CurrentIndex = 0;
    ULONG RunStart;
    ULONG RunSize;

    if (!ValidateXmsHandle(HandleEntry))
        return XMS_STATUS_INVALID_HANDLE;

    if (HandleEntry->LockCount)
        return XMS_STATUS_LOCKED;

    /* Get the block number */
    BlockNumber = (HandleEntry->Address - XMS_ADDRESS) / XMS_BLOCK_SIZE;

    if (NewSize < HandleEntry->Size)
    {
        /* Just reduce the size of this block */
        RtlClearBits(&AllocBitmap, BlockNumber + NewSize, HandleEntry->Size - NewSize);
        FreeBlocks += HandleEntry->Size - NewSize;
        HandleEntry->Size = NewSize;
    }
    else if (NewSize > HandleEntry->Size)
    {
        /* Check if we can expand in-place */
        if (RtlAreBitsClear(&AllocBitmap,
                            BlockNumber + HandleEntry->Size,
                            NewSize - HandleEntry->Size))
        {
            /* Just increase the size of this block */
            RtlSetBits(&AllocBitmap,
                       BlockNumber + HandleEntry->Size,
                       NewSize - HandleEntry->Size);
            FreeBlocks -= NewSize - HandleEntry->Size;
            HandleEntry->Size = NewSize;

            /* We're done */
            return XMS_STATUS_SUCCESS;
        }

        /* Deallocate the current block range */
        RtlClearBits(&AllocBitmap, BlockNumber, HandleEntry->Size);

        /* Find a new place for this block */
        while (CurrentIndex < XMS_BLOCKS)
        {
            RunSize = RtlFindNextForwardRunClear(&AllocBitmap, CurrentIndex, &RunStart);
            if (RunSize == 0) break;

            if (RunSize >= NewSize)
            {
                /* Allocate the new range */
                RtlSetBits(&AllocBitmap, RunStart, NewSize);

                /* Move the data to the new location */
                RtlMoveMemory((PVOID)REAL_TO_PHYS(XMS_ADDRESS + RunStart * XMS_BLOCK_SIZE),
                              (PVOID)REAL_TO_PHYS(HandleEntry->Address),
                              HandleEntry->Size * XMS_BLOCK_SIZE);

                /* Update the handle entry */
                HandleEntry->Address = XMS_ADDRESS + RunStart * XMS_BLOCK_SIZE;
                HandleEntry->Size = NewSize;

                /* Update the free block counter */
                FreeBlocks -= NewSize - HandleEntry->Size;

                return XMS_STATUS_SUCCESS;
            }

            /* Keep searching */
            CurrentIndex = RunStart + RunSize;
        }

        /* Restore the old block range */
        RtlSetBits(&AllocBitmap, BlockNumber, HandleEntry->Size);
        return XMS_STATUS_OUT_OF_MEMORY;
    }
    
    return XMS_STATUS_SUCCESS;
}