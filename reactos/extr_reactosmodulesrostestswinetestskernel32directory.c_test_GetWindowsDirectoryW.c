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
typedef  float WCHAR ;
typedef  int UINT ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ GetLastError () ; 
 int GetWindowsDirectoryW (float*,int) ; 
 int MAX_PATH ; 
 scalar_t__ lstrcmpW (float*,float const*) ; 
 int /*<<< orphan*/  lstrcpyW (float*,float const*) ; 
 int lstrlenW (float*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_GetWindowsDirectoryW(void)
{
    UINT len, len_with_null;
    WCHAR buf[MAX_PATH];
    static const WCHAR fooW[] = {'f','o','o',0};

    len_with_null = GetWindowsDirectoryW(NULL, 0);
    if (len_with_null == 0 && GetLastError() == ERROR_CALL_NOT_IMPLEMENTED)
    {
        win_skip("GetWindowsDirectoryW is not implemented\n");
        return;
    }
    ok(len_with_null <= MAX_PATH, "should fit into MAX_PATH\n");

    lstrcpyW(buf, fooW);
    len = GetWindowsDirectoryW(buf, 1);
    ok(lstrcmpW(buf, fooW) == 0, "should not touch the buffer\n");
    ok(len == len_with_null, "GetWindowsDirectoryW returned %d, expected %d\n",
       len, len_with_null);

    lstrcpyW(buf, fooW);
    len = GetWindowsDirectoryW(buf, len_with_null - 1);
    ok(lstrcmpW(buf, fooW) == 0, "should not touch the buffer\n");
    ok(len == len_with_null, "GetWindowsDirectoryW returned %d, expected %d\n",
       len, len_with_null);

    lstrcpyW(buf, fooW);
    len = GetWindowsDirectoryW(buf, len_with_null);
    ok(lstrcmpW(buf, fooW) != 0, "should touch the buffer\n");
    ok(len == lstrlenW(buf), "returned length should be equal to the length of string\n");
    ok(len == len_with_null-1, "GetWindowsDirectoryW returned %d, expected %d\n",
       len, len_with_null-1);
}