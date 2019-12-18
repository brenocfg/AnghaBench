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
 scalar_t__ FtpDeleteFileA (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_deletefile(HINTERNET hFtp, HINTERNET hConnect)
{
    BOOL      bRet;

    /* Invalid internet handle, the other is a valid parameter */
    SetLastError(0xdeadbeef);
    bRet = FtpDeleteFileA(NULL, "non_existent_file_deadbeef");
    ok ( bRet == FALSE, "Expected FtpDeleteFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_HANDLE,
        "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());

    /* No filename */
    SetLastError(0xdeadbeef);
    bRet = FtpDeleteFileA(hFtp, NULL);
    ok ( bRet == FALSE, "Expected FtpDeleteFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Parameters are OK but remote file should not be there */
    SetLastError(0xdeadbeef);
    bRet = FtpDeleteFileA(hFtp, "non_existent_file_deadbeef");
    ok ( bRet == FALSE, "Expected FtpDeleteFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_EXTENDED_ERROR,
        "Expected ERROR_INTERNET_EXTENDED_ERROR, got %d\n", GetLastError());

    /* One small test to show that handle type is checked before parameters */
    SetLastError(0xdeadbeef);
    bRet = FtpDeleteFileA(hConnect, NULL);
    ok ( bRet == FALSE, "Expected FtpDeleteFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    bRet = FtpDeleteFileA(hConnect, "non_existent_file_deadbeef");
    ok ( bRet == FALSE, "Expected FtpCreateDirectoryA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got %d\n", GetLastError());
}