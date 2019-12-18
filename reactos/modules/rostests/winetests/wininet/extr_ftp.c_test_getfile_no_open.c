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
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INTERNET_NOT_INITIALIZED ; 
 scalar_t__ ERROR_INVALID_HANDLE ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FILE_ATTRIBUTE_NORMAL ; 
 int /*<<< orphan*/  FTP_TRANSFER_TYPE_UNKNOWN ; 
 scalar_t__ FtpGetFileA (int /*<<< orphan*/ *,char*,char*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_getfile_no_open(void)
{
    BOOL      bRet;

    /* Invalid internet handle, the others are valid parameters */
    SetLastError(0xdeadbeef);
    bRet = FtpGetFileA(NULL, "welcome.msg", "should_be_non_existing_deadbeef", FALSE, FILE_ATTRIBUTE_NORMAL, FTP_TRANSFER_TYPE_UNKNOWN, 0);
    ok ( bRet == FALSE, "Expected FtpGetFileA to fail\n");
    ok ( GetLastError() == ERROR_INTERNET_NOT_INITIALIZED ||
         GetLastError() == ERROR_INVALID_HANDLE,
        "Expected ERROR_INTERNET_NOT_INITIALIZED or ERROR_INVALID_HANDLE (win98), got %d\n", GetLastError());
}