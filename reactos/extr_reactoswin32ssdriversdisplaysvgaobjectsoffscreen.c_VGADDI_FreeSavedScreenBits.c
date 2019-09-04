#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_7__ {int /*<<< orphan*/ * Flink; int /*<<< orphan*/ * Blink; } ;
struct TYPE_6__ {TYPE_3__ ListEntry; scalar_t__ Size; scalar_t__ Free; } ;
typedef  TYPE_1__* PSAVED_SCREEN_BITS ;

/* Variables and functions */
 TYPE_1__* CONTAINING_RECORD (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EngFreeMem (TYPE_1__*) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  RemoveEntryList (TYPE_3__*) ; 
 int /*<<< orphan*/  SAVED_SCREEN_BITS ; 
 int /*<<< orphan*/  SavedBitsList ; 
 scalar_t__ TRUE ; 

VOID
VGADDI_FreeSavedScreenBits(PSAVED_SCREEN_BITS SavedBits)
{
    SavedBits->Free = TRUE;

    if (SavedBits->ListEntry.Blink != &SavedBitsList)
    {
        PSAVED_SCREEN_BITS Previous;

        Previous = CONTAINING_RECORD(SavedBits->ListEntry.Blink,
                                     SAVED_SCREEN_BITS, ListEntry);
        if (Previous->Free)
        {
            Previous->Size += SavedBits->Size;
            RemoveEntryList(&SavedBits->ListEntry);
            EngFreeMem(SavedBits);
            SavedBits = Previous;
        }
    }
    if (SavedBits->ListEntry.Flink != &SavedBitsList)
    {
        PSAVED_SCREEN_BITS Next;

        Next = CONTAINING_RECORD(SavedBits->ListEntry.Flink, SAVED_SCREEN_BITS,
                                 ListEntry);
        if (Next->Free)
        {
            SavedBits->Size += Next->Size;
            RemoveEntryList(&SavedBits->ListEntry);
            EngFreeMem(SavedBits);
        }
    }
}