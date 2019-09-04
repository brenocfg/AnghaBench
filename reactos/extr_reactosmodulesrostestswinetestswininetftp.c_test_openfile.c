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
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CREATE_ALWAYS ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * CreateFileA (char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DeleteFileA (char*) ; 
 scalar_t__ ERROR_FILE_NOT_FOUND ; 
 scalar_t__ ERROR_FTP_TRANSFER_IN_PROGRESS ; 
 scalar_t__ ERROR_INTERNET_EXTENDED_ERROR ; 
 scalar_t__ ERROR_INTERNET_INCORRECT_HANDLE_TYPE ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FTP_TRANSFER_TYPE_ASCII ; 
 int /*<<< orphan*/  FTP_TRANSFER_TYPE_UNKNOWN ; 
 scalar_t__ FtpCreateDirectoryA (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ FtpDeleteFileA (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ FtpGetFileA (int /*<<< orphan*/ *,char*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * FtpOpenFileA (int /*<<< orphan*/ *,char*,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ FtpPutFileA (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ FtpRemoveDirectoryA (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ FtpRenameFileA (int /*<<< orphan*/ *,char*,char*) ; 
 int GENERIC_READ ; 
 int GENERIC_WRITE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TRUE ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace_extended_error (scalar_t__) ; 

__attribute__((used)) static void test_openfile(HINTERNET hFtp, HINTERNET hConnect)
{
    HINTERNET hOpenFile;

    /* Invalid internet handle, the rest are valid parameters */
    SetLastError(0xdeadbeef);
    hOpenFile = FtpOpenFileA(NULL, "welcome.msg", GENERIC_READ, FTP_TRANSFER_TYPE_ASCII, 0);
    ok ( !hOpenFile, "Expected FtpOpenFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_HANDLE,
        "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());
    InternetCloseHandle(hOpenFile); /* Just in case */

    /* No filename */
    SetLastError(0xdeadbeef);
    hOpenFile = FtpOpenFileA(hFtp, NULL, GENERIC_READ, FTP_TRANSFER_TYPE_ASCII, 0);
    ok ( !hOpenFile, "Expected FtpOpenFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    InternetCloseHandle(hOpenFile); /* Just in case */

    /* Illegal access flags */
    SetLastError(0xdeadbeef);
    hOpenFile = FtpOpenFileA(hFtp, "welcome.msg", 0, FTP_TRANSFER_TYPE_ASCII, 0);
    ok ( !hOpenFile, "Expected FtpOpenFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    InternetCloseHandle(hOpenFile); /* Just in case */

    /* Illegal combination of access flags */
    SetLastError(0xdeadbeef);
    hOpenFile = FtpOpenFileA(hFtp, "welcome.msg", GENERIC_READ|GENERIC_WRITE, FTP_TRANSFER_TYPE_ASCII, 0);
    ok ( !hOpenFile, "Expected FtpOpenFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    InternetCloseHandle(hOpenFile); /* Just in case */

    /* Illegal condition flags */
    SetLastError(0xdeadbeef);
    hOpenFile = FtpOpenFileA(hFtp, "welcome.msg", GENERIC_READ, 0xffffffff, 0);
    ok ( !hOpenFile, "Expected FtpOpenFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_EXTENDED_ERROR || GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INTERNET_EXTENDED_ERROR or ERROR_INVALID_PARAMETER (win98), got %d\n", GetLastError());
    InternetCloseHandle(hOpenFile); /* Just in case */

    SetLastError(0xdeadbeef);
    hOpenFile = FtpOpenFileA(hFtp, "welcome.msg", GENERIC_READ, FTP_TRANSFER_TYPE_ASCII, 0);
    ok ( hOpenFile != NULL, "Expected FtpOpenFileA to succeed\n");
    ok ( GetLastError() == ERROR_SUCCESS ||
        broken(GetLastError() == ERROR_FILE_NOT_FOUND), /* Win98 */
        "Expected ERROR_SUCCESS, got %u\n", GetLastError());

    if (hOpenFile)
    {
        BOOL bRet;
        DWORD error;
        HINTERNET hOpenFile2;
        HANDLE    hFile;

        /* We have a handle so all ftp calls should fail (TODO: Put all ftp-calls in here) */
        SetLastError(0xdeadbeef);
        bRet = FtpCreateDirectoryA(hFtp, "new_directory_deadbeef");
        error = GetLastError();
        ok ( bRet == FALSE, "Expected FtpCreateDirectoryA to fail\n");
        ok ( error == ERROR_FTP_TRANSFER_IN_PROGRESS || broken(error == ERROR_INTERNET_EXTENDED_ERROR),
            "Expected ERROR_FTP_TRANSFER_IN_PROGRESS, got %d\n", error);
        trace_extended_error(error);

        SetLastError(0xdeadbeef);
        bRet = FtpDeleteFileA(hFtp, "non_existent_file_deadbeef");
        error = GetLastError();
        ok ( bRet == FALSE, "Expected FtpDeleteFileA to fail\n");
        ok ( error == ERROR_FTP_TRANSFER_IN_PROGRESS || broken(error == ERROR_INTERNET_EXTENDED_ERROR),
            "Expected ERROR_FTP_TRANSFER_IN_PROGRESS, got %d\n", error);
        trace_extended_error(error);

        SetLastError(0xdeadbeef);
        bRet = FtpGetFileA(hFtp, "welcome.msg", "should_be_non_existing_deadbeef", FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
        error = GetLastError();
        ok ( bRet == FALSE || broken(bRet == TRUE), "Expected FtpGetFileA to fail\n");
        ok ( error == ERROR_FTP_TRANSFER_IN_PROGRESS || broken(error == ERROR_SUCCESS),
            "Expected ERROR_FTP_TRANSFER_IN_PROGRESS, got %d\n", error);
        DeleteFileA("should_be_non_existing_deadbeef"); /* Just in case */

        SetLastError(0xdeadbeef);
        hOpenFile2 = FtpOpenFileA(hFtp, "welcome.msg", GENERIC_READ, FTP_TRANSFER_TYPE_ASCII, 0);
        error = GetLastError();
        ok ( bRet == FALSE || broken(bRet == TRUE), "Expected FtpOpenFileA to fail\n");
        ok ( error == ERROR_FTP_TRANSFER_IN_PROGRESS || broken(error == ERROR_SUCCESS),
            "Expected ERROR_FTP_TRANSFER_IN_PROGRESS, got %d\n", error);
        InternetCloseHandle(hOpenFile2); /* Just in case */

        /* Create a temporary local file */
        SetLastError(0xdeadbeef);
        hFile = CreateFileA("now_existing_local", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
        ok ( hFile != NULL, "Error creating a local file : %d\n", GetLastError());
        CloseHandle(hFile);
        SetLastError(0xdeadbeef);
        bRet = FtpPutFileA(hFtp, "now_existing_local", "non_existing_remote", FTP_TRANSFER_TYPE_UNKNOWN, 0);
        error = GetLastError();
        ok ( bRet == FALSE, "Expected FtpPutFileA to fail\n");
        ok ( error == ERROR_FTP_TRANSFER_IN_PROGRESS || broken(error == ERROR_INTERNET_EXTENDED_ERROR),
            "Expected ERROR_FTP_TRANSFER_IN_PROGRESS, got %d\n", error);
        DeleteFileA("now_existing_local");

        SetLastError(0xdeadbeef);
        bRet = FtpRemoveDirectoryA(hFtp, "should_be_non_existing_deadbeef_dir");
        error = GetLastError();
        ok ( bRet == FALSE, "Expected FtpRemoveDirectoryA to fail\n");
        ok ( error == ERROR_FTP_TRANSFER_IN_PROGRESS || broken(error == ERROR_INTERNET_EXTENDED_ERROR),
            "Expected ERROR_FTP_TRANSFER_IN_PROGRESS, got %d\n", error);

        SetLastError(0xdeadbeef);
        bRet = FtpRenameFileA(hFtp , "should_be_non_existing_deadbeef", "new");
        error = GetLastError();
        ok ( bRet == FALSE, "Expected FtpRenameFileA to fail\n");
        ok ( error == ERROR_FTP_TRANSFER_IN_PROGRESS || broken(error == ERROR_INTERNET_EXTENDED_ERROR),
            "Expected ERROR_FTP_TRANSFER_IN_PROGRESS, got %d\n", error);
    }

    InternetCloseHandle(hOpenFile);

    /* One small test to show that handle type is checked before parameters */
    SetLastError(0xdeadbeef);
    hOpenFile = FtpOpenFileA(hConnect, "welcome.msg", GENERIC_READ, 5, 0);
    ok ( !hOpenFile, "Expected FtpOpenFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got %d\n", GetLastError());
    InternetCloseHandle(hOpenFile); /* Just in case */

    SetLastError(0xdeadbeef);
    hOpenFile = FtpOpenFileA(hConnect, "welcome.msg", GENERIC_READ, FTP_TRANSFER_TYPE_ASCII, 0);
    ok ( hOpenFile == NULL, "Expected FtpOpenFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got %d\n", GetLastError());

    InternetCloseHandle(hOpenFile); /* Just in case */
}