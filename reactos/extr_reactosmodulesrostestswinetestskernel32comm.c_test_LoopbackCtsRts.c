#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dcb ;
struct TYPE_4__ {scalar_t__ fRtsControl; } ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  TYPE_1__ DCB ;

/* Variables and functions */
 int /*<<< orphan*/  CLRRTS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  EscapeCommFunction (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCommModemStatus (scalar_t__,int*) ; 
 int /*<<< orphan*/  GetCommState (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MS_CTS_ON ; 
 int MS_DSR_ON ; 
 int MS_RING_ON ; 
 int MS_RLSD_ON ; 
 scalar_t__ RTS_CONTROL_HANDSHAKE ; 
 int /*<<< orphan*/  SETRTS ; 
 int /*<<< orphan*/  loopback_rts_cts ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ test_OpenComm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_LoopbackCtsRts(void)
{
    HANDLE hcom;
    DWORD ModemStat = 0, defaultStat = 0;
    DCB dcb;

    if (!loopback_rts_cts) return;

    hcom = test_OpenComm(FALSE);
    if (hcom == INVALID_HANDLE_VALUE) return;

    memset (&dcb, 0, sizeof (dcb));
    ok(GetCommState(hcom, &dcb), "GetCommState failed\n");
    if (dcb.fRtsControl == RTS_CONTROL_HANDSHAKE)
    {
	trace("RTS_CONTROL_HANDSHAKE is set, so don't manipulate RTS\n");
	CloseHandle(hcom);
	return;
    }
    ok(GetCommModemStatus(hcom, &defaultStat), "GetCommModemStatus failed\n");
    /* XP returns some values in the low nibble, so mask them out*/
    defaultStat &= MS_CTS_ON|MS_DSR_ON|MS_RING_ON|MS_RLSD_ON;
    if(defaultStat & MS_CTS_ON)
    {
	ok(EscapeCommFunction(hcom, CLRRTS), "EscapeCommFunction failed to clear RTS\n");
	ok(GetCommModemStatus(hcom, &ModemStat), "GetCommModemStatus failed\n");
	ok ((ModemStat & MS_CTS_ON) == 0, "CTS didn't react: 0x%04x,  expected 0x%04x\n",
	    ModemStat, (defaultStat & ~MS_CTS_ON));
	ok(EscapeCommFunction(hcom, SETRTS), "EscapeCommFunction failed to clear RTS\n");
	ok(GetCommModemStatus(hcom, &ModemStat), "GetCommModemStatus failed\n");
	ok (ModemStat ==  defaultStat, "Failed to restore CTS: 0x%04x, expected 0x%04x\n",
	    ModemStat, defaultStat);
    }
    else
    {
	ok(EscapeCommFunction(hcom, SETRTS), "EscapeCommFunction failed to set RTS\n");
	ok(GetCommModemStatus(hcom, &ModemStat), "GetCommModemStatus failed\n");
	ok ((ModemStat & MS_CTS_ON) == MS_CTS_ON,
            "CTS didn't react: 0x%04x,  expected 0x%04x\n",
	    ModemStat, (defaultStat | MS_CTS_ON));
	ok(EscapeCommFunction(hcom, CLRRTS), "EscapeCommFunction failed to clear RTS\n");
	ok(GetCommModemStatus(hcom, &ModemStat), "GetCommModemStatus failed\n");
	ok (ModemStat ==  defaultStat, "Failed to restore CTS: 0x%04x, expected 0x%04x\n",
	    ModemStat, defaultStat);
    }

    CloseHandle(hcom);
}