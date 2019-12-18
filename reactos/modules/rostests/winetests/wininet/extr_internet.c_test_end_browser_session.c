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
typedef  scalar_t__ DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_NO_MORE_ITEMS ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  INTERNET_OPTION_END_BROWSER_SESSION ; 
 int InternetGetCookieA (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int InternetSetCookieA (char*,int /*<<< orphan*/ *,char*) ; 
 int InternetSetOptionA (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_end_browser_session(void)
{
    DWORD len;
    BOOL ret;

    ret = InternetSetCookieA("http://www.example.com/test_end", NULL, "A=B");
    ok(ret == TRUE, "InternetSetCookie failed\n");

    len = 1024;
    ret = InternetGetCookieA("http://www.example.com/test_end", NULL, NULL, &len);
    ok(ret == TRUE,"InternetGetCookie failed\n");
    ok(len != 0, "len = 0\n");

    ret = InternetSetOptionA(NULL, INTERNET_OPTION_END_BROWSER_SESSION, NULL, 0);
    ok(ret, "InternetSetOption(INTERNET_OPTION_END_BROWSER_SESSION) failed: %u\n", GetLastError());

    len = 1024;
    ret = InternetGetCookieA("http://www.example.com/test_end", NULL, NULL, &len);
    ok(!ret && GetLastError() == ERROR_NO_MORE_ITEMS, "InternetGetCookie returned %x (%u)\n", ret, GetLastError());
    ok(!len, "len = %u\n", len);
}