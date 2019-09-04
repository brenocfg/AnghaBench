#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  request; } ;
typedef  TYPE_1__ test_request_t ;
typedef  int /*<<< orphan*/  file_name ;
typedef  int /*<<< orphan*/ * HANDLE ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int DeleteFileA (char*) ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_INTERNET_ITEM_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_SHARING_VIOLATION ; 
 int /*<<< orphan*/  GetLastError () ; 
 int HttpSendRequestA (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERNET_DEFAULT_HTTP_PORT ; 
 int /*<<< orphan*/  INTERNET_OPTION_DATAFILE_NAME ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ ) ; 
 int InternetLockRequestFile (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int InternetQueryOptionA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int InternetUnlockRequestFile (int /*<<< orphan*/ *) ; 
 int MAX_PATH ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  open_simple_request (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void InternetLockRequestFile_test(void)
{
    char file_name[MAX_PATH];
    test_request_t req;
    HANDLE lock, lock2;
    DWORD size;
    BOOL ret;

    open_simple_request(&req, "test.winehq.org", INTERNET_DEFAULT_HTTP_PORT, NULL, "/tests/hello.html");

    size = sizeof(file_name);
    ret = InternetQueryOptionA(req.request, INTERNET_OPTION_DATAFILE_NAME, file_name, &size);
    ok(!ret, "InternetQueryOptionA(INTERNET_OPTION_DATAFILE_NAME) succeeded\n");
    ok(GetLastError() == ERROR_INTERNET_ITEM_NOT_FOUND, "GetLastError()=%u\n", GetLastError());
    ok(!size, "size = %d\n", size);

    lock = NULL;
    ret = InternetLockRequestFile(req.request, &lock);
    ok(!ret && GetLastError() == ERROR_FILE_NOT_FOUND, "InternetLockRequestFile returned: %x(%u)\n", ret, GetLastError());

    ret = HttpSendRequestA(req.request, NULL, 0, NULL, 0);
    ok(ret, "HttpSendRequest failed: %u\n", GetLastError());

    size = sizeof(file_name);
    ret = InternetQueryOptionA(req.request, INTERNET_OPTION_DATAFILE_NAME, file_name, &size);
    ok(ret, "InternetQueryOptionA(INTERNET_OPTION_DATAFILE_NAME) failed: %u\n", GetLastError());

    ret = InternetLockRequestFile(req.request, &lock);
    ok(ret, "InternetLockRequestFile returned: %x(%u)\n", ret, GetLastError());
    ok(lock != NULL, "lock == NULL\n");

    ret = InternetLockRequestFile(req.request, &lock2);
    ok(ret, "InternetLockRequestFile returned: %x(%u)\n", ret, GetLastError());
    ok(lock == lock2, "lock != lock2\n");

    ret = InternetUnlockRequestFile(lock2);
    ok(ret, "InternetUnlockRequestFile failed: %u\n", GetLastError());

    ret = DeleteFileA(file_name);
    ok(!ret && GetLastError() == ERROR_SHARING_VIOLATION, "Deleting file returned %x(%u)\n", ret, GetLastError());

    ok(InternetCloseHandle(req.request), "Close request handle failed\n");

    ret = DeleteFileA(file_name);
    ok(!ret && GetLastError() == ERROR_SHARING_VIOLATION, "Deleting file returned %x(%u)\n", ret, GetLastError());

    ret = InternetUnlockRequestFile(lock);
    ok(ret, "InternetUnlockRequestFile failed: %u\n", GetLastError());

    ret = DeleteFileA(file_name);
    ok(ret, "Deleting file returned %x(%u)\n", ret, GetLastError());
}