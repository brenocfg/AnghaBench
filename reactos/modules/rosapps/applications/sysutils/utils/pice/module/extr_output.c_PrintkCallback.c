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
typedef  scalar_t__ ULONG_PTR ;
typedef  int ULONG ;
struct TYPE_2__ {int /*<<< orphan*/  Buffer; } ;
typedef  scalar_t__* PULONG ;
typedef  TYPE_1__* PANSI_STRING ;
typedef  int /*<<< orphan*/  LPSTR ;
typedef  int /*<<< orphan*/  CHAR ;

/* Variables and functions */
 scalar_t__ CurrentEIP ; 
 int /*<<< orphan*/  CurrentESP ; 
 int /*<<< orphan*/  CurrentSS ; 
 int /*<<< orphan*/  DPRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int GetLinearAddress (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IsAddressValid (int) ; 
 scalar_t__ PICE_KdpPrintString ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bInPrintk ; 

void PrintkCallback(void)
{
	LPSTR fmt,args;
	ULONG ulAddress;
	ULONG countArgs,i,len;
	PANSI_STRING temp;
  CHAR buf[128];

	DPRINT((0,"In PrintkCallback\n"));

	bInPrintk = TRUE;

	// get the linear address of stack where string resides
	ulAddress = GetLinearAddress(CurrentSS,CurrentESP);
	if(ulAddress)
	{
		DPRINT((0,"In PrintkCallback: ulAddress: %x\n", ulAddress));
		if(IsAddressValid(ulAddress+sizeof(char *)) )
		{
			//KdpPrintString has PANSI_STRING as a parameter
			temp = (PANSI_STRING)*(PULONG)(ulAddress+sizeof(char *));
    	DPRINT((0,"PrintkCallback: %s\n", temp->Buffer));
      /* Call our version of KdpPrintString() */
			CurrentEIP = (ULONG_PTR)PICE_KdpPrintString;
		}
	}
	bInPrintk = FALSE;
}