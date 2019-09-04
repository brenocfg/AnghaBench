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
typedef  scalar_t__ WORD ;
struct TYPE_5__ {scalar_t__ CurrentPsp; } ;
struct TYPE_4__ {scalar_t__ HandleTableSize; void* HandleTablePtr; int /*<<< orphan*/  HandleTable; } ;
typedef  TYPE_1__* PDOS_PSP ;
typedef  int /*<<< orphan*/  LPBYTE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 scalar_t__ DEFAULT_JFT_SIZE ; 
 scalar_t__ DosAllocateMemory (scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DosFreeMemory (scalar_t__) ; 
 int /*<<< orphan*/  DosResizeMemory (scalar_t__,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FAR_POINTER (void*) ; 
 scalar_t__ HIWORD (void*) ; 
 int LOWORD (void*) ; 
 void* MAKELONG (int,scalar_t__) ; 
 int /*<<< orphan*/  RtlCopyMemory (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 TYPE_1__* SEGMENT_TO_PSP (scalar_t__) ; 
 int /*<<< orphan*/  SEG_OFF_TO_PTR (scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_2__* Sda ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN DosResizeHandleTable(WORD NewSize)
{
    PDOS_PSP PspBlock;
    LPBYTE HandleTable;
    WORD Segment;

    /* Get the PSP block */
    PspBlock = SEGMENT_TO_PSP(Sda->CurrentPsp);

    if (NewSize == PspBlock->HandleTableSize)
    {
        /* No change */
        return TRUE;
    }

    if (PspBlock->HandleTableSize > DEFAULT_JFT_SIZE)
    {
        /* Get the segment of the current table */
        Segment = (LOWORD(PspBlock->HandleTablePtr) >> 4) + HIWORD(PspBlock->HandleTablePtr);

        if (NewSize <= DEFAULT_JFT_SIZE)
        {
            /* Get the current handle table */
            HandleTable = FAR_POINTER(PspBlock->HandleTablePtr);

            /* Copy it to the PSP */
            RtlCopyMemory(PspBlock->HandleTable, HandleTable, NewSize);

            /* Free the memory */
            DosFreeMemory(Segment);

            /* Update the handle table pointer and size */
            PspBlock->HandleTableSize = NewSize;
            PspBlock->HandleTablePtr = MAKELONG(0x18, Sda->CurrentPsp);
        }
        else
        {
            /* Resize the memory */
            if (!DosResizeMemory(Segment, NewSize, NULL))
            {
                /* Unable to resize, try allocating it somewhere else */
                Segment = DosAllocateMemory(NewSize, NULL);
                if (Segment == 0) return FALSE;

                /* Get the new handle table */
                HandleTable = SEG_OFF_TO_PTR(Segment, 0);

                /* Copy the handles to the new table */
                RtlCopyMemory(HandleTable,
                              FAR_POINTER(PspBlock->HandleTablePtr),
                              PspBlock->HandleTableSize);

                /* Update the handle table pointer */
                PspBlock->HandleTablePtr = MAKELONG(0, Segment);
            }

            /* Update the handle table size */
            PspBlock->HandleTableSize = NewSize;
        }
    }
    else if (NewSize > DEFAULT_JFT_SIZE)
    {
        Segment = DosAllocateMemory(NewSize, NULL);
        if (Segment == 0) return FALSE;

        /* Get the new handle table */
        HandleTable = SEG_OFF_TO_PTR(Segment, 0);

        /* Copy the handles from the PSP to the new table */
        RtlCopyMemory(HandleTable,
                      FAR_POINTER(PspBlock->HandleTablePtr),
                      PspBlock->HandleTableSize);

        /* Update the handle table pointer and size */
        PspBlock->HandleTableSize = NewSize;
        PspBlock->HandleTablePtr = MAKELONG(0, Segment);
    }

    return TRUE;
}