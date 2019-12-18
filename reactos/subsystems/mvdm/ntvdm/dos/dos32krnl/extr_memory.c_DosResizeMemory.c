#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ WORD ;
struct TYPE_6__ {void* LastErrorCode; } ;
struct TYPE_5__ {scalar_t__ OwnerPsp; scalar_t__ Size; char BlockType; } ;
typedef  TYPE_1__* PDOS_MCB ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__,...) ; 
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  DosCombineFreeBlocks (scalar_t__) ; 
 int /*<<< orphan*/  DosMemValidate () ; 
 void* ERROR_ARENA_TRASHED ; 
 void* ERROR_INVALID_BLOCK ; 
 void* ERROR_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* SEGMENT_TO_MCB (scalar_t__) ; 
 TYPE_3__* Sda ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ValidateMcb (TYPE_1__*) ; 

BOOLEAN DosResizeMemory(WORD BlockData, WORD NewSize, WORD *MaxAvailable)
{
    BOOLEAN Success = TRUE;
    WORD Segment = BlockData - 1, ReturnSize = 0, NextSegment;
    PDOS_MCB Mcb = SEGMENT_TO_MCB(Segment), NextMcb;

    DPRINT("DosResizeMemory: BlockData 0x%04X, NewSize 0x%04X\n",
           BlockData, NewSize);

    DosMemValidate();

    /* Make sure this is a valid and allocated block */
    if (BlockData == 0 || !ValidateMcb(Mcb) || Mcb->OwnerPsp == 0)
    {
        Sda->LastErrorCode = ERROR_INVALID_BLOCK;
        Success = FALSE;
        goto Done;
    }

    ReturnSize = Mcb->Size;

    /* Check if we need to expand or contract the block */
    if (NewSize > Mcb->Size)
    {
        /* We can't expand the last block */
        if (Mcb->BlockType == 'Z')
        {
            DPRINT("Cannot expand memory block 0x%04X: this is the last block (size 0x%04X)!\n", Segment, Mcb->Size);
            Sda->LastErrorCode = ERROR_NOT_ENOUGH_MEMORY;
            Success = FALSE;
            goto Done;
        }

        /* Get the pointer and segment of the next MCB */
        NextSegment = Segment + Mcb->Size + 1;
        NextMcb = SEGMENT_TO_MCB(NextSegment);

        /* Make sure it's valid */
        if (!ValidateMcb(NextMcb))
        {
            DPRINT1("The DOS memory arena is corrupted!\n");
            Sda->LastErrorCode = ERROR_ARENA_TRASHED;
            return FALSE;
        }

        /* Make sure the next segment is free */
        if (NextMcb->OwnerPsp != 0)
        {
            DPRINT("Cannot expand memory block 0x%04X: next segment is not free!\n", Segment);
            Sda->LastErrorCode = ERROR_NOT_ENOUGH_MEMORY;
            Success = FALSE;
            goto Done;
        }

        /* Combine this free block with adjoining free blocks */
        DosCombineFreeBlocks(NextSegment);

        /* Set the maximum possible size of the block */
        ReturnSize += NextMcb->Size + 1;

        if (ReturnSize < NewSize)
        {
            DPRINT("Cannot expand memory block 0x%04X: insufficient free segments available!\n", Segment);
            Sda->LastErrorCode = ERROR_NOT_ENOUGH_MEMORY;
            Success = FALSE;
            goto Done;
        }

        /* Maximize the current block */
        Mcb->Size = ReturnSize;
        Mcb->BlockType = NextMcb->BlockType;

        /* Invalidate the next block */
        NextMcb->BlockType = 'I';

        /* Check if the block is larger than requested */
        if (Mcb->Size > NewSize)
        {
            DPRINT("Block too large, reducing size from 0x%04X to 0x%04X\n",
                   Mcb->Size, NewSize);

            /* It is, split it into two blocks */
            NextMcb = SEGMENT_TO_MCB(Segment + NewSize + 1);

            /* Initialize the new MCB structure */
            NextMcb->BlockType = Mcb->BlockType;
            NextMcb->Size = Mcb->Size - NewSize - 1;
            NextMcb->OwnerPsp = 0;

            /* Update the current block */
            Mcb->BlockType = 'M';
            Mcb->Size = NewSize;
        }
    }
    else if (NewSize < Mcb->Size)
    {
        DPRINT("Shrinking block from 0x%04X to 0x%04X\n",
               Mcb->Size, NewSize);

        /* Just split the block */
        NextSegment = Segment + NewSize + 1;
        NextMcb = SEGMENT_TO_MCB(NextSegment);
        NextMcb->BlockType = Mcb->BlockType;
        NextMcb->Size = Mcb->Size - NewSize - 1;
        NextMcb->OwnerPsp = 0;

        /* Update the MCB */
        Mcb->BlockType = 'M';
        Mcb->Size = NewSize;

        /* Combine this free block with adjoining free blocks */
        DosCombineFreeBlocks(NextSegment);
    }

Done:
    /* Check if the operation failed */
    if (!Success)
    {
        DPRINT("DosResizeMemory FAILED. Maximum available: 0x%04X\n", ReturnSize);

        /* Return the maximum possible size */
        if (MaxAvailable) *MaxAvailable = ReturnSize;
    }

    DosMemValidate();

    return Success;
}