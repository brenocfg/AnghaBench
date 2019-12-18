#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int WORD ;
struct TYPE_8__ {int /*<<< orphan*/  LastErrorCode; } ;
struct TYPE_7__ {int UmbChainStart; } ;
struct TYPE_6__ {char BlockType; scalar_t__ Size; } ;
typedef  TYPE_1__* PDOS_MCB ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT1 (char*) ; 
 int /*<<< orphan*/  ERROR_ARENA_TRASHED ; 
 TYPE_1__* SEGMENT_TO_MCB (int) ; 
 TYPE_4__* Sda ; 
 TYPE_3__* SysVars ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ValidateMcb (TYPE_1__*) ; 

WORD DosGetPreviousUmb(WORD UmbSegment)
{
    PDOS_MCB CurrentMcb;
    WORD Segment, PrevSegment = 0; // FIXME: or use UmbChainStart ??

    if (SysVars->UmbChainStart == 0xFFFF)
        return 0;

    /* Start scanning the UMB chain */
    Segment = SysVars->UmbChainStart;
    while (TRUE)
    {
        /* Get a pointer to the MCB */
        CurrentMcb = SEGMENT_TO_MCB(Segment);

        /* Make sure it's valid */
        if (!ValidateMcb(CurrentMcb))
        {
            DPRINT1("The UMB DOS memory arena is corrupted!\n");
            Sda->LastErrorCode = ERROR_ARENA_TRASHED;
            return 0;
        }

        /* We went over the UMB segment, quit */
        if (Segment >= UmbSegment) break;

        PrevSegment = Segment;

        /* If this was the last MCB in the chain, quit */
        if (CurrentMcb->BlockType == 'Z') break;

        /* Otherwise, update the segment and continue */
        Segment += CurrentMcb->Size + 1;
    }

    return PrevSegment;
}