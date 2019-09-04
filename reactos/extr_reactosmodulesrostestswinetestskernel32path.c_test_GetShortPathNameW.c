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
typedef  int /*<<< orphan*/  short_path ;
typedef  char WCHAR ;
typedef  scalar_t__ HANDLE ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (scalar_t__) ; 
 int CreateDirectoryW (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ CreateFileW (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int DeleteFileW (char*) ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INVALID_NAME ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 int GetShortPathNameW (char*,char*,int) ; 
 int /*<<< orphan*/  GetTempPathW (int,char*) ; 
 scalar_t__ INVALID_HANDLE_VALUE ; 
 int MAX_PATH ; 
 int RemoveDirectoryW (char*) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,char const*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetShortPathNameW(void)
{
    static const WCHAR extended_prefix[] = {'\\','\\','?','\\',0};
    static const WCHAR test_path[] = { 'L', 'o', 'n', 'g', 'D', 'i', 'r', 'e', 'c', 't', 'o', 'r', 'y', 'N', 'a', 'm', 'e',  0 };
    static const WCHAR name[] = { 't', 'e', 's', 't', 0 };
    static const WCHAR backSlash[] = { '\\', 0 };
    static const WCHAR a_bcdeW[] = {'a','.','b','c','d','e',0};
    static const WCHAR wildW[] = { '*',0 };
    WCHAR path[MAX_PATH], tmppath[MAX_PATH], *ptr;
    WCHAR short_path[MAX_PATH];
    DWORD length;
    HANDLE file;
    int ret;

    SetLastError(0xdeadbeef);
    GetTempPathW( MAX_PATH, tmppath );
    if (GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("GetTempPathW is not implemented\n");
        return;
    }

    lstrcpyW( path, tmppath );
    lstrcatW( path, test_path );
    lstrcatW( path, backSlash );
    ret = CreateDirectoryW( path, NULL );
    ok( ret, "Directory was not created. LastError = %d\n", GetLastError() );

    /* Starting a main part of test */

    /* extended path \\?\C:\path\ */
    lstrcpyW( path, extended_prefix );
    lstrcatW( path, tmppath );
    lstrcatW( path, test_path );
    lstrcatW( path, backSlash );
    short_path[0] = 0;
    length = GetShortPathNameW( path, short_path, sizeof(short_path) / sizeof(*short_path) );
    ok( length, "GetShortPathNameW returned 0.\n" );

    lstrcpyW( path, tmppath );
    lstrcatW( path, test_path );
    lstrcatW( path, backSlash );
    length = GetShortPathNameW( path, short_path, 0 );
    ok( length, "GetShortPathNameW returned 0.\n" );
    ret = GetShortPathNameW( path, short_path, length );
    ok( ret && ret == length-1, "GetShortPathNameW returned 0.\n" );

    lstrcatW( short_path, name );

    /* GetShortPathName for a non-existent short file name should fail */
    SetLastError(0xdeadbeef);
    length = GetShortPathNameW( short_path, path, 0 );
    ok(!length, "GetShortPathNameW should fail\n");
    ok(GetLastError() == ERROR_FILE_NOT_FOUND, "expected ERROR_FILE_NOT_FOUND, got %d\n", GetLastError());

    file = CreateFileW( short_path, GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
    ok( file != INVALID_HANDLE_VALUE, "File was not created.\n" );
    CloseHandle( file );
    ret = DeleteFileW( short_path );
    ok( ret, "Cannot delete file.\n" );

    ptr = path + lstrlenW(path);
    lstrcpyW( ptr, a_bcdeW);
    file = CreateFileW( path, GENERIC_READ|GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL );
    ok( file != INVALID_HANDLE_VALUE, "File was not created.\n" );
    CloseHandle( file );

    length = GetShortPathNameW( path, short_path, sizeof(short_path)/sizeof(*short_path) );
    ok( length, "GetShortPathNameW failed: %u.\n", GetLastError() );

    lstrcpyW(ptr, wildW);
    SetLastError(0xdeadbeef);
    length = GetShortPathNameW( path, short_path, sizeof(short_path)/sizeof(*short_path) );
    ok(!length, "GetShortPathNameW should fail\n");
    ok(GetLastError() == ERROR_INVALID_NAME, "wrong error %d\n", GetLastError());

    lstrcpyW(ptr, a_bcdeW);
    ret = DeleteFileW( path );
    ok( ret, "Cannot delete file.\n" );
    *ptr = 0;

    /* End test */
    ret = RemoveDirectoryW( path );
    ok( ret, "Cannot delete directory.\n" );
}