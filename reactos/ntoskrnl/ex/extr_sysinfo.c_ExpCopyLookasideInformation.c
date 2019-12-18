#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  scalar_t__ ULONG ;
struct TYPE_11__ {scalar_t__ FreeHits; scalar_t__ TotalFrees; scalar_t__ AllocateHits; scalar_t__ TotalAllocates; scalar_t__ FreeMisses; scalar_t__ AllocateMisses; int /*<<< orphan*/  Size; int /*<<< orphan*/  Tag; int /*<<< orphan*/  Type; int /*<<< orphan*/  MaximumDepth; int /*<<< orphan*/  Depth; } ;
struct TYPE_10__ {struct TYPE_10__* Flink; } ;
struct TYPE_9__ {scalar_t__ FreeMisses; scalar_t__ AllocateMisses; int /*<<< orphan*/  Size; int /*<<< orphan*/  Tag; int /*<<< orphan*/  Type; scalar_t__ TotalFrees; scalar_t__ TotalAllocates; int /*<<< orphan*/  MaximumDepth; int /*<<< orphan*/  CurrentDepth; } ;
typedef  scalar_t__* PULONG ;
typedef  TYPE_1__* PSYSTEM_LOOKASIDE_INFORMATION ;
typedef  TYPE_2__* PLIST_ENTRY ;
typedef  TYPE_3__* PGENERAL_LOOKASIDE ;
typedef  scalar_t__ BOOLEAN ;

/* Variables and functions */
 TYPE_3__* CONTAINING_RECORD (TYPE_2__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  GENERAL_LOOKASIDE ; 

__attribute__((used)) static
VOID
ExpCopyLookasideInformation(
    PSYSTEM_LOOKASIDE_INFORMATION *InfoPointer,
    PULONG RemainingPointer,
    PLIST_ENTRY ListHead,
    BOOLEAN ListUsesMisses)

{
    PSYSTEM_LOOKASIDE_INFORMATION Info;
    PGENERAL_LOOKASIDE LookasideList;
    PLIST_ENTRY ListEntry;
    ULONG Remaining;

    /* Get info pointer and remaining count of free array element */
    Info = *InfoPointer;
    Remaining = *RemainingPointer;

    /* Loop as long as we have lookaside lists and free array elements */
    for (ListEntry = ListHead->Flink;
         (ListEntry != ListHead) && (Remaining > 0);
         ListEntry = ListEntry->Flink, Remaining--)
    {
        LookasideList = CONTAINING_RECORD(ListEntry, GENERAL_LOOKASIDE, ListEntry);

        /* Fill the next array element */
        Info->CurrentDepth = LookasideList->Depth;
        Info->MaximumDepth = LookasideList->MaximumDepth;
        Info->TotalAllocates = LookasideList->TotalAllocates;
        Info->TotalFrees = LookasideList->TotalFrees;
        Info->Type = LookasideList->Type;
        Info->Tag = LookasideList->Tag;
        Info->Size = LookasideList->Size;

        /* Check how the lists track misses/hits */
        if (ListUsesMisses)
        {
            /* Copy misses */
            Info->AllocateMisses = LookasideList->AllocateMisses;
            Info->FreeMisses = LookasideList->FreeMisses;
        }
        else
        {
            /* Calculate misses */
            Info->AllocateMisses = LookasideList->TotalAllocates
                                   - LookasideList->AllocateHits;
            Info->FreeMisses = LookasideList->TotalFrees
                               - LookasideList->FreeHits;
        }
    }

    /* Return the updated pointer and remaining count */
    *InfoPointer = Info;
    *RemainingPointer = Remaining;
}