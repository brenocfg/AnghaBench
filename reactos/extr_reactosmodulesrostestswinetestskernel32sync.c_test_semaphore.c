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
 int /*<<< orphan*/ * CreateSemaphoreA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,char*) ; 
 scalar_t__ ERROR_ALREADY_EXISTS ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * OpenSemaphoreA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * OpenSemaphoreW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SEMAPHORE_ALL_ACCESS ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_semaphore(void)
{
    HANDLE handle, handle2;

    /* test case sensitivity */

    SetLastError(0xdeadbeef);
    handle = CreateSemaphoreA(NULL, 0, 1, __FILE__ ": Test Semaphore");
    ok(handle != NULL, "CreateSemaphore failed with error %u\n", GetLastError());
    ok(GetLastError() == 0, "wrong error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    handle2 = CreateSemaphoreA(NULL, 0, 1, __FILE__ ": Test Semaphore");
    ok( handle2 != NULL, "CreateSemaphore failed with error %d\n", GetLastError());
    ok( GetLastError() == ERROR_ALREADY_EXISTS, "wrong error %u\n", GetLastError());
    CloseHandle( handle2 );

    SetLastError(0xdeadbeef);
    handle2 = CreateSemaphoreA(NULL, 0, 1, __FILE__ ": TEST SEMAPHORE");
    ok( handle2 != NULL, "CreateSemaphore failed with error %d\n", GetLastError());
    ok( GetLastError() == 0, "wrong error %u\n", GetLastError());
    CloseHandle( handle2 );

    SetLastError(0xdeadbeef);
    handle2 = OpenSemaphoreA( SEMAPHORE_ALL_ACCESS, FALSE, __FILE__ ": Test Semaphore");
    ok( handle2 != NULL, "OpenSemaphore failed with error %d\n", GetLastError());
    CloseHandle( handle2 );

    SetLastError(0xdeadbeef);
    handle2 = OpenSemaphoreA( SEMAPHORE_ALL_ACCESS, FALSE, __FILE__ ": TEST SEMAPHORE");
    ok( !handle2, "OpenSemaphore succeeded\n");
    ok( GetLastError() == ERROR_FILE_NOT_FOUND, "wrong error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    handle2 = OpenSemaphoreA( SEMAPHORE_ALL_ACCESS, FALSE, NULL );
    ok( !handle2, "OpenSemaphore succeeded\n");
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    handle2 = OpenSemaphoreW( SEMAPHORE_ALL_ACCESS, FALSE, NULL );
    ok( !handle2, "OpenSemaphore succeeded\n");
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError());

    CloseHandle( handle );
}