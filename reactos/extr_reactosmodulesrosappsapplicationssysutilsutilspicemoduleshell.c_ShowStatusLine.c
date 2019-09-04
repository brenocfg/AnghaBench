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
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_5__ {scalar_t__ y; } ;
struct TYPE_4__ {scalar_t__ ImageFileName; } ;
typedef  TYPE_1__* PEPROCESS ;
typedef  scalar_t__ LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_CAPTION ; 
 int /*<<< orphan*/  COLOR_TEXT ; 
 int /*<<< orphan*/  ClrLine (scalar_t__) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 TYPE_1__* IoGetCurrentProcess () ; 
 scalar_t__ IsAddressValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 size_t OUTPUT_WINDOW ; 
 int /*<<< orphan*/  PICE_sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  PutChar (int /*<<< orphan*/ ,int,scalar_t__) ; 
 int /*<<< orphan*/  ResetColor () ; 
 int /*<<< orphan*/  SetBackgroundColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetForegroundColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tempShell ; 
 TYPE_2__* wWindow ; 

void ShowStatusLine(void)
{
	PEPROCESS pCurrentProcess = IoGetCurrentProcess();
    LPSTR pProcessName;

    ENTER_FUNC();

    if(IsAddressValid((ULONG)pCurrentProcess))
    {
        SetForegroundColor(COLOR_TEXT);
	    SetBackgroundColor(COLOR_CAPTION);

		ClrLine(wWindow[OUTPUT_WINDOW].y-1);

        pProcessName = pCurrentProcess->ImageFileName;
        if(IsAddressValid((ULONG)pProcessName) )
        {
		    PICE_sprintf(tempShell,
                    " PROCESS(%.8X \"%s\") ",
                    (ULONG)pCurrentProcess,pProcessName);
        }
        else
        {
		    PICE_sprintf(tempShell,
                    " PROCESS(%.8X) ",
                    (ULONG)pCurrentProcess);
        }
		PutChar(tempShell,1,wWindow[OUTPUT_WINDOW].y-1);

        ResetColor();
    }

    LEAVE_FUNC();
}