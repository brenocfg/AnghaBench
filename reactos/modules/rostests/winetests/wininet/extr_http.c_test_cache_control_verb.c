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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/ * HttpOpenRequestA (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HttpSendRequestA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERNET_FLAG_NO_CACHE_WRITE ; 
 int /*<<< orphan*/  INTERNET_OPEN_TYPE_DIRECT ; 
 int /*<<< orphan*/  INTERNET_SERVICE_HTTP ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternetConnectA (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InternetOpenA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  test_status_code (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_cache_control_verb(int port)
{
    HINTERNET session, connect, request;
    BOOL ret;

    session = InternetOpenA("winetest", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    ok(session != NULL, "InternetOpen failed\n");

    connect = InternetConnectA(session, "localhost", port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    ok(connect != NULL, "InternetConnect failed\n");

    request = HttpOpenRequestA(connect, "RPC_OUT_DATA", "/test_cache_control_verb", NULL, NULL, NULL,
                              INTERNET_FLAG_NO_CACHE_WRITE, 0);
    ok(request != NULL, "HttpOpenRequest failed\n");
    ret = HttpSendRequestA(request, NULL, 0, NULL, 0);
    ok(ret, "HttpSendRequest failed %u\n", GetLastError());
    test_status_code(request, 200);
    InternetCloseHandle(request);

    request = HttpOpenRequestA(connect, "POST", "/test_cache_control_verb", NULL, NULL, NULL,
                              INTERNET_FLAG_NO_CACHE_WRITE, 0);
    ok(request != NULL, "HttpOpenRequest failed\n");
    ret = HttpSendRequestA(request, NULL, 0, NULL, 0);
    ok(ret, "HttpSendRequest failed %u\n", GetLastError());
    test_status_code(request, 200);
    InternetCloseHandle(request);

    request = HttpOpenRequestA(connect, "HEAD", "/test_cache_control_verb", NULL, NULL, NULL,
                              INTERNET_FLAG_NO_CACHE_WRITE, 0);
    ok(request != NULL, "HttpOpenRequest failed\n");
    ret = HttpSendRequestA(request, NULL, 0, NULL, 0);
    ok(ret, "HttpSendRequest failed %u\n", GetLastError());
    test_status_code(request, 200);
    InternetCloseHandle(request);

    request = HttpOpenRequestA(connect, "GET", "/test_cache_control_verb", NULL, NULL, NULL,
                              INTERNET_FLAG_NO_CACHE_WRITE, 0);
    ok(request != NULL, "HttpOpenRequest failed\n");
    ret = HttpSendRequestA(request, NULL, 0, NULL, 0);
    ok(ret, "HttpSendRequest failed %u\n", GetLastError());
    test_status_code(request, 200);
    InternetCloseHandle(request);

    InternetCloseHandle(connect);
    InternetCloseHandle(session);
}