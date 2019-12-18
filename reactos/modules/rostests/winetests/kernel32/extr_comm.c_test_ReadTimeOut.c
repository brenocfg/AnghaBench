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
typedef  int /*<<< orphan*/  rbuf ;
struct TYPE_8__ {int ReadTotalTimeoutConstant; } ;
struct TYPE_7__ {int ByteSize; int /*<<< orphan*/  StopBits; int /*<<< orphan*/  fDtrControl; int /*<<< orphan*/  fRtsControl; int /*<<< orphan*/  Parity; int /*<<< orphan*/  BaudRate; } ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;
typedef  TYPE_1__ DCB ;
typedef  TYPE_2__ COMMTIMEOUTS ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int /*<<< orphan*/  DTR_CONTROL_ENABLE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FASTBAUD ; 
 int /*<<< orphan*/  GetCommState (scalar_t__,TYPE_1__*) ; 
 int GetLastError () ; 
 int GetTickCount () ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  NOPARITY ; 
 int /*<<< orphan*/  ONESTOPBIT ; 
 int /*<<< orphan*/  RTS_CONTROL_ENABLE ; 
 scalar_t__ ReadFile (scalar_t__,char*,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetCommState (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  SetCommTimeouts (scalar_t__,TYPE_2__*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int TIMEOUT ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_GetModemStatus (scalar_t__) ; 
 scalar_t__ test_OpenComm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_ReadTimeOut(void)
{
    HANDLE hcom;
    DCB dcb;
    COMMTIMEOUTS timeouts;
    char rbuf[32];
    DWORD before, after, read, timediff, LastError;
    BOOL res;

    hcom = test_OpenComm(FALSE);
    if (hcom == INVALID_HANDLE_VALUE) return;

    test_GetModemStatus(hcom);

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

    before = GetTickCount();
    SetLastError(0xdeadbeef);
    res = ReadFile(hcom, rbuf, sizeof(rbuf), &read, NULL);
    LastError = GetLastError();
    after = GetTickCount();
    ok( res == TRUE, "A timed-out read should return TRUE\n");
    ok( LastError == 0xdeadbeef, "err=%d\n", LastError);
    timediff = after - before;
    ok( timediff > TIMEOUT>>2 && timediff < TIMEOUT *2,
	"Unexpected TimeOut %d, expected %d\n", timediff, TIMEOUT);

    CloseHandle(hcom);
}