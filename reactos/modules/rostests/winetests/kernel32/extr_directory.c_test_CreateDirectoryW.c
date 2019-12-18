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
typedef  char WCHAR ;
typedef  int BOOL ;

/* Variables and functions */
 int CreateDirectoryW (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ ERROR_ACCESS_DENIED ; 
 scalar_t__ ERROR_ALREADY_EXISTS ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_INVALID_NAME ; 
 scalar_t__ ERROR_PATH_NOT_FOUND ; 
 int FALSE ; 
 int /*<<< orphan*/  GetCurrentDirectoryW (int,char*) ; 
 scalar_t__ GetLastError () ; 
 int GetSystemDirectoryW (char*,int) ; 
 int /*<<< orphan*/  GetTempPathW (int,char*) ; 
 int MAX_PATH ; 
 int RemoveDirectoryW (char*) ; 
 int SetCurrentDirectoryW (char*) ; 
 int TRUE ; 
 int /*<<< orphan*/  lstrcatW (char*,char const*) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_CreateDirectoryW(void)
{
    WCHAR tmpdir[MAX_PATH];
    BOOL ret;
    static const WCHAR empty_strW[] = { 0 };
    static const WCHAR tmp_dir_name[] = {'P','l','e','a','s','e',' ','R','e','m','o','v','e',' ','M','e',0};
    static const WCHAR dotW[] = {'.',0};
    static const WCHAR slashW[] = {'/',0};
    static const WCHAR dotdotW[] = {'.','.',0};
    static const WCHAR questionW[] = {'?',0};
    WCHAR curdir[MAX_PATH];

    ret = CreateDirectoryW(NULL, NULL);
    if (!ret && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("CreateDirectoryW is not available\n");
        return;
    }
    ok(ret == FALSE && GetLastError() == ERROR_PATH_NOT_FOUND,
       "should not create NULL path ret %u err %u\n", ret, GetLastError());

    ret = CreateDirectoryW(empty_strW, NULL);
    ok(ret == FALSE && GetLastError() == ERROR_PATH_NOT_FOUND,
       "should not create empty path ret %u err %u\n", ret, GetLastError());

    ret = GetSystemDirectoryW(tmpdir, MAX_PATH);
    ok(ret < MAX_PATH, "System directory should fit into MAX_PATH\n");

    GetCurrentDirectoryW(MAX_PATH, curdir);
    ret = SetCurrentDirectoryW(tmpdir);
    ok(ret == TRUE, "could not chdir to the System directory ret %u err %u\n", ret, GetLastError());

    ret = CreateDirectoryW(dotW, NULL);
    ok(ret == FALSE && GetLastError() == ERROR_ALREADY_EXISTS,
       "should not create existing path ret %u err %u\n", ret, GetLastError());

    ret = CreateDirectoryW(dotdotW, NULL);
    ok(ret == FALSE && GetLastError() == ERROR_ALREADY_EXISTS,
       "should not create existing path ret %u err %u\n", ret, GetLastError());

    GetTempPathW(MAX_PATH, tmpdir);
    tmpdir[3] = 0; /* truncate the path */
    ret = CreateDirectoryW(tmpdir, NULL);
    ok(ret == FALSE && (GetLastError() == ERROR_ACCESS_DENIED || GetLastError() == ERROR_ALREADY_EXISTS),
       "should deny access to the drive root ret %u err %u\n", ret, GetLastError());

    GetTempPathW(MAX_PATH, tmpdir);
    lstrcatW(tmpdir, tmp_dir_name);
    ret = CreateDirectoryW(tmpdir, NULL);
    ok(ret == TRUE, "CreateDirectoryW should always succeed\n");

    ret = CreateDirectoryW(tmpdir, NULL);
    ok(ret == FALSE && GetLastError() == ERROR_ALREADY_EXISTS,
       "should not create existing path ret %u err %u\n", ret, GetLastError());

    ret = RemoveDirectoryW(tmpdir);
    ok(ret == TRUE, "RemoveDirectoryW should always succeed\n");

    lstrcatW(tmpdir, questionW);
    ret = CreateDirectoryW(tmpdir, NULL);
    ok(ret == FALSE && GetLastError() == ERROR_INVALID_NAME,
       "CreateDirectoryW with ? wildcard name should fail with error 183, ret=%s error=%d\n",
       ret ? " True" : "False", GetLastError());
    ret = RemoveDirectoryW(tmpdir);
    ok(ret == FALSE, "RemoveDirectoryW should have failed\n");

    tmpdir[lstrlenW(tmpdir) - 1] = '*';
    ret = CreateDirectoryW(tmpdir, NULL);
    ok(ret == FALSE && GetLastError() == ERROR_INVALID_NAME,
       "CreateDirectoryW with * wildcard name should fail with error 183, ret=%s error=%d\n",
       ret ? " True" : "False", GetLastError());
    ret = RemoveDirectoryW(tmpdir);
    ok(ret == FALSE, "RemoveDirectoryW should have failed\n");
    
    GetTempPathW(MAX_PATH, tmpdir);
    lstrcatW(tmpdir, tmp_dir_name);
    lstrcatW(tmpdir, slashW);
    lstrcatW(tmpdir, tmp_dir_name);
    ret = CreateDirectoryW(tmpdir, NULL);
    ok(ret == FALSE && GetLastError() == ERROR_PATH_NOT_FOUND,
      "CreateDirectoryW with multiple nonexistent directories in path should fail ret %u err %u\n",
       ret, GetLastError());
    ret = RemoveDirectoryW(tmpdir);
    ok(ret == FALSE, "RemoveDirectoryW should have failed\n");

    SetCurrentDirectoryW(curdir);
}