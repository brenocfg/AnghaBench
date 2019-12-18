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
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DUPLICATE_SAME_ACCESS ; 
 int /*<<< orphan*/  DuplicateHandle (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/ * GetCurrentProcess () ; 
 int /*<<< orphan*/  GetCurrentProcessId () ; 
 int /*<<< orphan*/  GetCurrentThreadId () ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * OpenProcess (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * OpenThread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int PROCESS_ALL_ACCESS ; 
 int /*<<< orphan*/  PROCESS_ALL_ACCESS_NT4 ; 
 int PROCESS_QUERY_LIMITED_INFORMATION ; 
 int PROCESS_TERMINATE ; 
 int PROCESS_VM_READ ; 
 int SPECIFIC_RIGHTS_ALL ; 
 int STANDARD_RIGHTS_ALL ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  TEST_GRANTED_ACCESS (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TEST_GRANTED_ACCESS2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  THREAD_SET_THREAD_TOKEN ; 
 int /*<<< orphan*/  THREAD_TERMINATE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_process_security_child(void)
{
    HANDLE handle, handle1;
    BOOL ret;
    DWORD err;

    handle = OpenProcess( PROCESS_TERMINATE, FALSE, GetCurrentProcessId() );
    ok(handle != NULL, "OpenProcess(PROCESS_TERMINATE) with err:%d\n", GetLastError());
    TEST_GRANTED_ACCESS( handle, PROCESS_TERMINATE );

    ret = DuplicateHandle( GetCurrentProcess(), handle, GetCurrentProcess(),
                           &handle1, 0, TRUE, DUPLICATE_SAME_ACCESS );
    ok(ret, "duplicating handle err:%d\n", GetLastError());
    TEST_GRANTED_ACCESS( handle1, PROCESS_TERMINATE );

    CloseHandle( handle1 );

    SetLastError( 0xdeadbeef );
    ret = DuplicateHandle( GetCurrentProcess(), handle, GetCurrentProcess(),
                           &handle1, PROCESS_ALL_ACCESS, TRUE, 0 );
    err = GetLastError();
    ok(!ret && err == ERROR_ACCESS_DENIED, "duplicating handle should have failed "
       "with STATUS_ACCESS_DENIED, instead of err:%d\n", err);

    CloseHandle( handle );

    /* These two should fail - they are denied by ACL */
    handle = OpenProcess( PROCESS_VM_READ, FALSE, GetCurrentProcessId() );
    ok(handle == NULL, "OpenProcess(PROCESS_VM_READ) should have failed\n");
    handle = OpenProcess( PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId() );
    ok(handle == NULL, "OpenProcess(PROCESS_ALL_ACCESS) should have failed\n");

    /* Documented privilege elevation */
    ret = DuplicateHandle( GetCurrentProcess(), GetCurrentProcess(), GetCurrentProcess(),
                           &handle, 0, TRUE, DUPLICATE_SAME_ACCESS );
    ok(ret, "duplicating handle err:%d\n", GetLastError());
    TEST_GRANTED_ACCESS2( handle, PROCESS_ALL_ACCESS_NT4,
                          STANDARD_RIGHTS_ALL | SPECIFIC_RIGHTS_ALL );

    CloseHandle( handle );

    /* Same only explicitly asking for all access rights */
    ret = DuplicateHandle( GetCurrentProcess(), GetCurrentProcess(), GetCurrentProcess(),
                           &handle, PROCESS_ALL_ACCESS, TRUE, 0 );
    ok(ret, "duplicating handle err:%d\n", GetLastError());
    TEST_GRANTED_ACCESS2( handle, PROCESS_ALL_ACCESS_NT4,
                          PROCESS_ALL_ACCESS | PROCESS_QUERY_LIMITED_INFORMATION );
    ret = DuplicateHandle( GetCurrentProcess(), handle, GetCurrentProcess(),
                           &handle1, PROCESS_VM_READ, TRUE, 0 );
    ok(ret, "duplicating handle err:%d\n", GetLastError());
    TEST_GRANTED_ACCESS( handle1, PROCESS_VM_READ );
    CloseHandle( handle1 );
    CloseHandle( handle );

    /* Test thread security */
    handle = OpenThread( THREAD_TERMINATE, FALSE, GetCurrentThreadId() );
    ok(handle != NULL, "OpenThread(THREAD_TERMINATE) with err:%d\n", GetLastError());
    TEST_GRANTED_ACCESS( handle, PROCESS_TERMINATE );
    CloseHandle( handle );

    handle = OpenThread( THREAD_SET_THREAD_TOKEN, FALSE, GetCurrentThreadId() );
    ok(handle == NULL, "OpenThread(THREAD_SET_THREAD_TOKEN) should have failed\n");
}