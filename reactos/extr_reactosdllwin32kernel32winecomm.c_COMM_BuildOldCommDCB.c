#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int WCHAR ;
struct TYPE_3__ {int BaudRate; void* fRtsControl; void* fDtrControl; void* fOutxDsrFlow; void* fOutxCtsFlow; void* fOutX; void* fInX; int /*<<< orphan*/  StopBits; int /*<<< orphan*/  ByteSize; int /*<<< orphan*/  Parity; } ;
typedef  TYPE_1__* LPDCB ;
typedef  char* LPCWSTR ;
typedef  void* BOOL ;

/* Variables and functions */
 char* COMM_ParseByteSize (char*,int /*<<< orphan*/ *) ; 
 char* COMM_ParseNumber (char*,int*) ; 
 char* COMM_ParseParity (char*,int /*<<< orphan*/ *) ; 
 char* COMM_ParseStopBits (char*,int /*<<< orphan*/ *) ; 
 void* DTR_CONTROL_ENABLE ; 
 void* DTR_CONTROL_HANDSHAKE ; 
 void* FALSE ; 
 void* RTS_CONTROL_ENABLE ; 
 void* RTS_CONTROL_HANDSHAKE ; 
 void* TRUE ; 
 int toupperW (int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL COMM_BuildOldCommDCB(LPCWSTR device, LPDCB lpdcb)
{
	WCHAR last = 0;

	if(!(device = COMM_ParseNumber(device, &lpdcb->BaudRate)))
		return FALSE;
	
	switch(lpdcb->BaudRate)
	{
	case 11:
	case 30:
	case 60:
		lpdcb->BaudRate *= 10;
		break;
	case 12:
	case 24:
	case 48:
	case 96:
		lpdcb->BaudRate *= 100;
		break;
	case 19:
		lpdcb->BaudRate = 19200;
		break;
	}

	while(*device == ' ') device++;
	if(*device++ != ',') return FALSE;
	while(*device == ' ') device++;

	if(!(device = COMM_ParseParity(device, &lpdcb->Parity)))
		return FALSE;

	while(*device == ' ') device++;
	if(*device++ != ',') return FALSE;
	while(*device == ' ') device++;
		
	if(!(device = COMM_ParseByteSize(device, &lpdcb->ByteSize)))
		return FALSE;

	while(*device == ' ') device++;
	if(*device++ != ',') return FALSE;
	while(*device == ' ') device++;

	if(!(device = COMM_ParseStopBits(device, &lpdcb->StopBits)))
		return FALSE;

	/* The last parameter for flow control is optional. */
	while(*device == ' ') device++;
	if(*device == ',')
	{
		device++;
		while(*device == ' ') device++;
		if(*device) last = toupperW(*device++);
		while(*device == ' ') device++;
	}

	/* Win NT sets the flow control members based on (or lack of) the last
	   parameter.  Win 9x does not set these members. */
	switch(last)
	{
	case 0:
		lpdcb->fInX = FALSE;
		lpdcb->fOutX = FALSE;
		lpdcb->fOutxCtsFlow = FALSE;
		lpdcb->fOutxDsrFlow = FALSE;
		lpdcb->fDtrControl = DTR_CONTROL_ENABLE;
		lpdcb->fRtsControl = RTS_CONTROL_ENABLE;
		break;
	case 'X':
		lpdcb->fInX = TRUE;
		lpdcb->fOutX = TRUE;
		lpdcb->fOutxCtsFlow = FALSE;
		lpdcb->fOutxDsrFlow = FALSE;
		lpdcb->fDtrControl = DTR_CONTROL_ENABLE;
		lpdcb->fRtsControl = RTS_CONTROL_ENABLE;
		break;
	case 'P':
		lpdcb->fInX = FALSE;
		lpdcb->fOutX = FALSE;
		lpdcb->fOutxCtsFlow = TRUE;
		lpdcb->fOutxDsrFlow = TRUE;
		lpdcb->fDtrControl = DTR_CONTROL_HANDSHAKE;
		lpdcb->fRtsControl = RTS_CONTROL_HANDSHAKE;
		break;
	default:
		return FALSE;
	}

	/* This should be the end of the string. */
	if(*device) return FALSE;
	
	return TRUE;
}