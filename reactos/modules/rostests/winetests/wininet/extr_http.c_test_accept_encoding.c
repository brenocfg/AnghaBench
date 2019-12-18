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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int HTTP_ADDREQ_FLAG_ADD ; 
 int HTTP_ADDREQ_FLAG_REPLACE ; 
 int /*<<< orphan*/  HttpAddRequestHeadersA (int /*<<< orphan*/ *,char*,unsigned int,int) ; 
 int /*<<< orphan*/ * HttpOpenRequestA (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HttpSendRequestA (int /*<<< orphan*/ *,char*,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERNET_OPEN_TYPE_DIRECT ; 
 int /*<<< orphan*/  INTERNET_SERVICE_HTTP ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternetConnectA (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InternetOpenA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  receive_simple_request (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 int /*<<< orphan*/  test_status_code (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void test_accept_encoding(int port)
{
    HINTERNET ses, con, req;
    char buf[1000];
    BOOL ret;

    ses = InternetOpenA("winetest", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
    ok(ses != NULL, "InternetOpen failed\n");

    con = InternetConnectA(ses, "localhost", port, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    ok(con != NULL, "InternetConnect failed\n");

    req = HttpOpenRequestA(con, "GET", "/echo_request", "HTTP/1.0", NULL, NULL, 0, 0);
    ok(req != NULL, "HttpOpenRequest failed\n");

    ret = HttpAddRequestHeadersA(req, "Accept-Encoding: gzip\r\n", ~0u, HTTP_ADDREQ_FLAG_REPLACE | HTTP_ADDREQ_FLAG_ADD);
    ok(ret, "HttpAddRequestHeaders failed\n");

    ret = HttpSendRequestA(req, NULL,  0, NULL, 0);
    ok(ret, "HttpSendRequestA failed\n");

    test_status_code(req, 200);
    receive_simple_request(req, buf, sizeof(buf));
    ok(strstr(buf, "Accept-Encoding: gzip") != NULL, "Accept-Encoding header not found in %s\n", buf);

    InternetCloseHandle(req);

    req = HttpOpenRequestA(con, "GET", "/echo_request", "HTTP/1.0", NULL, NULL, 0, 0);
    ok(req != NULL, "HttpOpenRequest failed\n");

    ret = HttpSendRequestA(req, "Accept-Encoding: gzip", ~0u, NULL, 0);
    ok(ret, "HttpSendRequestA failed\n");

    test_status_code(req, 200);
    receive_simple_request(req, buf, sizeof(buf));
    ok(strstr(buf, "Accept-Encoding: gzip") != NULL, "Accept-Encoding header not found in %s\n", buf);

    InternetCloseHandle(req);
    InternetCloseHandle(con);
    InternetCloseHandle(ses);
}