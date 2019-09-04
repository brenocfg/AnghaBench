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

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int GetLastError () ; 
 int /*<<< orphan*/ * INVALID_HANDLE_VALUE ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  SetupCloseInfFile (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_close_inf_file(void)
{
    SetLastError(0xdeadbeef);
    SetupCloseInfFile(NULL);
    ok(GetLastError() == 0xdeadbeef ||
        GetLastError() == ERROR_INVALID_PARAMETER, /* Win9x, WinMe */
        "Expected 0xdeadbeef, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    SetupCloseInfFile(INVALID_HANDLE_VALUE);
    ok(GetLastError() == 0xdeadbeef ||
        GetLastError() == ERROR_INVALID_PARAMETER, /* Win9x, WinMe */
        "Expected 0xdeadbeef, got %u\n", GetLastError());
}