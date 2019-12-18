#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  Lock; } ;
struct TYPE_6__ {TYPE_2__* Console; } ;
typedef  TYPE_1__* PGUI_CONSOLE_DATA ;
typedef  TYPE_2__* PCONSOLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CONSOLE_RUNNING ; 
 int /*<<< orphan*/  CTRL_CLOSE_EVENT ; 
 int /*<<< orphan*/  ConDrvConsoleProcessCtrlEvent (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ConDrvValidateConsoleUnsafe (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LeaveCriticalSection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static BOOL
GuiConsoleHandleClose(PGUI_CONSOLE_DATA GuiData)
{
    PCONSOLE Console = GuiData->Console;

    if (!ConDrvValidateConsoleUnsafe(Console, CONSOLE_RUNNING, TRUE))
        return TRUE;

    // TODO: Prompt for termination ? (Warn the user about possible apps running in this console)

    /*
     * FIXME: Windows will wait up to 5 seconds for the thread to exit.
     * We shouldn't wait here, though, since the console lock is entered.
     * A copy of the thread list probably needs to be made.
     */
    ConDrvConsoleProcessCtrlEvent(Console, 0, CTRL_CLOSE_EVENT);

    LeaveCriticalSection(&Console->Lock);
    return FALSE;
}