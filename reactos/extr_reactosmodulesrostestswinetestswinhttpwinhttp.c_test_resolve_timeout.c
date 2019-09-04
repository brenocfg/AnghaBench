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
typedef  int /*<<< orphan*/  timeout ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_WINHTTP_CANNOT_CONNECT ; 
 scalar_t__ ERROR_WINHTTP_NAME_NOT_RESOLVED ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WINHTTP_OPTION_RESOLVE_TIMEOUT ; 
 int /*<<< orphan*/  WinHttpCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WinHttpConnect (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WinHttpOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WinHttpOpenRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WinHttpSendRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WinHttpSetOption (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  proxy_active () ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_useragent ; 
 char const* test_winehq ; 

__attribute__((used)) static void test_resolve_timeout(void)
{
    static const WCHAR nxdomain[] =
        {'n','x','d','o','m','a','i','n','.','w','i','n','e','h','q','.','o','r','g',0};
    HINTERNET ses, con, req;
    DWORD timeout;
    BOOL ret;

    if (! proxy_active())
    {
        ses = WinHttpOpen(test_useragent, 0, NULL, NULL, 0);
        ok(ses != NULL, "failed to open session %u\n", GetLastError());

        timeout = 10000;
        ret = WinHttpSetOption(ses, WINHTTP_OPTION_RESOLVE_TIMEOUT, &timeout, sizeof(timeout));
        ok(ret, "failed to set resolve timeout %u\n", GetLastError());

        con = WinHttpConnect(ses, nxdomain, 0, 0);
        ok(con != NULL, "failed to open a connection %u\n", GetLastError());

        req = WinHttpOpenRequest(con, NULL, NULL, NULL, NULL, NULL, 0);
        ok(req != NULL, "failed to open a request %u\n", GetLastError());

        SetLastError(0xdeadbeef);
        ret = WinHttpSendRequest(req, NULL, 0, NULL, 0, 0, 0);
        if (ret)
        {
            skip("nxdomain returned success. Broken ISP redirects?\n");
            goto done;
        }
        ok(GetLastError() == ERROR_WINHTTP_NAME_NOT_RESOLVED,
           "expected ERROR_WINHTTP_NAME_NOT_RESOLVED got %u\n", GetLastError());

        WinHttpCloseHandle(req);
        WinHttpCloseHandle(con);
        WinHttpCloseHandle(ses);
    }
    else
       skip("Skipping host resolution tests, host resolution preformed by proxy\n");

    ses = WinHttpOpen(test_useragent, 0, NULL, NULL, 0);
    ok(ses != NULL, "failed to open session %u\n", GetLastError());

    timeout = 10000;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_RESOLVE_TIMEOUT, &timeout, sizeof(timeout));
    ok(ret, "failed to set resolve timeout %u\n", GetLastError());

    con = WinHttpConnect(ses, test_winehq, 0, 0);
    ok(con != NULL, "failed to open a connection %u\n", GetLastError());

    req = WinHttpOpenRequest(con, NULL, NULL, NULL, NULL, NULL, 0);
    ok(req != NULL, "failed to open a request %u\n", GetLastError());

    ret = WinHttpSendRequest(req, NULL, 0, NULL, 0, 0, 0);
    if (!ret && GetLastError() == ERROR_WINHTTP_CANNOT_CONNECT)
    {
        skip("connection failed, skipping\n");
        goto done;
    }
    ok(ret, "failed to send request\n");

 done:
    WinHttpCloseHandle(req);
    WinHttpCloseHandle(con);
    WinHttpCloseHandle(ses);
}