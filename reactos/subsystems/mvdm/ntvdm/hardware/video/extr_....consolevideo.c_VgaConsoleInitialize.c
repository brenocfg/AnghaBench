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
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  ConsoleInfo ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetConsoleCursorInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  GetConsoleScreenBufferInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsConsoleHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  OrgConsoleBufferInfo ; 
 int /*<<< orphan*/  OrgConsoleCursorInfo ; 
 int /*<<< orphan*/  SetActiveScreenBuffer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * TextConsoleBuffer ; 

BOOLEAN VgaConsoleInitialize(HANDLE TextHandle)
{
    /*
     * Initialize the console video by saving the default
     * text-mode console output handle, if it is valid.
     */
    if (!IsConsoleHandle(TextHandle)) return FALSE;
    TextConsoleBuffer = TextHandle;

    /* Save the original cursor and console screen buffer information */
    if (!GetConsoleCursorInfo(TextConsoleBuffer, &OrgConsoleCursorInfo) ||
        !GetConsoleScreenBufferInfo(TextConsoleBuffer, &OrgConsoleBufferInfo))
    {
        TextConsoleBuffer = NULL;
        return FALSE;
    }
    ConsoleInfo = OrgConsoleBufferInfo;

    /* Switch to the text buffer, but do not enter into a text mode */
    SetActiveScreenBuffer(TextConsoleBuffer);

    return TRUE;
}