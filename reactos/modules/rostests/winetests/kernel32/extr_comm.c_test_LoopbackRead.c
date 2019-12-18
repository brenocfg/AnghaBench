#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timeouts ;
typedef  int /*<<< orphan*/  tbuf ;
typedef  int /*<<< orphan*/  rbuf ;
struct TYPE_8__ {int ReadTotalTimeoutConstant; } ;
struct TYPE_7__ {int BaudRate; int ByteSize; void* StopBits; void* fDtrControl; void* fRtsControl; void* Parity; } ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  TYPE_1__ DCB ;
typedef  TYPE_2__ COMMTIMEOUTS ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 void* DTR_CONTROL_ENABLE ; 
 int EV_RXCHAR ; 
 int EV_TXEMPTY ; 
 int /*<<< orphan*/  FALSE ; 
 int FASTBAUD ; 
 int /*<<< orphan*/  GetCommState (scalar_t__,TYPE_1__*) ; 
 int GetTickCount () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 void* NOPARITY ; 
 void* ONESTOPBIT ; 
 void* RTS_CONTROL_ENABLE ; 
 int /*<<< orphan*/  ReadFile (scalar_t__,char*,int,int*,int /*<<< orphan*/ *) ; 
 int SLOWBAUD ; 
 int /*<<< orphan*/  SetCommMask (scalar_t__,int) ; 
 int /*<<< orphan*/  SetCommState (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  SetCommTimeouts (scalar_t__,TYPE_2__*) ; 
 int TIMEDELTA ; 
 int TIMEOUT ; 
 int /*<<< orphan*/  WaitCommEvent (scalar_t__,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  WriteFile (scalar_t__,char*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  loopback_txd_rxd ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ test_OpenComm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void test_LoopbackRead(void)
{
    HANDLE hcom;
    DCB dcb;
    COMMTIMEOUTS timeouts;
    char rbuf[32];
    DWORD before, after, diff, read, read1, written, evtmask=0, i;
    BOOL res;
    char tbuf[]="test_LoopbackRead";

    if (!loopback_txd_rxd) return;

    hcom = test_OpenComm(FALSE);
    if (hcom == INVALID_HANDLE_VALUE) return;

    trace("Starting test_LoopbackRead\n");
    ok(GetCommState(hcom, &dcb), "GetCommState failed\n");
    dcb.BaudRate = FASTBAUD;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.fRtsControl=RTS_CONTROL_ENABLE;
    dcb.fDtrControl=DTR_CONTROL_ENABLE;
    dcb.StopBits = ONESTOPBIT;
    ok(SetCommState(hcom, &dcb), "SetCommState failed\n");

    ZeroMemory( &timeouts, sizeof(timeouts));
    timeouts.ReadTotalTimeoutConstant = TIMEOUT;
    ok(SetCommTimeouts(hcom, &timeouts),"SetCommTimeouts failed\n");

    ok(SetCommMask(hcom, EV_TXEMPTY), "SetCommMask failed\n");

    before = GetTickCount();
    ok(WriteFile(hcom,tbuf,sizeof(tbuf),&written, NULL), "WriteFile failed\n");
    after = GetTickCount();
    ok(written == sizeof(tbuf),"WriteFile %d bytes written\n", written);
    diff = after -before;

    /* make sure all bytes are written, so Readfile will succeed in one call*/
    ok(WaitCommEvent(hcom, &evtmask, NULL), "WaitCommEvent failed\n");
    before = GetTickCount();
    ok(evtmask == EV_TXEMPTY,
                 "WaitCommEvent: Unexpected EvtMask 0x%08x, expected 0x%08x\n",
		 evtmask, EV_TXEMPTY);
    trace("Write %d ms WaitCommEvent EV_TXEMPTY %d ms\n", diff, before- after);

    read=0;
    ok(ReadFile(hcom, rbuf, sizeof(rbuf), &read, NULL), "Readfile failed\n");
    ok(read == sizeof(tbuf),"ReadFile read %d bytes, expected \"%s\"\n", read,rbuf);

    /* Now do the same with a slower Baud rate.
       As we request more characters than written, we will hit the timeout
    */

    ok(GetCommState(hcom, &dcb), "GetCommState failed\n");
    dcb.BaudRate = 9600;
    dcb.ByteSize = 8;
    dcb.Parity = NOPARITY;
    dcb.fRtsControl=RTS_CONTROL_ENABLE;
    dcb.fDtrControl=DTR_CONTROL_ENABLE;
    dcb.StopBits = ONESTOPBIT;
    ok(SetCommState(hcom, &dcb), "SetCommState failed\n");

    ok(SetCommMask(hcom, EV_RXCHAR), "SetCommMask failed\n");
    ok(WriteFile(hcom,tbuf,sizeof(tbuf),&written, NULL), "WriteFile failed\n");
    ok(written == sizeof(tbuf),"WriteFile %d bytes written\n", written);

    trace("WaitCommEventEV_RXCHAR\n");
    ok(WaitCommEvent(hcom, &evtmask, NULL), "WaitCommEvent failed\n");
    ok(evtmask == EV_RXCHAR, "WaitCommEvent: Unexpected EvtMask 0x%08x, expected 0x%08x\n",
       evtmask, EV_RXCHAR);

    before = GetTickCount();
    res = ReadFile(hcom, rbuf, sizeof(rbuf), &read, NULL);
    after = GetTickCount();
    ok(res, "Readfile failed\n");
    ok(read == sizeof(tbuf),"ReadFile read %d bytes\n", read);
    diff = after - before;
    trace("Readfile for %d chars took %d ms\n", read, diff);
    ok( (diff > TIMEOUT - TIMEDELTA) && (diff < TIMEOUT + TIMEDELTA),
	"Timedout Wait took %d ms, expected around %d\n", diff, TIMEOUT);

    /* now do a plain read with slow speed
     * This will result in several low level reads and a timeout to happen
     */
    dcb.BaudRate = SLOWBAUD;
    ok(SetCommState(hcom, &dcb), "SetCommState failed\n");
    ok(WriteFile(hcom,tbuf,sizeof(tbuf),&written, NULL), "WriteFile failed\n");
    before = GetTickCount();
    read = 0;
    read1 =0;
    i=0;
    do 
    {
	res = ReadFile(hcom, rbuf+read, sizeof(rbuf)-read, &read1, NULL);
	ok(res, "Readfile failed\n");
	read += read1;
	i++;
    }
    while ((read < sizeof(tbuf)) && (i <10));
    after =  GetTickCount();
    ok( read == sizeof(tbuf),"ReadFile read %d bytes\n", read);
    trace("Plain Read for %d char at %d baud took %d ms\n", read, SLOWBAUD, after-before);

    CloseHandle(hcom);
}