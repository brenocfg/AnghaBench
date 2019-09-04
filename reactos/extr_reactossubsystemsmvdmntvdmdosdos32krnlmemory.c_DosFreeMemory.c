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
struct TYPE_5__ {scalar_t__ BlockType; scalar_t__ OwnerPsp; } ;
typedef  TYPE_1__* PDOS_MCB ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (char*,scalar_t__) ; 
 int /*<<< orphan*/  DosMemValidate () ; 
 void* ERROR_INVALID_BLOCK ; 
 int /*<<< orphan*/  FALSE ; 
 TYPE_1__* SEGMENT_TO_MCB (scalar_t__) ; 
 TYPE_3__* Sda ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ValidateMcb (TYPE_1__*) ; 

BOOLEAN DosFreeMemory(WORD BlockData)
{
    PDOS_MCB Mcb = SEGMENT_TO_MCB(BlockData - 1);

    DPRINT("DosFreeMemory: BlockData 0x%04X\n", BlockData);

    if (BlockData == 0)
    {
        Sda->LastErrorCode = ERROR_INVALID_BLOCK;
        return FALSE;
    }

    DosMemValidate();

    /* Make sure the MCB is valid */
    if (!ValidateMcb(Mcb))
    {
        DPRINT("MCB block type '%c' not valid!\n", Mcb->BlockType);
        Sda->LastErrorCode = ERROR_INVALID_BLOCK;
        return FALSE;
    }

    /* Mark the block as free */
    Mcb->OwnerPsp = 0;

    return TRUE;
}