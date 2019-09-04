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

/* Variables and functions */
 int /*<<< orphan*/  ConsoleShutdownHercules () ; 
 int /*<<< orphan*/  ConsoleShutdownSerial () ; 
 int /*<<< orphan*/  ConsoleShutdownVga () ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  KeStallExecutionProcessor (int) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
#define  TERMINAL_MODE_HERCULES_GRAPHICS 132 
#define  TERMINAL_MODE_HERCULES_TEXT 131 
#define  TERMINAL_MODE_NONE 130 
#define  TERMINAL_MODE_SERIAL 129 
#define  TERMINAL_MODE_VGA_TEXT 128 
 int eTerminalMode ; 

void ConsoleShutdown(void)
{
    ENTER_FUNC();

    // sleep for a few seconds
    KeStallExecutionProcessor(1000*5000);

	switch(eTerminalMode)
    {
        case TERMINAL_MODE_HERCULES_GRAPHICS:
            ConsoleShutdownHercules();
            break;
        case TERMINAL_MODE_HERCULES_TEXT:
            break;
        case TERMINAL_MODE_VGA_TEXT:
            ConsoleShutdownVga();
            break;
        case TERMINAL_MODE_SERIAL:
            ConsoleShutdownSerial();
            break;
        case TERMINAL_MODE_NONE:
        default:
            // fail
            break;
    }

    LEAVE_FUNC();
}