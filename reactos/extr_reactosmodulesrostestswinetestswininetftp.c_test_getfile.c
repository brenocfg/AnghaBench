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
 scalar_t__ ERROR_FILE_EXISTS ; 
 scalar_t__ ERROR_INTERNET_EXTENDED_ERROR ; 
 scalar_t__ ERROR_INTERNET_INCORRECT_HANDLE_TYPE ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int FTP_TRANSFER_TYPE_UNKNOWN ; 
 scalar_t__ FtpGetFileA (int /*<<< orphan*/ *,char*,char*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GENERIC_WRITE ; 
 scalar_t__ GetFileAttributesA (char*) ; 
 scalar_t__ GetLastError () ; 
 scalar_t__ INVALID_FILE_ATTRIBUTES ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_getfile(HINTERNET hFtp, HINTERNET hConnect)
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
    bRet = FtpGetFileA(NULL, NULL, "should_be_non_existing_deadbeef", FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_HANDLE ||
         GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_HANDLE (win98) or ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Test to show session handle is checked before 'condition flags' */
    SetLastError(0xdeadbeef);
    bRet = FtpGetFileA(NULL, "welcome.msg", "should_be_non_existing_deadbeef", FALSE, FILE_ATTRIBUTE_NORMAL, 5, 0);
    ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_HANDLE,
        "Expected ERROR_INVALID_HANDLE, got %d\n", GetLastError());

    /* Make sure we start clean */

    DeleteFileA("should_be_non_existing_deadbeef");
    DeleteFileA("should_also_be_non_existing_deadbeef");

    /* No remote file */
    SetLastError(0xdeadbeef);
    bRet = FtpGetFileA(hFtp, NULL, "should_be_non_existing_deadbeef", FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());
    ok (GetFileAttributesA("should_be_non_existing_deadbeef") == INVALID_FILE_ATTRIBUTES,
        "Local file should not have been created\n");
    DeleteFileA("should_be_non_existing_deadbeef");

    /* No local file */
    SetLastError(0xdeadbeef);
    bRet = FtpGetFileA(hFtp, "welcome.msg", NULL, FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
    ok ( GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Zero attributes */
    bRet = FtpGetFileA(hFtp, "welcome.msg", "should_be_existing_non_deadbeef", FALSE, 0, FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == TRUE, "Expected FtpGetFileA to succeed\n");
    ok (GetFileAttributesA("should_be_existing_non_deadbeef") != INVALID_FILE_ATTRIBUTES,
        "Local file should have been created\n");
    DeleteFileA("should_be_existing_non_deadbeef");

    /* Illegal condition flags */
    SetLastError(0xdeadbeef);
    bRet = FtpGetFileA(hFtp, "welcome.msg", "should_be_non_existing_deadbeef", FALSE, FILE_ATTRIBUTE_NORMAL, 0xffffffff, 0);
    ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_EXTENDED_ERROR || GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INTERNET_EXTENDED_ERROR or ERROR_INVALID_PARAMETER (win98), got %d\n", GetLastError());
    ok (GetFileAttributesA("should_be_non_existing_deadbeef") == INVALID_FILE_ATTRIBUTES,
        "Local file should not have been created\n");
    DeleteFileA("should_be_non_existing_deadbeef");

    /* Remote file doesn't exist (and local doesn't exist as well) */
    SetLastError(0xdeadbeef);
    bRet = FtpGetFileA(hFtp, "should_be_non_existing_deadbeef", "should_also_be_non_existing_deadbeef", FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_EXTENDED_ERROR,
        "Expected ERROR_INTERNET_EXTENDED_ERROR, got %d\n", GetLastError());
    /* Currently Wine always creates the local file (even on failure) which is not correct, hence the test */
    ok (GetFileAttributesA("should_also_be_non_existing_deadbeef") == INVALID_FILE_ATTRIBUTES,
        "Local file should not have been created\n");

    DeleteFileA("should_also_be_non_existing_deadbeef");

    /* Same call as the previous but now the local file does exists. Windows just removes the file if the call fails
     * even if the local existed before!
     */

    /* Create a temporary local file */
    SetLastError(0xdeadbeef);
    hFile = CreateFileA("should_also_be_non_existing_deadbeef", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 0, NULL);
    ok ( hFile != NULL, "Error creating a local file : %d\n", GetLastError());
    CloseHandle(hFile);
    SetLastError(0xdeadbeef);
    bRet = FtpGetFileA(hFtp, "should_be_non_existing_deadbeef", "should_also_be_non_existing_deadbeef", FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_EXTENDED_ERROR,
        "Expected ERROR_INTERNET_EXTENDED_ERROR, got %d\n", GetLastError());
    /* Currently Wine always creates the local file (even on failure) which is not correct, hence the test */
    ok (GetFileAttributesA("should_also_be_non_existing_deadbeef") == INVALID_FILE_ATTRIBUTES,
        "Local file should not have been created\n");

    DeleteFileA("should_also_be_non_existing_deadbeef");

    /* This one should succeed */
    SetLastError(0xdeadbeef);
    bRet = FtpGetFileA(hFtp, "welcome.msg", "should_be_existing_non_deadbeef", FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == TRUE, "Expected FtpGetFileA to fail\n");
    ok ( GetLastError() == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got %d\n", GetLastError());

    if (GetFileAttributesA("should_be_existing_non_deadbeef") != INVALID_FILE_ATTRIBUTES)
    {
        /* Should succeed as fFailIfExists is set to FALSE (meaning don't fail if local file exists) */
        SetLastError(0xdeadbeef);
        bRet = FtpGetFileA(hFtp, "welcome.msg", "should_be_non_existing_deadbeef", FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
        ok ( bRet == TRUE, "Expected FtpGetFileA to succeed\n");
        ok ( GetLastError() == ERROR_SUCCESS,
            "Expected ERROR_SUCCESS, got %d\n", GetLastError());

        /* Should fail as fFailIfExists is set to TRUE */
        SetLastError(0xdeadbeef);
        bRet = FtpGetFileA(hFtp, "welcome.msg", "should_be_non_existing_deadbeef", TRUE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
        ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
        ok ( GetLastError() == ERROR_FILE_EXISTS,
            "Expected ERROR_FILE_EXISTS, got %d\n", GetLastError());

        /* Prove that the existence of the local file is checked first (or at least reported last) */
        SetLastError(0xdeadbeef);
        bRet = FtpGetFileA(hFtp, "should_be_non_existing_deadbeef", "should_be_non_existing_deadbeef", TRUE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
        ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
        ok ( GetLastError() == ERROR_FILE_EXISTS,
            "Expected ERROR_FILE_EXISTS, got %d\n", GetLastError());

        DeleteFileA("should_be_existing_non_deadbeef");
    }

    /* Test to show the parameter checking order depends on the Windows version */
    SetLastError(0xdeadbeef);
    bRet = FtpGetFileA(hConnect, NULL, "should_be_non_existing_deadbeef", FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE ||
         GetLastError() == ERROR_INVALID_PARAMETER,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE (win98) or ERROR_INVALID_PARAMETER, got %d\n", GetLastError());

    /* Test to show that 'session handle type' is checked before 'condition flags' */
    SetLastError(0xdeadbeef);
    bRet = FtpGetFileA(hConnect, "welcome.msg", "should_be_non_existing_deadbeef", FALSE, FILE_ATTRIBUTE_NORMAL, 5, 0);
    ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got %d\n", GetLastError());

    SetLastError(0xdeadbeef);
    bRet = FtpGetFileA(hConnect, "should_be_non_existing_deadbeef", "should_be_non_existing_deadbeef", TRUE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
        "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got %d\n", GetLastError());
}