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
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ COOKIE_STATE_ACCEPT ; 
 scalar_t__ COOKIE_STATE_REJECT ; 
 char* ERROR_INVALID_OPERATION ; 
 char* ERROR_NO_MORE_ITEMS ; 
 char* GetLastError () ; 
 int /*<<< orphan*/  GetModuleHandleA (char*) ; 
 int /*<<< orphan*/  GetProcAddress (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  INTERNET_COOKIE_HTTPONLY ; 
 int InternetGetCookieA (char*,int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int InternetGetCookieExA (char*,int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int InternetSetCookieA (char*,int /*<<< orphan*/ *,char*) ; 
 scalar_t__ InternetSetCookieExA (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_cookie_attrs(void)
{
    char buf[100];
    DWORD size, state;
    BOOL ret;

    if(!GetProcAddress(GetModuleHandleA("wininet.dll"), "DeleteWpadCacheForNetworks")) {
        win_skip("Skipping cookie attributes tests. Too old IE.\n");
        return;
    }

    ret = InternetSetCookieA("http://cookie.attrs.com/bar", NULL, "A=data; httponly");
    ok(!ret && GetLastError() == ERROR_INVALID_OPERATION, "InternetSetCookie returned: %x (%u)\n", ret, GetLastError());

    SetLastError(0xdeadbeef);
    state = InternetSetCookieExA("http://cookie.attrs.com/bar", NULL, "A=data; httponly", 0, 0);
    ok(state == COOKIE_STATE_REJECT && GetLastError() == ERROR_INVALID_OPERATION,
       "InternetSetCookieEx returned: %x (%u)\n", ret, GetLastError());

    size = sizeof(buf);
    ret = InternetGetCookieExA("http://cookie.attrs.com/", NULL, buf, &size, INTERNET_COOKIE_HTTPONLY, NULL);
    ok(!ret && GetLastError() == ERROR_NO_MORE_ITEMS, "InternetGetCookieEx returned: %x (%u)\n", ret, GetLastError());

    state = InternetSetCookieExA("http://cookie.attrs.com/bar",NULL,"A=data; httponly", INTERNET_COOKIE_HTTPONLY, 0);
    ok(state == COOKIE_STATE_ACCEPT,"InternetSetCookieEx failed: %u\n", GetLastError());

    size = sizeof(buf);
    ret = InternetGetCookieA("http://cookie.attrs.com/", NULL, buf, &size);
    ok(!ret && GetLastError() == ERROR_NO_MORE_ITEMS, "InternetGetCookie returned: %x (%u)\n", ret, GetLastError());

    size = sizeof(buf);
    ret = InternetGetCookieExA("http://cookie.attrs.com/", NULL, buf, &size, 0, NULL);
    ok(!ret && GetLastError() == ERROR_NO_MORE_ITEMS, "InternetGetCookieEx returned: %x (%u)\n", ret, GetLastError());

    size = sizeof(buf);
    ret = InternetGetCookieExA("http://cookie.attrs.com/", NULL, buf, &size, INTERNET_COOKIE_HTTPONLY, NULL);
    ok(ret, "InternetGetCookieEx failed: %u\n", GetLastError());
    ok(!strcmp(buf, "A=data"), "data = %s\n", buf);

    /* Try to override httponly cookie with non-httponly one */
    ret = InternetSetCookieA("http://cookie.attrs.com/bar", NULL, "A=test");
    ok(!ret && GetLastError() == ERROR_INVALID_OPERATION, "InternetSetCookie returned: %x (%u)\n", ret, GetLastError());

    SetLastError(0xdeadbeef);
    state = InternetSetCookieExA("http://cookie.attrs.com/bar", NULL, "A=data", 0, 0);
    ok(state == COOKIE_STATE_REJECT && GetLastError() == ERROR_INVALID_OPERATION,
       "InternetSetCookieEx returned: %x (%u)\n", ret, GetLastError());

    size = sizeof(buf);
    ret = InternetGetCookieExA("http://cookie.attrs.com/", NULL, buf, &size, INTERNET_COOKIE_HTTPONLY, NULL);
    ok(ret, "InternetGetCookieEx failed: %u\n", GetLastError());
    ok(!strcmp(buf, "A=data"), "data = %s\n", buf);

}