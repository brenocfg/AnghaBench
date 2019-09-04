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
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_INTERNET_EXTENDED_ERROR ; 
 scalar_t__ ERROR_INTERNET_INCORRECT_HANDLE_TYPE ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ FALSE ; 
 int FTP_TRANSFER_TYPE_UNKNOWN ; 
 scalar_t__ FtpPutFileA (int /*<<< orphan*/ *,char*,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_putfile(HINTERNET hFtp, HINTERNET hConnect)
{
    BOOL      bRet;
    HANDLE    hFile;

    /* The order of checking is:
     *
     *   All parameters except 'session handle' and 'condition flags'
     *   Session handle
     *   Session handle type
     *   Condition flags
     */

    /* Test to show the parameter checking order depends on the Windows version */
    SetLastError(0xdeadbeef);
    bRet = FtpPutFileA(NULL, NULL, "non_existing_remote", FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpPutFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_HANDLE ||
         GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_HANDLE (win98) or ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Test to show session handle is checked before 'condition flags' */
    SetLastError(0xdeadbeef);
    bRet = FtpPutFileA(NULL, "non_existing_local", "non_existing_remote", 5, 0);
    ok ( bRet == FALSE, "Expected FtpPutFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_HANDLE,
        "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());

    /* Start clean */
    DeleteFileA("non_existing_local");

    /* No local file given */
    SetLastError(0xdeadbeef);
    bRet = FtpPutFileA(hFtp, NULL, "non_existing_remote", FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpPutFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* No remote file given */
    SetLastError(0xdeadbeef);
    bRet = FtpPutFileA(hFtp, "non_existing_local", NULL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpPutFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Illegal condition flags */
    SetLastError(0xdeadbeef);
    bRet = FtpPutFileA(hFtp, "non_existing_local", "non_existing_remote", 5, 0);
    ok ( bRet == FALSE, "Expected FtpPutFileA to fail\n");
    ok ( GetLastError() == ERROR_FILE_NOT_FOUND || GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_FILE_NOT_FOUND or ERROR_INVALID_PARAMETER (win98), got %d\n", GetLastError());

    /* Parameters are OK but local file doesn't exist */
    SetLastError(0xdeadbeef);
    bRet = FtpPutFileA(hFtp, "non_existing_local", "non_existing_remote", FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpPutFileA to fail\n");
    ok ( GetLastError() == ERROR_FILE_NOT_FOUND,
        "Expected ERROR_FILE_NOT_FOUND, got %d\n", GetLastError());

    /* Create a temporary local file */
    SetLastError(0xdeadbeef);
    hFile = CreateFileA("now_existing_local", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    ok ( hFile != NULL, "Error creating a local file : %d\n", GetLastError());
    CloseHandle(hFile);

    /* Local file exists but we shouldn't be allowed to 'put' the file */
    SetLastError(0xdeadbeef);
    bRet = FtpPutFileA(hFtp, "now_existing_local", "non_existing_remote", FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpPutFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_EXTENDED_ERROR,
        "Expected ERROR_INTERNET_EXTENDED_ERROR, got %d\n", GetLastError());

    DeleteFileA("now_existing_local");

    /* Test to show the parameter checking order depends on the Windows version */
    SetLastError(0xdeadbeef);
    bRet = FtpPutFileA(hConnect, NULL, "non_existing_remote", FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpPutFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE ||
         GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE (win98) or ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Test to show that 'session handle type' is checked before 'condition flags' */
    SetLastError(0xdeadbeef);
    bRet = FtpPutFileA(hConnect, "non_existing_local", "non_existing_remote", 5, 0);
    ok ( bRet == FALSE, "Expected FtpPutFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    bRet = FtpPutFileA(hConnect, "non_existing_local", "non_existing_remote", FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpPutFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got %d\n", GetLastError());
}