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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  scalar_t__ DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_WINHTTP_CANNOT_CONNECT ; 
 scalar_t__ ERROR_WINHTTP_TIMEOUT ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  WinHttpCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WinHttpConnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WinHttpOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WinHttpOpenRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WinHttpSendRequest (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_useragent ; 
 int /*<<< orphan*/  test_winehq ; 

__attribute__((used)) static void test_empty_headers_param(void)
{
    static const WCHAR empty[]  = {0};
    HINTERNET ses, con, req;
    DWORD err;
    BOOL ret;

    ses = WinHttpOpen(test_useragent, 0, NULL, NULL, 0);
    ok(ses != NULL, "failed to open session %u\n", GetLastError());

    con = WinHttpConnect(ses, test_winehq, 80, 0);
    ok(con != NULL, "failed to open a connection %u\n", GetLastError());

    req = WinHttpOpenRequest(con, NULL, NULL, NULL, NULL, NULL, 0);
    ok(req != NULL, "failed to open a request %u\n", GetLastError());

    ret = WinHttpSendRequest(req, empty, 0, NULL, 0, 0, 0);
    err = GetLastError();
    if (!ret && (err == ERROR_WINHTTP_CANNOT_CONNECT || err == ERROR_WINHTTP_TIMEOUT))
    {
        skip("connection failed, skipping\n");
        goto done;
    }
    ok(ret, "failed to send request %u\n", GetLastError());

 done:
    WinHttpCloseHandle(req);
    WinHttpCloseHandle(con);
    WinHttpCloseHandle(ses);
}