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
typedef  int /*<<< orphan*/  VOID ;
struct TYPE_4__ {scalar_t__ ServerEvent; scalar_t__ ProcessHandle; scalar_t__ CurDirsLength; struct TYPE_4__* CurrentDirs; } ;
typedef  TYPE_1__* PVDM_CONSOLE_RECORD ;

/* Variables and functions */
 int /*<<< orphan*/  BaseSrvHeap ; 
 int /*<<< orphan*/  NtClose (scalar_t__) ; 
 int /*<<< orphan*/  RtlFreeHeap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

VOID BaseSrvDestroyConsoleRecord(PVDM_CONSOLE_RECORD ConsoleRecord)
{
    if (ConsoleRecord->CurrentDirs != NULL)
    {
        /* Free the current directories */
        RtlFreeHeap(BaseSrvHeap, 0, ConsoleRecord->CurrentDirs);
        ConsoleRecord->CurrentDirs = NULL;
        ConsoleRecord->CurDirsLength = 0;
    }

    /* Close the process handle */
    if (ConsoleRecord->ProcessHandle)
        NtClose(ConsoleRecord->ProcessHandle);

    /* Close the event handle */
    if (ConsoleRecord->ServerEvent)
        NtClose(ConsoleRecord->ServerEvent);

    /* Remove the console record */
    // RemoveEntryList(&ConsoleRecord->Entry);
    RtlFreeHeap(BaseSrvHeap, 0, ConsoleRecord);

}