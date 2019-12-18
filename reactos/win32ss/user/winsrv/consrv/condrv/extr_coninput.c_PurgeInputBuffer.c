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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {int /*<<< orphan*/  InputEvents; } ;
struct TYPE_5__ {TYPE_1__ InputBuffer; } ;
typedef  int /*<<< orphan*/  PLIST_ENTRY ;
typedef  TYPE_2__* PCONSOLE ;

/* Variables and functions */
 int CONTAINING_RECORD (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConsoleFreeHeap (int) ; 
 int ConsoleInput ; 
 int Event ; 
 int /*<<< orphan*/  IsListEmpty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ListEntry ; 
 int /*<<< orphan*/  RemoveHeadList (int /*<<< orphan*/ *) ; 

__attribute__((used)) static VOID
PurgeInputBuffer(PCONSOLE Console)
{
    PLIST_ENTRY CurrentEntry;
    ConsoleInput* Event;

    while (!IsListEmpty(&Console->InputBuffer.InputEvents))
    {
        CurrentEntry = RemoveHeadList(&Console->InputBuffer.InputEvents);
        Event = CONTAINING_RECORD(CurrentEntry, ConsoleInput, ListEntry);
        ConsoleFreeHeap(Event);
    }

    // CloseHandle(Console->InputBuffer.ActiveEvent);
}