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
typedef  int /*<<< orphan*/  HANDLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int BASE_SEARCH_PATH_DISABLE_SAFE_SEARCHMODE ; 
 int BASE_SEARCH_PATH_ENABLE_SAFE_SEARCHMODE ; 
 int BASE_SEARCH_PATH_PERMANENT ; 
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CreateDirectoryA (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_ACCESS_DENIED ; 
 int /*<<< orphan*/  ERROR_INVALID_PARAMETER ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 int /*<<< orphan*/  GetCurrentDirectoryA (int,char*) ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  GetSystemDirectoryA (char*,int) ; 
 int /*<<< orphan*/  GetTempFileNameA (char*,char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  GetTempPathA (int,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  RemoveDirectoryA (char*) ; 
 int /*<<< orphan*/  SearchPathA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetCurrentDirectoryA (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcmpiA (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  pSetSearchPathMode (int) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SetSearchPathMode(void)
{
    BOOL ret;
    char orig[MAX_PATH], buf[MAX_PATH], dir[MAX_PATH], expect[MAX_PATH];
    HANDLE handle;

    if (!pSetSearchPathMode)
    {
        win_skip( "SetSearchPathMode isn't available\n" );
        return;
    }
    GetCurrentDirectoryA( MAX_PATH, orig );
    GetTempPathA( MAX_PATH, buf );
    GetTempFileNameA( buf, "path", 0, dir );
    DeleteFileA( dir );
    CreateDirectoryA( dir, NULL );
    ret = SetCurrentDirectoryA( dir );
    ok( ret, "failed to switch to %s\n", dir );
    if (!ret)
    {
        RemoveDirectoryA( dir );
        return;
    }

    handle = CreateFileA( "kernel32.dll", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, 0 );
    CloseHandle( handle );

    SetLastError( 0xdeadbeef );
    ret = pSetSearchPathMode( 0 );
    ok( !ret, "SetSearchPathMode succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = pSetSearchPathMode( 0x80 );
    ok( !ret, "SetSearchPathMode succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = pSetSearchPathMode( BASE_SEARCH_PATH_PERMANENT );
    ok( !ret, "SetSearchPathMode succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = SearchPathA( NULL, "kernel32.dll", NULL, MAX_PATH, buf, NULL );
    ok( ret, "SearchPathA failed err %u\n", GetLastError() );
    GetCurrentDirectoryA( MAX_PATH, expect );
    strcat( expect, "\\kernel32.dll" );
    ok( !lstrcmpiA( buf, expect ), "found %s expected %s\n", buf, expect );

    SetLastError( 0xdeadbeef );
    ret = pSetSearchPathMode( BASE_SEARCH_PATH_ENABLE_SAFE_SEARCHMODE );
    ok( ret, "SetSearchPathMode failed err %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = SearchPathA( NULL, "kernel32.dll", NULL, MAX_PATH, buf, NULL );
    ok( ret, "SearchPathA failed err %u\n", GetLastError() );
    GetSystemDirectoryA( expect, MAX_PATH );
    strcat( expect, "\\kernel32.dll" );
    ok( !lstrcmpiA( buf, expect ), "found %s expected %s\n", buf, expect );

    SetLastError( 0xdeadbeef );
    ret = pSetSearchPathMode( BASE_SEARCH_PATH_DISABLE_SAFE_SEARCHMODE );
    ok( ret, "SetSearchPathMode failed err %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = SearchPathA( NULL, "kernel32.dll", NULL, MAX_PATH, buf, NULL );
    ok( ret, "SearchPathA failed err %u\n", GetLastError() );
    GetCurrentDirectoryA( MAX_PATH, expect );
    strcat( expect, "\\kernel32.dll" );
    ok( !lstrcmpiA( buf, expect ), "found %s expected %s\n", buf, expect );

    SetLastError( 0xdeadbeef );
    ret = pSetSearchPathMode( BASE_SEARCH_PATH_DISABLE_SAFE_SEARCHMODE | BASE_SEARCH_PATH_PERMANENT );
    ok( !ret, "SetSearchPathMode succeeded\n" );
    ok( GetLastError() == ERROR_INVALID_PARAMETER, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = pSetSearchPathMode( BASE_SEARCH_PATH_ENABLE_SAFE_SEARCHMODE | BASE_SEARCH_PATH_PERMANENT );
    ok( ret, "SetSearchPathMode failed err %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = pSetSearchPathMode( BASE_SEARCH_PATH_DISABLE_SAFE_SEARCHMODE );
    ok( !ret, "SetSearchPathMode succeeded\n" );
    ok( GetLastError() == ERROR_ACCESS_DENIED, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = pSetSearchPathMode( BASE_SEARCH_PATH_ENABLE_SAFE_SEARCHMODE );
    ok( !ret, "SetSearchPathMode succeeded\n" );
    ok( GetLastError() == ERROR_ACCESS_DENIED, "wrong error %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = pSetSearchPathMode( BASE_SEARCH_PATH_ENABLE_SAFE_SEARCHMODE | BASE_SEARCH_PATH_PERMANENT );
    ok( ret, "SetSearchPathMode failed err %u\n", GetLastError() );

    SetLastError( 0xdeadbeef );
    ret = SearchPathA( NULL, "kernel32.dll", NULL, MAX_PATH, buf, NULL );
    ok( ret, "SearchPathA failed err %u\n", GetLastError() );
    GetSystemDirectoryA( expect, MAX_PATH );
    strcat( expect, "\\kernel32.dll" );
    ok( !lstrcmpiA( buf, expect ), "found %s expected %s\n", buf, expect );

    DeleteFileA( "kernel32.dll" );
    SetCurrentDirectoryA( orig );
    RemoveDirectoryA( dir );
}