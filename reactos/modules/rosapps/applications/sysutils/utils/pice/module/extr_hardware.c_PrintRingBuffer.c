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
typedef  scalar_t__ ULONG ;
struct TYPE_2__ {scalar_t__ y; int usCurX; } ;

/* Variables and functions */
 int /*<<< orphan*/  ClrLine (scalar_t__) ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Home (size_t) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 scalar_t__ LINES_IN_BUFFER ; 
 scalar_t__ LinesInRingBuffer () ; 
 size_t OUTPUT_WINDOW ; 
 int /*<<< orphan*/  OUTPUT_WINDOW_UNBUFFERED ; 
 int /*<<< orphan*/  Print (int /*<<< orphan*/ ,char*) ; 
 char** aBuffers ; 
 scalar_t__ bSuspendPrintRingBuffer ; 
 scalar_t__ ulInPos ; 
 scalar_t__ ulOldDelta ; 
 TYPE_1__* wWindow ; 

void PrintRingBuffer(ULONG ulLines)
{
	ULONG ulDelta = LinesInRingBuffer();
	ULONG ulOutPos,i=0;

//    ENTER_FUNC();

	if(bSuspendPrintRingBuffer)
    {
        DPRINT((0,"PrintRingBuffer(): suspended\n"));
        LEAVE_FUNC();
        return;
    }

	if(!ulDelta)
    {
        DPRINT((0,"PrintRingBuffer(): no lines in ring buffer\n"));
        LEAVE_FUNC();
		return;
    }

    if(ulDelta<ulOldDelta)
    {
        DPRINT((0,"PrintRingBuffer(): lines already output\n"));
        LEAVE_FUNC();
        return;
    }

    ulOldDelta = ulDelta;

	if(ulDelta < ulLines)
    {
        DPRINT((0,"PrintRingBuffer(): less lines than requested: ulDelta: %x, ulLines: %x\n", ulDelta, ulLines));
		ulLines = ulDelta;
    }

	ulOutPos = (ulInPos-ulLines)%LINES_IN_BUFFER;
    DPRINT((0,"PrintRingBuffer(): ulOutPos = %u\n",ulOutPos));

    Home(OUTPUT_WINDOW);

	while(ulLines--)
	{
        ClrLine(wWindow[OUTPUT_WINDOW].y+i);
		Print(OUTPUT_WINDOW_UNBUFFERED,aBuffers[ulOutPos]);
	    i++;
		ulOutPos = (ulOutPos+1)%LINES_IN_BUFFER;
	}

    if(aBuffers[ulOutPos][0]==':')
    {
        ClrLine(wWindow[OUTPUT_WINDOW].y+i);
		Print(OUTPUT_WINDOW_UNBUFFERED,aBuffers[ulOutPos]);
    	wWindow[OUTPUT_WINDOW].usCurX = 1;
    }

//    LEAVE_FUNC();
}