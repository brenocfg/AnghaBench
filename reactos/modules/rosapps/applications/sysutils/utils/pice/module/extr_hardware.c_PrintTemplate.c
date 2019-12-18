#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int USHORT ;
struct TYPE_2__ {int y; int cy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COLOR_CAPTION ; 
 int /*<<< orphan*/  COLOR_TEXT ; 
 int /*<<< orphan*/  ClrLine (int) ; 
 size_t DATA_WINDOW ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 size_t OUTPUT_WINDOW ; 
 int /*<<< orphan*/  PrintCaption () ; 
 int /*<<< orphan*/  PrintLogo (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetColor () ; 
 size_t SOURCE_WINDOW ; 
 int /*<<< orphan*/  SetBackgroundColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetForegroundColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ShowRunningMsg () ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__* wWindow ; 

void PrintTemplate(void)
{
    USHORT i,j;

	ENTER_FUNC();

    ResetColor();

    for(j=0;j<4;j++)
    {
	    for(i=wWindow[j].y;i<(wWindow[j].y+wWindow[j].cy);i++)
        {
		    ClrLine(i);
        }
    }

    PrintCaption();

	SetForegroundColor(COLOR_TEXT);
	SetBackgroundColor(COLOR_CAPTION);

	ClrLine(wWindow[DATA_WINDOW].y-1);
	ClrLine(wWindow[SOURCE_WINDOW].y-1);
	ClrLine(wWindow[OUTPUT_WINDOW].y-1);

    ResetColor();

	ShowRunningMsg();
    PrintLogo(TRUE);

	LEAVE_FUNC();
}