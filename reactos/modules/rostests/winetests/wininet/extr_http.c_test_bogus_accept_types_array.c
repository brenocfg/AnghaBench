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
 int HTTP_QUERY_ACCEPT ; 
 int HTTP_QUERY_FLAG_REQUEST_HEADERS ; 
 int /*<<< orphan*/ * HttpOpenRequestA (int /*<<< orphan*/ *,char*,char*,char*,char*,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int HttpQueryInfoA (int /*<<< orphan*/ *,int,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INTERNET_FLAG_FORMS_SUBMIT ; 
 int /*<<< orphan*/  INTERNET_OPEN_TYPE_DIRECT ; 
 int /*<<< orphan*/  INTERNET_SERVICE_HTTP ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternetConnectA (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InternetOpenA (char*,int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 

__attribute__((used)) static void test_bogus_accept_types_array(void)
{
    HINTERNET ses, con, req;
    static const char *types[] = { (const char *)6240, "*/*", "%p", "", (const char *)0xffffffff, "*/*", NULL };
    DWORD size, error;
    char buffer[32];
    BOOL ret;

    ses = InternetOpenA("MERONG(0.9/;p)", INTERNET_OPEN_TYPE_DIRECT, "", "", 0);
    con = InternetConnectA(ses, "www.winehq.org", 80, NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);
    req = HttpOpenRequestA(con, "POST", "/post/post_action.php", "HTTP/1.0", "", types, INTERNET_FLAG_FORMS_SUBMIT, 0);

    ok(req != NULL, "HttpOpenRequest failed: %u\n", GetLastError());

    buffer[0] = 0;
    size = sizeof(buffer);
    SetLastError(0xdeadbeef);
    ret = HttpQueryInfoA(req, HTTP_QUERY_ACCEPT | HTTP_QUERY_FLAG_REQUEST_HEADERS, buffer, &size, NULL);
    error = GetLastError();
    ok(!ret || broken(ret), "HttpQueryInfo succeeded\n");
    if (!ret) ok(error == ERROR_HTTP_HEADER_NOT_FOUND, "expected ERROR_HTTP_HEADER_NOT_FOUND, got %u\n", error);
    ok(broken(!strcmp(buffer, ", */*, %p, , , */*")) /* IE6 */ ||
       broken(!strcmp(buffer, "*/*, %p, */*")) /* IE7/8 */ ||
       !strcmp(buffer, ""), "got '%s' expected ''\n", buffer);

    InternetCloseHandle(req);
    InternetCloseHandle(con);
    InternetCloseHandle(ses);
}