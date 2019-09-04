#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  overlapped_w ;
typedef  int /*<<< orphan*/  overlapped ;
struct TYPE_6__ {scalar_t__ hEvent; } ;
typedef  TYPE_1__ OVERLAPPED ;
typedef  scalar_t__ HANDLE ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 scalar_t__ CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_IO_PENDING ; 
 scalar_t__ EV_RXCHAR ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetOverlappedResult (scalar_t__,TYPE_1__*,scalar_t__*,scalar_t__) ; 
 scalar_t__ GetTickCount () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetCommMask (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  Sleep (int) ; 
 int TIMEDELTA ; 
 int TIMEOUT ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ WAIT_OBJECT_0 ; 
 scalar_t__ WaitCommEvent (scalar_t__,scalar_t__*,TYPE_1__*) ; 
 scalar_t__ WaitForSingleObjectEx (scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ WriteFile (scalar_t__,char*,int,scalar_t__*,TYPE_1__*) ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_1__*,int) ; 
 int /*<<< orphan*/  loopback_txd_rxd ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ test_OpenComm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace (char*,...) ; 

__attribute__((used)) static void test_WaitRx(void)
{
    OVERLAPPED overlapped, overlapped_w;
    HANDLE hcom, hComPortEvent, hComWriteEvent;
    DWORD before, after, after1, diff, success_wait = FALSE, success_write;
    DWORD err_wait, err_write, written, evtmask=0;

    if (!loopback_txd_rxd) return;

    hcom = test_OpenComm(TRUE);
    if (hcom == INVALID_HANDLE_VALUE) return;

    ok(SetCommMask(hcom, EV_RXCHAR), "SetCommMask failed\n");
    hComPortEvent =  CreateEventW( NULL, TRUE, FALSE, NULL );
    ok(hComPortEvent != 0, "CreateEvent failed\n");
    ZeroMemory( &overlapped, sizeof(overlapped));
    overlapped.hEvent = hComPortEvent;

    hComWriteEvent = CreateEventW( NULL, TRUE, FALSE, NULL );
    ok(hComWriteEvent != NULL, "CreateEvent res %d\n", GetLastError());
    ZeroMemory( &overlapped_w, sizeof(overlapped_w));
    overlapped_w.hEvent = hComWriteEvent;

    before = GetTickCount();
    success_wait = WaitCommEvent(hcom, &evtmask, &overlapped);
    err_wait = GetLastError();
    after = GetTickCount();
    trace("Success 0x%08x err %d evtmask 0x%08x\n", success_wait, err_wait, evtmask);
    ok(success_wait || err_wait == ERROR_IO_PENDING, "overlapped WaitCommEvent failed\n");
    trace("overlapped WaitCommEvent returned.\n");

    success_write= WriteFile(hcom, "X", 1, &written, &overlapped_w);
    err_write = GetLastError();
    ok(success_write || err_write == ERROR_IO_PENDING,
       "overlapped WriteFile failed, err %d\n",
       err_write);

    if (!success_write && (err_write == ERROR_IO_PENDING)) {
      success_write = WaitForSingleObjectEx(hComWriteEvent, TIMEOUT, TRUE);
      err_write = GetLastError();
      ok(success_write == WAIT_OBJECT_0, "WaitForSingleObjectEx, res %d, err %d\n",
	 success_write, err_write);
    }
    Sleep(TIMEOUT >>1);
    success_write = GetOverlappedResult(hcom, &overlapped_w, &written, FALSE);
    err_write = GetLastError();

    trace("Write after Wait res 0x%08x err %d\n",success_write, err_write);
    ok(success_write && written ==1, "Write after Wait res 0x%08x err %d\n",
       success_write, err_write);

    if (!success_wait && (err_wait == ERROR_IO_PENDING)) {
      success_wait = WaitForSingleObjectEx(hComPortEvent, TIMEOUT, TRUE);
      err_wait = GetLastError();
      ok(success_wait == WAIT_OBJECT_0, "wait hComPortEvent, res 0x%08x, err %d\n",
	 success_wait, err_wait);
    }
    success_wait = GetOverlappedResult(hcom, &overlapped, &written, FALSE);
    err_wait = GetLastError();
    after1 = GetTickCount();
    trace("Success 0x%08x err %d evtmask 0x%08x diff1 %d, diff2 %d\n",
	  success_wait, err_wait, evtmask, after-before, after1-before);

    ok(evtmask & EV_RXCHAR, "Detect  EV_RXCHAR: 0x%08x, expected 0x%08x\n",
       evtmask, EV_RXCHAR);
    diff = after1 - before;
    ok ((diff > (TIMEOUT>>1) -TIMEDELTA) && (diff < (TIMEOUT>>1) + TIMEDELTA),
	"Unexpected time %d, expected around %d\n", diff, TIMEOUT>>1);

    CloseHandle(hcom);
}