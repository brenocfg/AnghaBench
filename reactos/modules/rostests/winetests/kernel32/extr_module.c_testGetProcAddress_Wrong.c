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
typedef  int /*<<< orphan*/ * HMODULE ;
typedef  scalar_t__ FARPROC ;

/* Variables and functions */
 scalar_t__ ERROR_MOD_NOT_FOUND ; 
 scalar_t__ ERROR_PROC_NOT_FOUND ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ GetProcAddress (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void testGetProcAddress_Wrong(void)
{
    FARPROC fp;

    SetLastError(0xdeadbeef);
    fp = GetProcAddress(NULL, "non_ex_call");
    ok( !fp, "non_ex_call should not be found\n");
    ok( GetLastError() == ERROR_PROC_NOT_FOUND, "Expected ERROR_PROC_NOT_FOUND, got %d\n", GetLastError() );

    SetLastError(0xdeadbeef);
    fp = GetProcAddress((HMODULE)0xdeadbeef, "non_ex_call");
    ok( !fp, "non_ex_call should not be found\n");
    ok( GetLastError() == ERROR_MOD_NOT_FOUND, "Expected ERROR_MOD_NOT_FOUND, got %d\n", GetLastError() );
}