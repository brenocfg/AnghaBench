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
 scalar_t__ ERROR_INTERNET_CANNOT_CONNECT ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * HttpOpenRequestA (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ HttpSendRequestA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERNET_DEFAULT_HTTPS_PORT ; 
 int /*<<< orphan*/  INTERNET_FLAG_SECURE ; 
 int /*<<< orphan*/  INTERNET_OPEN_TYPE_PRECONFIG ; 
 int /*<<< orphan*/  INTERNET_SERVICE_HTTP ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternetConnectA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InternetOpenA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static BOOL can_do_https(void)
{
    HINTERNET ses, con, req;
    BOOL ret;

    ses = InternetOpenA("winetest", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    ok(ses != NULL, "InternetOpen failed\n");

    con = InternetConnectA(ses, "test.winehq.org", INTERNET_DEFAULT_HTTPS_PORT,
            NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    ok(con != NULL, "InternetConnect failed\n");

    req = HttpOpenRequestA(con, "GET", "/tests/hello.html", NULL, NULL, NULL,
            INTERNET_FLAG_SECURE, 0);
    ok(req != NULL, "HttpOpenRequest failed\n");

    ret = HttpSendRequestA(req, NULL, 0, NULL, 0);
    ok(ret || broken(GetLastError() == ERROR_INTERNET_CANNOT_CONNECT),
        "request failed: %u\n", GetLastError());

    InternetCloseHandle(req);
    InternetCloseHandle(con);
    InternetCloseHandle(ses);
    return ret;
}