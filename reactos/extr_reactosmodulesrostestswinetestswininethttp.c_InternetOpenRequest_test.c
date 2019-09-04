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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INTERNET_NAME_NOT_RESOLVED ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/ * HttpOpenRequestA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HttpOpenRequestW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HttpSendRequestA (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HttpSendRequestW (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INTERNET_DEFAULT_HTTP_PORT ; 
 int /*<<< orphan*/  INTERNET_FLAG_NO_CACHE_WRITE ; 
 int /*<<< orphan*/  INTERNET_OPEN_TYPE_PRECONFIG ; 
 int /*<<< orphan*/  INTERNET_SERVICE_HTTP ; 
 int /*<<< orphan*/  InternetCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * InternetConnectA (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * InternetOpenA (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void InternetOpenRequest_test(void)
{
    HINTERNET session, connect, request;
    static const char *types[] = { "*", "", NULL };
    static const WCHAR slash[] = {'/', 0}, any[] = {'*', 0}, empty[] = {0};
    static const WCHAR *typesW[] = { any, empty, NULL };
    BOOL ret;

    session = InternetOpenA("Wine Regression Test", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
    ok(session != NULL ,"Unable to open Internet session\n");

    connect = InternetConnectA(session, NULL, INTERNET_DEFAULT_HTTP_PORT, NULL, NULL,
                              INTERNET_SERVICE_HTTP, 0, 0);
    ok(connect == NULL, "InternetConnectA should have failed\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "InternetConnectA with NULL server named should have failed with ERROR_INVALID_PARAMETER instead of %d\n", GetLastError());

    connect = InternetConnectA(session, "", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL,
                              INTERNET_SERVICE_HTTP, 0, 0);
    ok(connect == NULL, "InternetConnectA should have failed\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER, "InternetConnectA with blank server named should have failed with ERROR_INVALID_PARAMETER instead of %d\n", GetLastError());

    connect = InternetConnectA(session, "test.winehq.org", INTERNET_DEFAULT_HTTP_PORT, NULL, NULL,
                              INTERNET_SERVICE_HTTP, 0, 0);
    ok(connect != NULL, "Unable to connect to http://test.winehq.org with error %d\n", GetLastError());

    request = HttpOpenRequestA(connect, NULL, "/", NULL, NULL, types, INTERNET_FLAG_NO_CACHE_WRITE, 0);
    if (!request && GetLastError() == ERROR_INTERNET_NAME_NOT_RESOLVED)
    {
        skip( "Network unreachable, skipping test\n" );
        goto done;
    }
    ok(request != NULL, "Failed to open request handle err %u\n", GetLastError());

    ret = HttpSendRequestW(request, NULL, 0, NULL, 0);
    ok(ret, "HttpSendRequest failed: %u\n", GetLastError());
    ok(InternetCloseHandle(request), "Close request handle failed\n");

    request = HttpOpenRequestW(connect, NULL, slash, NULL, NULL, typesW, INTERNET_FLAG_NO_CACHE_WRITE, 0);
    ok(request != NULL, "Failed to open request handle err %u\n", GetLastError());

    ret = HttpSendRequestA(request, NULL, 0, NULL, 0);
    ok(ret, "HttpSendRequest failed: %u\n", GetLastError());
    ok(InternetCloseHandle(request), "Close request handle failed\n");

done:
    ok(InternetCloseHandle(connect), "Close connect handle failed\n");
    ok(InternetCloseHandle(session), "Close session handle failed\n");
}