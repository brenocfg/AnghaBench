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
typedef  int /*<<< orphan*/  path ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * DLL_DIRECTORY_COOKIE ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  DeleteFileW (char*) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int GetTempFileNameW (char*,char const*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetTempPathW (int,char*) ; 
 int /*<<< orphan*/  GetWindowsDirectoryW (char*,int) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/ * pAddDllDirectory (char const*) ; 
 int pRemoveDllDirectory (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_AddDllDirectory(void)
{
    static const WCHAR tmpW[] = {'t','m','p',0};
    static const WCHAR dotW[] = {'.','\\','.',0};
    static const WCHAR rootW[] = {'\\',0};
    WCHAR path[MAX_PATH], buf[MAX_PATH];
    DLL_DIRECTORY_COOKIE cookie;
    BOOL ret;

    if (!pAddDllDirectory || !pRemoveDllDirectory)
    {
        win_skip( "AddDllDirectory not available\n" );
        return;
    }

    buf[0] = '\0';
    GetTempPathW( sizeof(path)/sizeof(path[0]), path );
    ret = GetTempFileNameW( path, tmpW, 0, buf );
    ok( ret, "GetTempFileName failed err %u\n", GetLastError() );
    SetLastError( 0xdeadbeef );
    cookie = pAddDllDirectory( buf );
    ok( cookie != NULL, "AddDllDirectory failed err %u\n", GetLastError() );
    SetLastError( 0xdeadbeef );
    ret = pRemoveDllDirectory( cookie );
    ok( ret, "RemoveDllDirectory failed err %u\n", GetLastError() );

    DeleteFileW( buf );
    SetLastError( 0xdeadbeef );
    cookie = pAddDllDirectory( buf );
    ok( !cookie, "AddDllDirectory succeeded\n" );
    ok( GetLastError() == ERROR_FILE_NOT_FOUND, "wrong error %u\n", GetLastError() );
    cookie = pAddDllDirectory( dotW );
    ok( !cookie, "AddDllDirectory succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );
    cookie = pAddDllDirectory( rootW );
    ok( cookie != NULL, "AddDllDirectory failed err %u\n", GetLastError() );
    SetLastError( 0xdeadbeef );
    ret = pRemoveDllDirectory( cookie );
    ok( ret, "RemoveDllDirectory failed err %u\n", GetLastError() );
    GetWindowsDirectoryW( buf, MAX_PATH );
    lstrcpyW( buf + 2, tmpW );
    cookie = pAddDllDirectory( buf );
    ok( !cookie, "AddDllDirectory succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );
}