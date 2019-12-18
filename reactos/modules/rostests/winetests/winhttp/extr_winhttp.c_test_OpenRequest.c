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
typedef  scalar_t__ DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 scalar_t__ ERROR_WINHTTP_CANNOT_CONNECT ; 
 scalar_t__ ERROR_WINHTTP_NAME_NOT_RESOLVED ; 
 scalar_t__ ERROR_WINHTTP_TIMEOUT ; 
 scalar_t__ GetLastError () ; 
 int /*<<< orphan*/  INTERNET_DEFAULT_HTTP_PORT ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  WINHTTP_ACCESS_TYPE_DEFAULT_PROXY ; 
 int /*<<< orphan*/  WINHTTP_DEFAULT_ACCEPT_TYPES ; 
 int /*<<< orphan*/  WINHTTP_NO_ADDITIONAL_HEADERS ; 
 int /*<<< orphan*/  WINHTTP_NO_PROXY_BYPASS ; 
 int /*<<< orphan*/  WINHTTP_NO_PROXY_NAME ; 
 int /*<<< orphan*/  WINHTTP_NO_REFERER ; 
 scalar_t__ WSAEINVAL ; 
 scalar_t__ WinHttpCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WinHttpConnect (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WinHttpOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WinHttpOpenRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ WinHttpSendRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_useragent ; 
 int /*<<< orphan*/ * test_winehq ; 

__attribute__((used)) static void test_OpenRequest (void)
{
    BOOL ret;
    HINTERNET session, request, connection;
    DWORD err;

    SetLastError(0xdeadbeef);
    session = WinHttpOpen(test_useragent, WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
        WINHTTP_NO_PROXY_NAME, WINHTTP_NO_PROXY_BYPASS, 0);
    err = GetLastError();
    ok(session != NULL, "WinHttpOpen failed to open session.\n");
    ok(err == ERROR_SUCCESS, "got %u\n", err);

    /* Test with a bad server name */
    SetLastError(0xdeadbeef);
    connection = WinHttpConnect(session, NULL, INTERNET_DEFAULT_HTTP_PORT, 0);
    err = GetLastError();
    ok (connection == NULL, "WinHttpConnect succeeded in opening connection to NULL server argument.\n");
    ok(err == ERROR_INVALID_PARAMETER, "Expected ERROR_INVALID_PARAMETER, got %u.\n", err);

    /* Test with a valid server name */
    SetLastError(0xdeadbeef);
    connection = WinHttpConnect (session, test_winehq, INTERNET_DEFAULT_HTTP_PORT, 0);
    err = GetLastError();
    ok(connection != NULL, "WinHttpConnect failed to open a connection, error: %u.\n", err);
    ok(err == ERROR_SUCCESS || broken(err == WSAEINVAL) /* < win7 */, "got %u\n", err);

    SetLastError(0xdeadbeef);
    request = WinHttpOpenRequest(connection, NULL, NULL, NULL, WINHTTP_NO_REFERER,
        WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
    err = GetLastError();
    if (request == NULL && err == ERROR_WINHTTP_NAME_NOT_RESOLVED)
    {
        skip("Network unreachable, skipping.\n");
        goto done;
    }
    ok(request != NULL, "WinHttpOpenrequest failed to open a request, error: %u.\n", err);
    ok(err == ERROR_SUCCESS, "got %u\n", err);

    SetLastError(0xdeadbeef);
    ret = WinHttpSendRequest(request, WINHTTP_NO_ADDITIONAL_HEADERS, 0, NULL, 0, 0, 0);
    err = GetLastError();
    if (!ret && (err == ERROR_WINHTTP_CANNOT_CONNECT || err == ERROR_WINHTTP_TIMEOUT))
    {
        skip("Connection failed, skipping.\n");
        goto done;
    }
    ok(ret, "WinHttpSendRequest failed: %u\n", err);
    ok(err == ERROR_SUCCESS, "got %u\n", err);

    SetLastError(0xdeadbeef);
    ret = WinHttpCloseHandle(request);
    err = GetLastError();
    ok(ret, "WinHttpCloseHandle failed on closing request, got %u.\n", err);
    ok(err == ERROR_SUCCESS, "got %u\n", err);

 done:
    ret = WinHttpCloseHandle(connection);
    ok(ret == TRUE, "WinHttpCloseHandle failed on closing connection, got %d.\n", ret);
    ret = WinHttpCloseHandle(session);
    ok(ret == TRUE, "WinHttpCloseHandle failed on closing session, got %d.\n", ret);

}