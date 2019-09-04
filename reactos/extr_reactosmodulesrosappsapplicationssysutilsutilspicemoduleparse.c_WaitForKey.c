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
struct TYPE_2__ {int cy; scalar_t__ y; } ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  BLACK ; 
 int /*<<< orphan*/  ClrLine (scalar_t__) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetKeyPolled () ; 
 size_t OUTPUT_WINDOW ; 
 int /*<<< orphan*/  PrintCursor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PrintRingBuffer (int) ; 
 int /*<<< orphan*/  PutChar (char*,int,scalar_t__) ; 
 scalar_t__ SCANCODE_ESC ; 
 int /*<<< orphan*/  SetBackgroundColor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SuspendPrintRingBuffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WHITE ; 
 scalar_t__ ucKeyPressedWhileIdle ; 
 scalar_t__ ulCountForWaitKey ; 
 TYPE_1__* wWindow ; 

BOOLEAN WaitForKey(void)
{
    BOOLEAN result=TRUE;

    if(ulCountForWaitKey == 0)
        SuspendPrintRingBuffer(TRUE);

    ulCountForWaitKey++;

	if(ulCountForWaitKey == (wWindow[OUTPUT_WINDOW].cy-1))
	{
        SuspendPrintRingBuffer(FALSE);

    	PrintRingBuffer(wWindow[OUTPUT_WINDOW].cy-1);

        ulCountForWaitKey = 0;

		SetBackgroundColor(WHITE);
		ClrLine(wWindow[OUTPUT_WINDOW].y+wWindow[OUTPUT_WINDOW].cy);
		PutChar(" Press any key to continue listing or press ESC to stop... ",1,wWindow[OUTPUT_WINDOW].y+wWindow[OUTPUT_WINDOW].cy);
		ucKeyPressedWhileIdle=0;
        while(!(ucKeyPressedWhileIdle=GetKeyPolled()))
		{
			PrintCursor(FALSE);
		}
		SetBackgroundColor(BLACK);
		// if ESCAPE then indicate retreat
		if(ucKeyPressedWhileIdle==SCANCODE_ESC)
		{
			result=FALSE;
		}
		ucKeyPressedWhileIdle=0;
	}


    return result;
}