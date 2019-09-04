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
typedef  int ULONG ;
typedef  int /*<<< orphan*/  PVOID ;
typedef  int* PULONG ;
typedef  int /*<<< orphan*/  LPSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FindFunctionByAddress (int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IsRangeValid (int,int) ; 
 int /*<<< orphan*/  OUTPUT_WINDOW ; 
 int /*<<< orphan*/  PICE_sprintf (int /*<<< orphan*/ ,char*,int,int,...) ; 
 int /*<<< orphan*/  Print (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PutStatusText (char*) ; 
 scalar_t__ WaitForKey () ; 
 int /*<<< orphan*/  tempUtil ; 

void IntelStackWalk(ULONG pc,ULONG ebp,ULONG esp)
{
    PULONG pFrame, pPrevFrame;
    LPSTR pSymbolName;

    DPRINT((0,"IntelStackWalk(): pc = %X ebp = %X esp = %X\n",pc,ebp,esp));

    pFrame = pPrevFrame = (PULONG)ebp;

    PutStatusText("EIP      FRAME    NAME\n");
    while(1)
    {
        DPRINT((0,"IntelStackWalk(): pFrame = %X pPrevFrame = %X pc =%X\n",(ULONG)pFrame,(ULONG)pPrevFrame,pc));
        if ( ( (ULONG)pFrame & 3 )    ||
             ( (pFrame <= pPrevFrame) ) )
        {
            DPRINT((0,"IntelStackWalk(): pFrame is either unaligned or not less than previous\n"));
            if( !IsRangeValid((ULONG)pFrame, sizeof(PVOID)*2) )
            {
                DPRINT((0,"IntelStackWalk(): pFrame not valid pointer!\n"));
                break;
            }
        }

        if((pSymbolName = FindFunctionByAddress(pc,NULL,NULL)) )
		    PICE_sprintf(tempUtil,"%08X %08X %s\n",pc, (ULONG)pFrame,pSymbolName);
		else
		    PICE_sprintf(tempUtil,"%08X %08X\n",pc, (ULONG)pFrame);
        Print(OUTPUT_WINDOW,tempUtil);
        if(WaitForKey()==FALSE)break;

        pc = pFrame[1];

        pPrevFrame = pFrame;

        pFrame = (PULONG)pFrame[0]; // proceed to next higher frame on stack
    }
}