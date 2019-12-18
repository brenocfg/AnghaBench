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
typedef  int /*<<< orphan*/  ulArg ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INTERNET_BAD_OPTION_LENGTH ; 
 scalar_t__ ERROR_INTERNET_INCORRECT_HANDLE_TYPE ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ FALSE ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * HttpOpenRequestA (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERNET_OPEN_TYPE_DIRECT ; 
 int /*<<< orphan*/  INTERNET_OPTION_ERROR_MASK ; 
 int /*<<< orphan*/  INTERNET_OPTION_POLICY ; 
 int /*<<< orphan*/  INTERNET_OPTION_REFRESH ; 
 int /*<<< orphan*/  INTERNET_OPTION_SETTINGS_CHANGED ; 
 int /*<<< orphan*/  INTERNET_SERVICE_HTTP ; 
 scalar_t__ InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternetConnectA (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InternetOpenA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ InternetQueryOptionW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int*) ; 
 scalar_t__ InternetSetOptionA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void*,int) ; 
 scalar_t__ InternetSetOptionW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_InternetSetOption(void)
{
    HINTERNET ses, con, req;
    ULONG ulArg;
    DWORD size;
    BOOL ret;

    ses = InternetOpenA(NULL, INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    ok(ses != 0, "InternetOpen failed: 0x%08x\n", GetLastError());
    con = InternetConnectA(ses, "www.winehq.org", 80, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    ok(con != 0, "InternetConnect failed: 0x%08x\n", GetLastError());
    req = HttpOpenRequestA(con, "GET", "/", NULL, NULL, NULL, 0, 0);
    ok(req != 0, "HttpOpenRequest failed: 0x%08x\n", GetLastError());

    /* INTERNET_OPTION_POLICY tests */
    SetLastError(0xdeadbeef);
    ret = InternetSetOptionW(ses, INTERNET_OPTION_POLICY, NULL, 0);
    ok(ret == FALSE, "InternetSetOption should've failed\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "GetLastError should've "
            "given ERROR_INVALID_PARAMETER, gave: 0x%08x\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = InternetQueryOptionW(ses, INTERNET_OPTION_POLICY, NULL, 0);
    ok(ret == FALSE, "InternetQueryOption should've failed\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "GetLastError should've "
            "given ERROR_INVALID_PARAMETER, gave: 0x%08x\n", GetLastError());

    /* INTERNET_OPTION_ERROR_MASK tests */
    SetLastError(0xdeadbeef);
    size = sizeof(ulArg);
    ret = InternetQueryOptionW(NULL, INTERNET_OPTION_ERROR_MASK, (void*)&ulArg, &size);
    ok(ret == FALSE, "InternetQueryOption should've failed\n");
    ok(GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE, "GetLastError() = %x\n", GetLastError());

    SetLastError(0xdeadbeef);
    ulArg = 11;
    ret = InternetSetOptionA(NULL, INTERNET_OPTION_ERROR_MASK, (void*)&ulArg, sizeof(ULONG));
    ok(ret == FALSE, "InternetSetOption should've failed\n");
    ok(GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE, "GetLastError() = %x\n", GetLastError());

    SetLastError(0xdeadbeef);
    ulArg = 11;
    ret = InternetSetOptionA(req, INTERNET_OPTION_ERROR_MASK, (void*)&ulArg, 20);
    ok(ret == FALSE, "InternetSetOption should've failed\n");
    ok(GetLastError() == ERROR_INTERNET_BAD_OPTION_LENGTH, "GetLastError() = %d\n", GetLastError());

    ulArg = 11;
    ret = InternetSetOptionA(req, INTERNET_OPTION_ERROR_MASK, (void*)&ulArg, sizeof(ULONG));
    ok(ret == TRUE, "InternetSetOption should've succeeded\n");

    SetLastError(0xdeadbeef);
    ulArg = 4;
    ret = InternetSetOptionA(req, INTERNET_OPTION_ERROR_MASK, (void*)&ulArg, sizeof(ULONG));
    ok(ret == FALSE, "InternetSetOption should've failed\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "GetLastError() = %x\n", GetLastError());

    SetLastError(0xdeadbeef);
    ulArg = 16;
    ret = InternetSetOptionA(req, INTERNET_OPTION_ERROR_MASK, (void*)&ulArg, sizeof(ULONG));
    ok(ret == FALSE, "InternetSetOption should've failed\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "GetLastError() = %x\n", GetLastError());

    ret = InternetSetOptionA(req, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
    ok(ret == TRUE, "InternetSetOption should've succeeded\n");

    ret = InternetSetOptionA(con, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
    ok(ret == TRUE, "InternetSetOption should've succeeded\n");

    ret = InternetSetOptionA(ses, INTERNET_OPTION_SETTINGS_CHANGED, NULL, 0);
    ok(ret == TRUE, "InternetSetOption should've succeeded\n");

    ret = InternetSetOptionA(ses, INTERNET_OPTION_REFRESH, NULL, 0);
    ok(ret == TRUE, "InternetSetOption should've succeeded\n");

    SetLastError(0xdeadbeef);
    ret = InternetSetOptionA(req, INTERNET_OPTION_REFRESH, NULL, 0);
    ok(ret == FALSE, "InternetSetOption should've failed\n");
    ok(GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE, "GetLastError() = %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = InternetSetOptionA(con, INTERNET_OPTION_REFRESH, NULL, 0);
    ok(ret == FALSE, "InternetSetOption should've failed\n");
    ok(GetLastError() == ERROR_INTERNET_INCORRECT_HANDLE_TYPE, "GetLastError() = %u\n", GetLastError());

    ret = InternetCloseHandle(req);
    ok(ret == TRUE, "InternetCloseHandle failed: 0x%08x\n", GetLastError());
    ret = InternetCloseHandle(con);
    ok(ret == TRUE, "InternetCloseHandle failed: 0x%08x\n", GetLastError());
    ret = InternetCloseHandle(ses);
    ok(ret == TRUE, "InternetCloseHandle failed: 0x%08x\n", GetLastError());
}