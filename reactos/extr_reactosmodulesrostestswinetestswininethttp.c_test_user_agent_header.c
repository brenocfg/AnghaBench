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
typedef  int /*<<< orphan*/  buffer ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_HTTP_HEADER_NOT_FOUND ; 
 char* GetLastError () ; 
 int /*<<< orphan*/  HTTP_ADDREQ_FLAG_ADD_IF_NEW ; 
 int HTTP_QUERY_ACCEPT ; 
 int HTTP_QUERY_FLAG_REQUEST_HEADERS ; 
 int HTTP_QUERY_USER_AGENT ; 
 int HttpAddRequestHeadersA (int /*<<< orphan*/ *,char*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HttpOpenRequestA (int /*<<< orphan*/ *,char*,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HttpQueryInfoA (int /*<<< orphan*/ *,int,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTERNET_OPEN_TYPE_PRECONFIG ; 
 int /*<<< orphan*/  INTERNET_SERVICE_HTTP ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternetConnectA (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InternetOpenA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_user_agent_header(void)
{
    HINTERNET ses, con, req;
    DWORD size, err;
    char buffer[64];
    BOOL ret;

    ses = InternetOpenA("Gizmo5", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    ok(ses != NULL, "InternetOpen failed\n");

    con = InternetConnectA(ses, "test.winehq.org", 80, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    ok(con != NULL, "InternetConnect failed\n");

    req = HttpOpenRequestA(con, "GET", "/tests/hello.html", "HTTP/1.0", NULL, NULL, 0, 0);
    ok(req != NULL, "HttpOpenRequest failed\n");

    size = sizeof(buffer);
    ret = HttpQueryInfoA(req, HTTP_QUERY_USER_AGENT | HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer, &size, NULL);
    err = GetLastError();
    ok(!ret, "HttpQueryInfo succeeded\n");
    ok(err == ERROR_HTTP_HEADER_NOT_FOUND, "expected ERROR_HTTP_HEADER_NOT_FOUND, got %u\n", err);

    ret = HttpAddRequestHeadersA(req, "User-Agent: Gizmo Project\r\n", ~0u, HTTP_ADDREQ_FLAG_ADD_IF_NEW);
    ok(ret, "HttpAddRequestHeaders succeeded\n");

    size = sizeof(buffer);
    ret = HttpQueryInfoA(req, HTTP_QUERY_USER_AGENT | HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer, &size, NULL);
    err = GetLastError();
    ok(ret, "HttpQueryInfo failed\n");

    InternetCloseHandle(req);

    req = HttpOpenRequestA(con, "GET", "/", "HTTP/1.0", NULL, NULL, 0, 0);
    ok(req != NULL, "HttpOpenRequest failed\n");

    size = sizeof(buffer);
    ret = HttpQueryInfoA(req, HTTP_QUERY_ACCEPT | HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer, &size, NULL);
    err = GetLastError();
    ok(!ret, "HttpQueryInfo succeeded\n");
    ok(err == ERROR_HTTP_HEADER_NOT_FOUND, "expected ERROR_HTTP_HEADER_NOT_FOUND, got %u\n", err);

    ret = HttpAddRequestHeadersA(req, "Accept: audio/*, image/*, text/*\r\nUser-Agent: Gizmo Project\r\n", ~0u, HTTP_ADDREQ_FLAG_ADD_IF_NEW);
    ok(ret, "HttpAddRequestHeaders failed\n");

    buffer[0] = 0;
    size = sizeof(buffer);
    ret = HttpQueryInfoA(req, HTTP_QUERY_ACCEPT | HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer, &size, NULL);
    ok(ret, "HttpQueryInfo failed: %u\n", GetLastError());
    ok(!strcmp(buffer, "audio/*, image/*, text/*"), "got '%s' expected 'audio/*, image/*, text/*'\n", buffer);

    InternetCloseHandle(req);
    InternetCloseHandle(con);
    InternetCloseHandle(ses);
}