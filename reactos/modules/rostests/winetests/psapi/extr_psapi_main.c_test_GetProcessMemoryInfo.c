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
typedef  int /*<<< orphan*/  pmc ;
typedef  int /*<<< orphan*/  PROCESS_MEMORY_COUNTERS ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_INSUFFICIENT_BUFFER ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ GetLastError () ; 
 int GetProcessMemoryInfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/ * hpQI ; 
 int /*<<< orphan*/ * hpSR ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_GetProcessMemoryInfo(void)
{
    PROCESS_MEMORY_COUNTERS pmc;
    DWORD ret;

    SetLastError(0xdeadbeef);
    ret = GetProcessMemoryInfo(NULL, &pmc, sizeof(pmc));
    ok(!ret, "GetProcessMemoryInfo should fail\n");
    ok(GetLastError() == ERROR_INVALID_HANDLE, "expected error=ERROR_INVALID_HANDLE but got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = GetProcessMemoryInfo(hpSR, &pmc, sizeof(pmc));
    ok(!ret, "GetProcessMemoryInfo should fail\n");
    ok(GetLastError() == ERROR_ACCESS_DENIED, "expected error=ERROR_ACCESS_DENIED but got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = GetProcessMemoryInfo(hpQI, &pmc, sizeof(pmc)-1);
    ok(!ret, "GetProcessMemoryInfo should fail\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER, "expected error=ERROR_INSUFFICIENT_BUFFER but got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = GetProcessMemoryInfo(hpQI, &pmc, sizeof(pmc));
    ok(ret == 1, "failed with %d\n", GetLastError());
}