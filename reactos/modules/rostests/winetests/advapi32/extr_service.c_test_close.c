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
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  int BOOL ;

/* Variables and functions */
 int CloseServiceHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * OpenSCManagerA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SC_MANAGER_CONNECT ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_close(void)
{
    SC_HANDLE handle;
    BOOL ret;

    /* NULL handle */
    SetLastError(0xdeadbeef);
    ret = CloseServiceHandle(NULL);
    ok(!ret, "Expected failure\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE, "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());

    /* TODO: Add some tests with invalid handles. These produce errors on Windows but crash on Wine */

    /* Proper call */
    handle = OpenSCManagerA(NULL, NULL, SC_MANAGER_CONNECT);
    SetLastError(0xdeadbeef);
    ret = CloseServiceHandle(handle);
    ok(ret, "Expected success got error %u\n", GetLastError());
}