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
struct TYPE_3__ {scalar_t__ fDtrControl; } ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  TYPE_1__ DCB ;

/* Variables and functions */
 int /*<<< orphan*/  CLRDTR ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ DTR_CONTROL_HANDSHAKE ; 
 int /*<<< orphan*/  EscapeCommFunction (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetCommModemStatus (scalar_t__,int*) ; 
 int /*<<< orphan*/  GetCommState (scalar_t__,TYPE_1__*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MS_CTS_ON ; 
 int MS_DSR_ON ; 
 int MS_RING_ON ; 
 int MS_RLSD_ON ; 
 int /*<<< orphan*/  SETDTR ; 
 int /*<<< orphan*/  loopback_dtr_ring ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ test_OpenComm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*) ; 

__attribute__((used)) static void test_LoopbackDtrRing(void)
{
    HANDLE hcom;
    DWORD ModemStat = 0, defaultStat = 0;
    DCB dcb;

    if (!loopback_dtr_ring) return;

    hcom = test_OpenComm(FALSE);
    if (hcom == INVALID_HANDLE_VALUE) return;

    ok(GetCommState(hcom, &dcb), "GetCommState failed\n");
    if (dcb.fDtrControl == DTR_CONTROL_HANDSHAKE)
    {
	trace("DTR_CONTROL_HANDSHAKE is set, so don't manipulate DTR\n");
	CloseHandle(hcom);
	return;
    }
    ok(GetCommModemStatus(hcom, &defaultStat), "GetCommModemStatus failed\n");
    /* XP returns some values in the low nibble, so mask them out*/
    defaultStat &= MS_CTS_ON|MS_DSR_ON|MS_RING_ON|MS_RLSD_ON;
    if(defaultStat & MS_RING_ON)
    {
	ok(EscapeCommFunction(hcom, CLRDTR), "EscapeCommFunction failed to clear DTR\n");
	ok(GetCommModemStatus(hcom, &ModemStat), "GetCommModemStatus failed\n");
	ok ((ModemStat & MS_RING_ON) == 0, "RING didn't react: 0x%04x,  expected 0x%04x\n",
	    ModemStat, (defaultStat & ~MS_RING_ON));
	ok(EscapeCommFunction(hcom, SETDTR), "EscapeCommFunction failed to set DTR\n");
	ok(GetCommModemStatus(hcom, &ModemStat), "GetCommModemStatus failed\n");
	ok (ModemStat ==  defaultStat, "Failed to restore RING: 0x%04x, expected 0x%04x\n",
	    ModemStat, defaultStat);
    }
    else
    {
	ok(EscapeCommFunction(hcom, SETDTR), "EscapeCommFunction failed to set DTR\n");
	ok(GetCommModemStatus(hcom, &ModemStat), "GetCommModemStatus failed\n");
	ok ((ModemStat & MS_RING_ON) == MS_RING_ON,
            "RING didn't react: 0x%04x,expected 0x%04x\n",
	    ModemStat, (defaultStat | MS_RING_ON));
	ok(EscapeCommFunction(hcom, CLRDTR), "EscapeCommFunction failed to clear DTR\n");
	ok(GetCommModemStatus(hcom, &ModemStat), "GetCommModemStatus failed\n");
	ok (ModemStat ==  defaultStat, "Failed to restore RING: 0x%04x, expected 0x%04x\n",
	    ModemStat, defaultStat);
    }

    CloseHandle(hcom);
}