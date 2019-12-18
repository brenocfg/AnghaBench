#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  VOID ;
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ENABLE_MOUSE_INPUT ; 
 scalar_t__ GetConsoleMode (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ MousePresent ; 
 int /*<<< orphan*/  SetConsoleMode (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static VOID EnableExtraHardware(HANDLE ConsoleInput)
{
    DWORD ConInMode;

    if (GetConsoleMode(ConsoleInput, &ConInMode))
    {
#if 0
        // GetNumberOfConsoleMouseButtons();
        // GetSystemMetrics(SM_CMOUSEBUTTONS);
        // GetSystemMetrics(SM_MOUSEPRESENT);
        if (MousePresent)
        {
#endif
            /* Support mouse input events if there is a mouse on the system */
            ConInMode |= ENABLE_MOUSE_INPUT;
#if 0
        }
        else
        {
            /* Do not support mouse input events if there is no mouse on the system */
            ConInMode &= ~ENABLE_MOUSE_INPUT;
        }
#endif

        SetConsoleMode(ConsoleInput, ConInMode);
    }
}