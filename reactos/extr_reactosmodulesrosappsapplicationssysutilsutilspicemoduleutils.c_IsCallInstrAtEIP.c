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
typedef  int /*<<< orphan*/  ULONG ;
typedef  int* PUCHAR ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int /*<<< orphan*/  CurrentCS ; 
 int /*<<< orphan*/  CurrentEIP ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENTER_FUNC () ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLinearAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsRangeValid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  LEAVE_FUNC () ; 
 int /*<<< orphan*/  TRUE ; 

BOOLEAN IsCallInstrAtEIP(void)
{
PUCHAR linear;
BOOLEAN result=FALSE;

    ENTER_FUNC();
	DPRINT((0,"IsCallInstrAtEIP()\n"));

	linear=(PUCHAR)GetLinearAddress(CurrentCS,CurrentEIP);
	if(IsRangeValid((ULONG)linear,2))
	{
		if(*linear== 0xE8 || // call
		   (*linear== 0xFF && ( ((*(linear+1)>>3)&0x7)==0x2 || ((*(linear+1)>>3)&0x7)==0x3) ) || // call
		   *linear== 0x9A || // call
		   *linear== 0xF2 || // REP
		   *linear== 0xF3)   // REP
			result=TRUE;
	}

    LEAVE_FUNC();

	return result;
}