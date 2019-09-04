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
typedef  int /*<<< orphan*/  compName ;
typedef  int /*<<< orphan*/ * SC_HANDLE ;
typedef  scalar_t__ LONG ;
typedef  int /*<<< orphan*/  HKEY ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  CHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CloseServiceHandle (int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_BAD_NETPATH ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_DLL_INIT_FAILED ; 
 int /*<<< orphan*/  GENERIC_READ ; 
 int GetComputerNameA (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  HKEY_LOCAL_MACHINE ; 
 int MAX_COMPUTERNAME_LENGTH ; 
 int /*<<< orphan*/ * OpenSCManagerA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RegCloseKey (int /*<<< orphan*/ ) ; 
 scalar_t__ RegConnectRegistryA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcpyA (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lstrcpynA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_regconnectregistry( void)
{
    CHAR compName[MAX_COMPUTERNAME_LENGTH + 1];
    CHAR netwName[MAX_COMPUTERNAME_LENGTH + 3]; /* 2 chars for double backslash */
    DWORD len = sizeof(compName) ;
    BOOL ret;
    LONG retl;
    HKEY hkey;
    SC_HANDLE schnd;

    SetLastError(0xdeadbeef);
    ret = GetComputerNameA(compName, &len);
    ok( ret, "GetComputerName failed err = %d\n", GetLastError());
    if( !ret) return;

    lstrcpyA(netwName, "\\\\");
    lstrcpynA(netwName+2, compName, MAX_COMPUTERNAME_LENGTH + 1);

    retl = RegConnectRegistryA( compName, HKEY_LOCAL_MACHINE, &hkey);
    ok( !retl ||
        retl == ERROR_DLL_INIT_FAILED ||
        retl == ERROR_BAD_NETPATH, /* some win2k */
        "RegConnectRegistryA failed err = %d\n", retl);
    if( !retl) RegCloseKey( hkey);

    retl = RegConnectRegistryA( netwName, HKEY_LOCAL_MACHINE, &hkey);
    ok( !retl ||
        retl == ERROR_DLL_INIT_FAILED ||
        retl == ERROR_BAD_NETPATH, /* some win2k */
        "RegConnectRegistryA failed err = %d\n", retl);
    if( !retl) RegCloseKey( hkey);

    SetLastError(0xdeadbeef);
    schnd = OpenSCManagerA( compName, NULL, GENERIC_READ); 
    if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("OpenSCManagerA is not implemented\n");
        return;
    }

    ok( schnd != NULL, "OpenSCManagerA failed err = %d\n", GetLastError());
    CloseServiceHandle( schnd);

    SetLastError(0xdeadbeef);
    schnd = OpenSCManagerA( netwName, NULL, GENERIC_READ); 
    ok( schnd != NULL, "OpenSCManagerA failed err = %d\n", GetLastError());
    CloseServiceHandle( schnd);

}