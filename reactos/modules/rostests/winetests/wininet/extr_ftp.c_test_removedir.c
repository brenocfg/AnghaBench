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
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INTERNET_EXTENDED_ERROR ; 
 scalar_t__ ERROR_INTERNET_INCORRECT_HANDLE_TYPE ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ FALSE ; 
 scalar_t__ FtpRemoveDirectoryA (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_removedir(HINTERNET hFtp, HINTERNET hConnect)
{
    BOOL      bRet;

    /* Invalid internet handle, the other is a valid parameter */
    SetLastError(0xdeadbeef);
    bRet = FtpRemoveDirectoryA(NULL, "should_be_non_existing_deadbeef_dir");
    ok ( bRet == FALSE, "Expected FtpRemoveDirectoryA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_HANDLE,
        "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());

    /* No remote directory given */
    SetLastError(0xdeadbeef);
    bRet = FtpRemoveDirectoryA(hFtp, NULL);
    ok ( bRet == FALSE, "Expected FtpRemoveDirectoryA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Remote directory doesn't exist */
    SetLastError(0xdeadbeef);
    bRet = FtpRemoveDirectoryA(hFtp, "should_be_non_existing_deadbeef_dir");
    ok ( bRet == FALSE, "Expected FtpRemoveDirectoryA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_EXTENDED_ERROR,
        "Expected ERROR_INTERNET_EXTENDED_ERROR, got %d\n", GetLastError());

    /* We shouldn't be allowed to remove that directory */
    SetLastError(0xdeadbeef);
    bRet = FtpRemoveDirectoryA(hFtp, "pub");
    ok ( bRet == FALSE, "Expected FtpRemoveDirectoryA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_EXTENDED_ERROR,
        "Expected ERROR_INTERNET_EXTENDED_ERROR, got %d\n", GetLastError());

    /* One small test to show that handle type is checked before parameters */
    SetLastError(0xdeadbeef);
    bRet = FtpRemoveDirectoryA(hConnect, NULL);
    ok ( bRet == FALSE, "Expected FtpRemoveDirectoryA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    bRet = FtpRemoveDirectoryA(hConnect, "should_be_non_existing_deadbeef_dir");
    ok ( bRet == FALSE, "Expected FtpRemoveDirectoryA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got %d\n", GetLastError());
}