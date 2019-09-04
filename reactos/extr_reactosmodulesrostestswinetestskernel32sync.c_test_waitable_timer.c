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
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateWaitableTimerA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ ERROR_ALREADY_EXISTS ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * OpenWaitableTimerA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * OpenWaitableTimerW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TIMER_ALL_ACCESS ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_waitable_timer(void)
{
    HANDLE handle, handle2;

    /* test case sensitivity */

    SetLastError(0xdeadbeef);
    handle = CreateWaitableTimerA(NULL, FALSE, __FILE__ ": Test WaitableTimer");
    ok(handle != NULL, "CreateWaitableTimer failed with error %u\n", GetLastError());
    ok(GetLastError() == 0, "wrong error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    handle2 = CreateWaitableTimerA(NULL, FALSE, __FILE__ ": Test WaitableTimer");
    ok( handle2 != NULL, "CreateWaitableTimer failed with error %d\n", GetLastError());
    ok( GetLastError() == ERROR_ALREADY_EXISTS, "wrong error %u\n", GetLastError());
    CloseHandle( handle2 );

    SetLastError(0xdeadbeef);
    handle2 = CreateWaitableTimerA(NULL, FALSE, __FILE__ ": TEST WAITABLETIMER");
    ok( handle2 != NULL, "CreateWaitableTimer failed with error %d\n", GetLastError());
    ok( GetLastError() == 0, "wrong error %u\n", GetLastError());
    CloseHandle( handle2 );

    SetLastError(0xdeadbeef);
    handle2 = OpenWaitableTimerA( TIMER_ALL_ACCESS, FALSE, __FILE__ ": Test WaitableTimer");
    ok( handle2 != NULL, "OpenWaitableTimer failed with error %d\n", GetLastError());
    CloseHandle( handle2 );

    SetLastError(0xdeadbeef);
    handle2 = OpenWaitableTimerA( TIMER_ALL_ACCESS, FALSE, __FILE__ ": TEST WAITABLETIMER");
    ok( !handle2, "OpenWaitableTimer succeeded\n");
    ok( GetLastError() == ERROR_FILE_NOT_FOUND, "wrong error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    handle2 = OpenWaitableTimerA( TIMER_ALL_ACCESS, FALSE, NULL );
    ok( !handle2, "OpenWaitableTimer failed with error %d\n", GetLastError());
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    handle2 = OpenWaitableTimerW( TIMER_ALL_ACCESS, FALSE, NULL );
    ok( !handle2, "OpenWaitableTimer failed with error %d\n", GetLastError());
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError());

    CloseHandle( handle );
}