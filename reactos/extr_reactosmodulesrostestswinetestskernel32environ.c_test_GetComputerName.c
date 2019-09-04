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
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/ * LPWSTR ;
typedef  int /*<<< orphan*/ * LPSTR ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ERROR_BUFFER_OVERFLOW ; 
 int ERROR_CALL_NOT_IMPLEMENTED ; 
 int GetComputerNameA (int /*<<< orphan*/ *,int*) ; 
 int GetComputerNameW (int /*<<< orphan*/ *,int*) ; 
 int GetLastError () ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int MAX_COMPUTERNAME_LENGTH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 
 int strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetComputerName(void)
{
    DWORD size;
    BOOL ret;
    LPSTR name;
    LPWSTR nameW;
    DWORD error;
    int name_len;

    size = 0;
    ret = GetComputerNameA((LPSTR)0xdeadbeef, &size);
    error = GetLastError();
    ok(!ret && error == ERROR_BUFFER_OVERFLOW, "GetComputerNameA should have failed with ERROR_BUFFER_OVERFLOW instead of %d\n", error);

    /* Only Vista returns the computer name length as documented in the MSDN */
    if (size != 0)
    {
        size++; /* nul terminating character */
        name = HeapAlloc(GetProcessHeap(), 0, size * sizeof(name[0]));
        ok(name != NULL, "HeapAlloc failed with error %d\n", GetLastError());
        ret = GetComputerNameA(name, &size);
        ok(ret, "GetComputerNameA failed with error %d\n", GetLastError());
        HeapFree(GetProcessHeap(), 0, name);
    }

    size = MAX_COMPUTERNAME_LENGTH + 1;
    name = HeapAlloc(GetProcessHeap(), 0, size * sizeof(name[0]));
    ok(name != NULL, "HeapAlloc failed with error %d\n", GetLastError());
    ret = GetComputerNameA(name, &size);
    ok(ret, "GetComputerNameA failed with error %d\n", GetLastError());
    trace("computer name is \"%s\"\n", name);
    name_len = strlen(name);
    ok(size == name_len, "size should be same as length, name_len=%d, size=%d\n", name_len, size);
    HeapFree(GetProcessHeap(), 0, name);

    size = 0;
    SetLastError(0xdeadbeef);
    ret = GetComputerNameW((LPWSTR)0xdeadbeef, &size);
    error = GetLastError();
    if (error == ERROR_CALL_NOT_IMPLEMENTED)
        win_skip("GetComputerNameW is not implemented\n");
    else
    {
        ok(!ret && error == ERROR_BUFFER_OVERFLOW, "GetComputerNameW should have failed with ERROR_BUFFER_OVERFLOW instead of %d\n", error);
        size++; /* nul terminating character */
        nameW = HeapAlloc(GetProcessHeap(), 0, size * sizeof(nameW[0]));
        ok(nameW != NULL, "HeapAlloc failed with error %d\n", GetLastError());
        ret = GetComputerNameW(nameW, &size);
        ok(ret, "GetComputerNameW failed with error %d\n", GetLastError());
        HeapFree(GetProcessHeap(), 0, nameW);
    }
}