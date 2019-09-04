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
typedef  int DWORD ;
typedef  char CHAR ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 char* ERROR_INSUFFICIENT_BUFFER ; 
 char* ERROR_INTERNET_INCORRECT_HANDLE_TYPE ; 
 char* ERROR_INVALID_HANDLE ; 
 char* ERROR_INVALID_PARAMETER ; 
 char* ERROR_SUCCESS ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FTP_TRANSFER_TYPE_ASCII ; 
 scalar_t__ FtpGetCurrentDirectoryA (int /*<<< orphan*/ *,char*,int*) ; 
 char* GetLastError () ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 scalar_t__ pFtpCommandA (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int strcmp (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_get_current_dir(HINTERNET hFtp, HINTERNET hConnect)
{
    BOOL    bRet;
    DWORD   dwCurrentDirectoryLen = MAX_PATH;
    CHAR    lpszCurrentDirectory[MAX_PATH];

    if (!pFtpCommandA)
    {
        win_skip("FtpCommandA() is not available. Skipping the Ftp get_current_dir tests\n");
        return;
    }

    /* change directories to get a more interesting pwd */
    bRet = pFtpCommandA(hFtp, FALSE, FTP_TRANSFER_TYPE_ASCII, "CWD pub/", 0, NULL);
    if(bRet == FALSE)
    {
        skip("Failed to change directories in test_get_current_dir(HINTERNET hFtp).\n");
        return;
    }

    /* test with all NULL arguments */
    SetLastError(0xdeadbeef);
    bRet = FtpGetCurrentDirectoryA( NULL, NULL, 0 );
    ok ( bRet == FALSE, "Expected FtpGetCurrentDirectoryA to fail\n" );
    ok ( GetLastError() == ERROR_INVALID_HANDLE, "Expected ERROR_INVALID_HANDLE, got: %d\n", GetLastError());

    /* test with NULL parameters instead of expected LPSTR/LPDWORD */
    SetLastError(0xdeadbeef);
    bRet = FtpGetCurrentDirectoryA( hFtp, NULL, 0 );
    ok ( bRet == FALSE, "Expected FtpGetCurrentDirectoryA to fail\n" );
    ok ( GetLastError() == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got: %d\n", GetLastError());

    /* test with no valid handle and valid parameters */
    SetLastError(0xdeadbeef);
    bRet = FtpGetCurrentDirectoryA( NULL, lpszCurrentDirectory, &dwCurrentDirectoryLen );
    ok ( bRet == FALSE, "Expected FtpGetCurrentDirectoryA to fail\n" );
    ok ( GetLastError() == ERROR_INVALID_HANDLE, "Expected ERROR_INVALID_HANDLE, got: %d\n", GetLastError());

    /* test with invalid dwCurrentDirectory and all other parameters correct */
    SetLastError(0xdeadbeef);
    bRet = FtpGetCurrentDirectoryA( hFtp, lpszCurrentDirectory, 0 );
    ok ( bRet == FALSE, "Expected FtpGetCurrentDirectoryA to fail\n" );
    ok ( GetLastError() == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got: %d\n", GetLastError());

    /* test with invalid lpszCurrentDirectory and all other parameters correct */
    SetLastError(0xdeadbeef);
    bRet = FtpGetCurrentDirectoryA( hFtp, NULL, &dwCurrentDirectoryLen );
    ok ( bRet == FALSE, "Expected FtpGetCurrentDirectoryA to fail\n" );
    ok ( GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Expected ERROR_INSUFFICIENT_BUFFER, got: %d\n", GetLastError());

    /* test to show it checks the handle type */
    SetLastError(0xdeadbeef);
    bRet = FtpGetCurrentDirectoryA( hConnect, lpszCurrentDirectory, &dwCurrentDirectoryLen );
    ok ( bRet == FALSE, "Expected FtpGetCurrentDirectoryA to fail\n" );
    ok ( GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE,
    "Expected ERROR_INTERNET_INCORRECT_HANDLE_TYPE, got: %d\n", GetLastError());

    /* test for the current directory with legitimate values */
    SetLastError(0xdeadbeef);
    bRet = FtpGetCurrentDirectoryA( hFtp, lpszCurrentDirectory, &dwCurrentDirectoryLen );
    ok ( bRet == TRUE, "Expected FtpGetCurrentDirectoryA to pass\n" );
    ok ( !strcmp(lpszCurrentDirectory, "/pub"), "Expected returned value \"%s\" to match \"/pub\"\n", lpszCurrentDirectory);
    ok ( GetLastError() == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got: %d\n", GetLastError());

    /* test for the current directory with a size only large enough to
     * fit the string and not the null terminating character */
    SetLastError(0xdeadbeef);
    dwCurrentDirectoryLen = 4;
    lpszCurrentDirectory[4] = 'a'; /* set position 4 of the array to something else to make sure a leftover \0 isn't fooling the test */
    bRet = FtpGetCurrentDirectoryA( hFtp, lpszCurrentDirectory, &dwCurrentDirectoryLen );
    ok ( bRet == FALSE, "Expected FtpGetCurrentDirectoryA to fail\n");
    ok ( strcmp(lpszCurrentDirectory, "/pub"), "Expected returned value \"%s\" to not match \"/pub\"\n", lpszCurrentDirectory);
    ok ( GetLastError() == ERROR_INSUFFICIENT_BUFFER, "Expected ERROR_INSUFFICIENT_BUFFER, got: %d\n", GetLastError());

    /* test for the current directory with a size large enough to store
     * the expected string as well as the null terminating character */
    SetLastError(0xdeadbeef);
    dwCurrentDirectoryLen = 5;
    bRet = FtpGetCurrentDirectoryA( hFtp, lpszCurrentDirectory, &dwCurrentDirectoryLen );
    ok ( bRet == TRUE, "Expected FtpGetCurrentDirectoryA to pass\n");
    ok ( !strcmp(lpszCurrentDirectory, "/pub"), "Expected returned value \"%s\" to match \"/pub\"\n", lpszCurrentDirectory);
    ok ( GetLastError() == ERROR_SUCCESS, "Expected ERROR_SUCCESS, got: %d\n", GetLastError());
}