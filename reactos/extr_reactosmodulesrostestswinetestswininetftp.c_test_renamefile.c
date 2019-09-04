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
 scalar_t__ FtpRenameFileA (int /*<<< orphan*/ *,char*,char*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_renamefile(HINTERNET hFtp, HINTERNET hConnect)
{
    BOOL      bRet;

    /* Invalid internet handle, the rest are valid parameters */
    SetLastError(0xdeadbeef);
    bRet = FtpRenameFileA(NULL , "should_be_non_existing_deadbeef", "new");
    ok ( bRet == FALSE, "Expected FtpRenameFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_HANDLE,
        "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());

    /* No 'existing' file */
    SetLastError(0xdeadbeef);
    bRet = FtpRenameFileA(hFtp , NULL, "new");
    ok ( bRet == FALSE, "Expected FtpRenameFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* No new file */
    SetLastError(0xdeadbeef);
    bRet = FtpRenameFileA(hFtp , "should_be_non_existing_deadbeef", NULL);
    ok ( bRet == FALSE, "Expected FtpRenameFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Existing file shouldn't be there */
    SetLastError(0xdeadbeef);
    bRet = FtpRenameFileA(hFtp , "should_be_non_existing_deadbeef", "new");
    ok ( bRet == FALSE, "Expected FtpRenameFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_EXTENDED_ERROR,
        "Expected ERROR_INTERNET_EXTENDED_ERROR, got %d\n", GetLastError());

    /* One small test to show that handle type is checked before parameters */
    SetLastError(0xdeadbeef);
    bRet = FtpRenameFileA(hConnect , "should_be_non_existing_deadbeef", NULL);
    ok ( bRet == FALSE, "Expected FtpRenameFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    bRet = FtpRenameFileA(hConnect , "should_be_non_existing_deadbeef", "new");
    ok ( bRet == FALSE, "Expected FtpRenameFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got %d\n", GetLastError());
}