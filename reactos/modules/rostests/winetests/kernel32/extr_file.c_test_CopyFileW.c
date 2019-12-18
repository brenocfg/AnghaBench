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
typedef  int DWORD ;

/* Variables and functions */
 int CopyFileW (char*,char*,int /*<<< orphan*/ ) ; 
 int DeleteFileW (char*) ; 
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_FILE_EXISTS ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ GetLastError () ; 
 int GetTempFileNameW (char*,char const*,int /*<<< orphan*/ ,char*) ; 
 int GetTempPathW (int,char*) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_CopyFileW(void)
{
    WCHAR temp_path[MAX_PATH];
    WCHAR source[MAX_PATH], dest[MAX_PATH];
    static const WCHAR prefix[] = {'p','f','x',0};
    DWORD ret;

    ret = GetTempPathW(MAX_PATH, temp_path);
    if (ret == 0 && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("GetTempPathW is not available\n");
        return;
    }
    ok(ret != 0, "GetTempPathW error %d\n", GetLastError());
    ok(ret < MAX_PATH, "temp path should fit into MAX_PATH\n");

    ret = GetTempFileNameW(temp_path, prefix, 0, source);
    ok(ret != 0, "GetTempFileNameW error %d\n", GetLastError());

    ret = GetTempFileNameW(temp_path, prefix, 0, dest);
    ok(ret != 0, "GetTempFileNameW error %d\n", GetLastError());

    ret = CopyFileW(source, dest, TRUE);
    ok(!ret && GetLastError() == ERROR_FILE_EXISTS,
       "CopyFileW: unexpected error %d\n", GetLastError());

    ret = CopyFileW(source, dest, FALSE);
    ok(ret, "CopyFileW: error %d\n", GetLastError());

    ret = DeleteFileW(source);
    ok(ret, "DeleteFileW: error %d\n", GetLastError());
    ret = DeleteFileW(dest);
    ok(ret, "DeleteFileW: error %d\n", GetLastError());
}