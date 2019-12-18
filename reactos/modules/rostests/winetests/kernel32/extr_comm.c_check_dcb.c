#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int fDsrSensitivity; unsigned int fOutxDsrFlow; } ;
struct TYPE_6__ {scalar_t__ old_style; scalar_t__ result; } ;
typedef  TYPE_1__ TEST ;
typedef  unsigned int DWORD ;
typedef  TYPE_2__ DCB ;

/* Variables and functions */
 int /*<<< orphan*/  BaudRate ; 
 int /*<<< orphan*/  ByteSize ; 
 int /*<<< orphan*/  DCBlength ; 
 int /*<<< orphan*/  EofChar ; 
 int /*<<< orphan*/  ErrorChar ; 
 int /*<<< orphan*/  EvtChar ; 
 int /*<<< orphan*/  Parity ; 
 int /*<<< orphan*/  StopBits ; 
 int /*<<< orphan*/  XoffChar ; 
 int /*<<< orphan*/  XoffLim ; 
 int /*<<< orphan*/  XonChar ; 
 int /*<<< orphan*/  XonLim ; 
 int /*<<< orphan*/  check_dcb_member (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  check_dcb_member2 (int /*<<< orphan*/ ,unsigned int,char*) ; 
 int /*<<< orphan*/  fAbortOnError ; 
 int /*<<< orphan*/  fBinary ; 
 int /*<<< orphan*/  fDsrSensitivity ; 
 int /*<<< orphan*/  fDtrControl ; 
 int /*<<< orphan*/  fDummy2 ; 
 int /*<<< orphan*/  fErrorChar ; 
 int /*<<< orphan*/  fInX ; 
 int /*<<< orphan*/  fNull ; 
 int /*<<< orphan*/  fOutX ; 
 int /*<<< orphan*/  fOutxCtsFlow ; 
 int /*<<< orphan*/  fOutxDsrFlow ; 
 int /*<<< orphan*/  fParity ; 
 int /*<<< orphan*/  fRtsControl ; 
 int /*<<< orphan*/  fTXContinueOnXoff ; 
 int /*<<< orphan*/  wReserved ; 
 int /*<<< orphan*/  wReserved1 ; 

__attribute__((used)) static void check_dcb(const char *function, const TEST *ptest, int initial_value, const DCB *pdcb1, const DCB *pdcb2)
{
	/* DCBlength is a special case since Win 9x sets it but NT does not.
	   We will accept either as correct. */
	check_dcb_member2(DCBlength, (DWORD)sizeof(DCB), "%u");

	/* For old style control strings Win 9x does not set the next five members, NT does. */
	if(ptest->old_style && ptest->result)
	{
		check_dcb_member2(fOutxCtsFlow, ((unsigned int)initial_value & 1), "%u");
		check_dcb_member2(fDtrControl, ((unsigned int)initial_value & 3), "%u");
		check_dcb_member2(fOutX, ((unsigned int)initial_value & 1), "%u");
		check_dcb_member2(fInX, ((unsigned)initial_value & 1), "%u");
		check_dcb_member2(fRtsControl, ((unsigned)initial_value & 3), "%u");
	}
	else
	{
		check_dcb_member(fOutxCtsFlow, "%u");
		check_dcb_member(fDtrControl, "%u");
		check_dcb_member(fOutX, "%u");
		check_dcb_member(fInX, "%u");
		check_dcb_member(fRtsControl, "%u");
	}

	if(ptest->result)
	{
		/* For the idsr=xxx parameter, NT sets fDsrSensitivity, 9x sets
		   fOutxDsrFlow. */
		if(!ptest->old_style)
		{
			check_dcb_member2(fOutxDsrFlow, pdcb2->fDsrSensitivity, "%u");
			check_dcb_member2(fDsrSensitivity, pdcb2->fOutxDsrFlow, "%u");
		}
		else
		{
			/* For old style control strings Win 9x does not set the
			   fOutxDsrFlow member, NT does. */
			check_dcb_member2(fOutxDsrFlow, ((unsigned int)initial_value & 1), "%u");
			check_dcb_member(fDsrSensitivity, "%u");
		}
	}
	else
	{
		check_dcb_member(fOutxDsrFlow, "%u");
		check_dcb_member(fDsrSensitivity, "%u");
	}

	/* Check the result of the DCB members. */
	check_dcb_member(BaudRate, "%u");
	check_dcb_member(fBinary, "%u");
	check_dcb_member(fParity, "%u");
	check_dcb_member(fTXContinueOnXoff, "%u");
	check_dcb_member(fErrorChar, "%u");
	check_dcb_member(fNull, "%u");
	check_dcb_member(fAbortOnError, "%u");
	check_dcb_member(fDummy2, "%u");
	check_dcb_member(wReserved, "%u");
	check_dcb_member(XonLim, "%u");
	check_dcb_member(XoffLim, "%u");
	check_dcb_member(ByteSize, "%u");
	check_dcb_member(Parity, "%u");
	check_dcb_member(StopBits, "%u");
	check_dcb_member(XonChar, "%d");
	check_dcb_member(XoffChar, "%d");
	check_dcb_member(ErrorChar, "%d");
	check_dcb_member(EofChar, "%d");
	check_dcb_member(EvtChar, "%d");
	check_dcb_member(wReserved1, "%u");
}