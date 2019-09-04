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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ComputerNameDnsDomain ; 
 int /*<<< orphan*/  ComputerNameDnsFullyQualified ; 
 int /*<<< orphan*/  ComputerNameDnsHostname ; 
 int /*<<< orphan*/  ComputerNameNetBIOS ; 
 int ERROR_MORE_DATA ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int pGetComputerNameExA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetComputerNameExA(void)
{
    DWORD size;
    BOOL ret;
    LPSTR name;
    DWORD error;

    static const int MAX_COMP_NAME = 32767;

    if (!pGetComputerNameExA)
    {
        win_skip("GetComputerNameExA function not implemented\n");
        return;
    }

    size = 0;
    ret = pGetComputerNameExA(ComputerNameDnsDomain, (LPSTR)0xdeadbeef, &size);
    error = GetLastError();
    ok(ret == 0, "Expected 0, got %d\n", ret);
    ok(error == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", error);

    /* size is not set in win2k */
    if (size == 0)
    {
        win_skip("Win2k doesn't set the size\n");
        size = MAX_COMP_NAME;
    }
    name = HeapAlloc(GetProcessHeap(), 0, size * sizeof(name[0]));
    ok(name != NULL, "HeapAlloc failed with error %d\n", GetLastError());
    ret = pGetComputerNameExA(ComputerNameDnsDomain, name, &size);
    ok(ret, "GetComputerNameExA(ComputerNameDnsDomain) failed with error %d\n", GetLastError());
    trace("domain name is \"%s\"\n", name);
    HeapFree(GetProcessHeap(), 0, name);

    size = 0;
    ret = pGetComputerNameExA(ComputerNameDnsFullyQualified, (LPSTR)0xdeadbeef, &size);
    error = GetLastError();
    ok(ret == 0, "Expected 0, got %d\n", ret);
    ok(error == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", error);

    /* size is not set in win2k */
    if (size == 0)
        size = MAX_COMP_NAME;
    name = HeapAlloc(GetProcessHeap(), 0, size * sizeof(name[0]));
    ok(name != NULL, "HeapAlloc failed with error %d\n", GetLastError());
    ret = pGetComputerNameExA(ComputerNameDnsFullyQualified, name, &size);
    ok(ret, "GetComputerNameExA(ComputerNameDnsFullyQualified) failed with error %d\n", GetLastError());
    trace("fully qualified hostname is \"%s\"\n", name);
    HeapFree(GetProcessHeap(), 0, name);

    size = 0;
    ret = pGetComputerNameExA(ComputerNameDnsHostname, (LPSTR)0xdeadbeef, &size);
    error = GetLastError();
    ok(ret == 0, "Expected 0, got %d\n", ret);
    ok(error == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", error);

    /* size is not set in win2k */
    if (size == 0)
        size = MAX_COMP_NAME;
    name = HeapAlloc(GetProcessHeap(), 0, size * sizeof(name[0]));
    ok(name != NULL, "HeapAlloc failed with error %d\n", GetLastError());
    ret = pGetComputerNameExA(ComputerNameDnsHostname, name, &size);
    ok(ret, "GetComputerNameExA(ComputerNameDnsHostname) failed with error %d\n", GetLastError());
    trace("hostname is \"%s\"\n", name);
    HeapFree(GetProcessHeap(), 0, name);

    size = 0;
    ret = pGetComputerNameExA(ComputerNameNetBIOS, (LPSTR)0xdeadbeef, &size);
    error = GetLastError();
    ok(ret == 0, "Expected 0, got %d\n", ret);
    ok(error == ERROR_MORE_DATA, "Expected ERROR_MORE_DATA, got %d\n", error);

    /* size is not set in win2k */
    if (size == 0)
        size = MAX_COMP_NAME;
    name = HeapAlloc(GetProcessHeap(), 0, size * sizeof(name[0]));
    ok(name != NULL, "HeapAlloc failed with error %d\n", GetLastError());
    ret = pGetComputerNameExA(ComputerNameNetBIOS, name, &size);
    ok(ret, "GetComputerNameExA(ComputerNameNetBIOS) failed with error %d\n", GetLastError());
    trace("NetBIOS name is \"%s\"\n", name);
    HeapFree(GetProcessHeap(), 0, name);
}