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
typedef  int /*<<< orphan*/  nameW ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ComputerNameDnsDomain ; 
 int /*<<< orphan*/  ComputerNameDnsFullyQualified ; 
 int /*<<< orphan*/  ComputerNameDnsHostname ; 
 int /*<<< orphan*/  ComputerNameNetBIOS ; 
 scalar_t__ ERROR_MORE_DATA ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int pGetComputerNameExW (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetComputerNameExW(void)
{
    DWORD size;
    BOOL ret;
    LPWSTR nameW;
    DWORD error;

    if (!pGetComputerNameExW)
    {
        win_skip("GetComputerNameExW function not implemented\n");
        return;
    }

    size = 0;
    ret = pGetComputerNameExW(ComputerNameDnsDomain, (LPWSTR)0xdeadbeef, &size);
    error = GetLastError();
    ok(!ret && error == ERROR_MORE_DATA, "GetComputerNameExW should have failed with ERROR_MORE_DATA instead of %d\n", error);
    nameW = HeapAlloc(GetProcessHeap(), 0, size * sizeof(nameW[0]));
    ok(nameW != NULL, "HeapAlloc failed with error %d\n", GetLastError());
    ret = pGetComputerNameExW(ComputerNameDnsDomain, nameW, &size);
    ok(ret, "GetComputerNameExW(ComputerNameDnsDomain) failed with error %d\n", GetLastError());
    HeapFree(GetProcessHeap(), 0, nameW);

    size = 0;
    ret = pGetComputerNameExW(ComputerNameDnsFullyQualified, (LPWSTR)0xdeadbeef, &size);
    error = GetLastError();
    ok(!ret && error == ERROR_MORE_DATA, "GetComputerNameExW should have failed with ERROR_MORE_DATA instead of %d\n", error);
    nameW = HeapAlloc(GetProcessHeap(), 0, size * sizeof(nameW[0]));
    ok(nameW != NULL, "HeapAlloc failed with error %d\n", GetLastError());
    ret = pGetComputerNameExW(ComputerNameDnsFullyQualified, nameW, &size);
    ok(ret, "GetComputerNameExW(ComputerNameDnsFullyQualified) failed with error %d\n", GetLastError());
    HeapFree(GetProcessHeap(), 0, nameW);

    size = 0;
    ret = pGetComputerNameExW(ComputerNameDnsHostname, (LPWSTR)0xdeadbeef, &size);
    error = GetLastError();
    ok(!ret && error == ERROR_MORE_DATA, "GetComputerNameExW should have failed with ERROR_MORE_DATA instead of %d\n", error);
    nameW = HeapAlloc(GetProcessHeap(), 0, size * sizeof(nameW[0]));
    ok(nameW != NULL, "HeapAlloc failed with error %d\n", GetLastError());
    ret = pGetComputerNameExW(ComputerNameDnsHostname, nameW, &size);
    ok(ret, "GetComputerNameExW(ComputerNameDnsHostname) failed with error %d\n", GetLastError());
    HeapFree(GetProcessHeap(), 0, nameW);

    size = 0;
    ret = pGetComputerNameExW(ComputerNameNetBIOS, (LPWSTR)0xdeadbeef, &size);
    error = GetLastError();
    ok(!ret && error == ERROR_MORE_DATA, "GetComputerNameExW should have failed with ERROR_MORE_DATA instead of %d\n", error);
    nameW = HeapAlloc(GetProcessHeap(), 0, size * sizeof(nameW[0]));
    ok(nameW != NULL, "HeapAlloc failed with error %d\n", GetLastError());
    ret = pGetComputerNameExW(ComputerNameNetBIOS, nameW, &size);
    ok(ret, "GetComputerNameExW(ComputerNameNetBIOS) failed with error %d\n", GetLastError());
    HeapFree(GetProcessHeap(), 0, nameW);
}