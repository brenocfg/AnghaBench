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
typedef  int /*<<< orphan*/  feature ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ERROR_INSUFFICIENT_BUFFER ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int ERROR_WINHTTP_INCORRECT_HANDLE_TYPE ; 
 int ERROR_WINHTTP_NAME_NOT_RESOLVED ; 
 int GetLastError () ; 
 int /*<<< orphan*/  INTERNET_DEFAULT_HTTP_PORT ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WINHTTP_DEFAULT_ACCEPT_TYPES ; 
 int WINHTTP_DISABLE_COOKIES ; 
 int /*<<< orphan*/  WINHTTP_NO_REFERER ; 
 int /*<<< orphan*/  WINHTTP_OPTION_DISABLE_FEATURE ; 
 int /*<<< orphan*/  WINHTTP_OPTION_REDIRECT_POLICY ; 
 int WINHTTP_OPTION_REDIRECT_POLICY_ALWAYS ; 
 int WINHTTP_OPTION_REDIRECT_POLICY_DISALLOW_HTTPS_TO_HTTP ; 
 int WinHttpCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WinHttpConnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WinHttpOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WinHttpOpenRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int WinHttpQueryOption (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*) ; 
 int WinHttpSetOption (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  test_useragent ; 
 int /*<<< orphan*/  test_winehq ; 

__attribute__((used)) static void test_QueryOption(void)
{
    BOOL ret;
    HINTERNET session, request, connection;
    DWORD feature, size;

    SetLastError(0xdeadbeef);
    session = WinHttpOpen(test_useragent, 0, 0, 0, 0);
    ok(session != NULL, "WinHttpOpen failed to open session, error %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpQueryOption(session, WINHTTP_OPTION_REDIRECT_POLICY, NULL, NULL);
    ok(!ret, "should fail to set redirect policy %u\n", GetLastError());
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    size = 0xdeadbeef;
    SetLastError(0xdeadbeef);
    ret = WinHttpQueryOption(session, WINHTTP_OPTION_REDIRECT_POLICY, NULL, &size);
    ok(!ret, "should fail to query option\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "expected ERROR_INSUFFICIENT_BUFFER, got %u\n", GetLastError());
    ok(size == 4, "expected 4, got %u\n", size);

    feature = 0xdeadbeef;
    size = sizeof(feature) - 1;
    SetLastError(0xdeadbeef);
    ret = WinHttpQueryOption(session, WINHTTP_OPTION_REDIRECT_POLICY, &feature, &size);
    ok(!ret, "should fail to query option\n");
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "expected ERROR_INSUFFICIENT_BUFFER, got %u\n", GetLastError());
    ok(size == 4, "expected 4, got %u\n", size);

    feature = 0xdeadbeef;
    size = sizeof(feature) + 1;
    SetLastError(0xdeadbeef);
    ret = WinHttpQueryOption(session, WINHTTP_OPTION_REDIRECT_POLICY, &feature, &size);
    ok(ret, "failed to query option %u\n", GetLastError());
    ok(GetLastError() == ERROR_SUCCESS || broken(GetLastError() == 0xdeadbeef) /* < win7 */,
       "got %u\n", GetLastError());
    ok(size == sizeof(feature), "WinHttpQueryOption should set the size: %u\n", size);
    ok(feature == WINHTTP_OPTION_REDIRECT_POLICY_DISALLOW_HTTPS_TO_HTTP,
       "expected WINHTTP_OPTION_REDIRECT_POLICY_DISALLOW_HTTPS_TO_HTTP, got %#x\n", feature);

    SetLastError(0xdeadbeef);
    ret = WinHttpSetOption(session, WINHTTP_OPTION_REDIRECT_POLICY, NULL, sizeof(feature));
    ok(!ret, "should fail to set redirect policy %u\n", GetLastError());
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    feature = WINHTTP_OPTION_REDIRECT_POLICY_ALWAYS;
    SetLastError(0xdeadbeef);
    ret = WinHttpSetOption(session, WINHTTP_OPTION_REDIRECT_POLICY, &feature, sizeof(feature) - 1);
    ok(!ret, "should fail to set redirect policy %u\n", GetLastError());
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "expected ERROR_INSUFFICIENT_BUFFER, got %u\n", GetLastError());

    feature = WINHTTP_OPTION_REDIRECT_POLICY_ALWAYS;
    SetLastError(0xdeadbeef);
    ret = WinHttpSetOption(session, WINHTTP_OPTION_REDIRECT_POLICY, &feature, sizeof(feature) + 1);
    ok(!ret, "should fail to set redirect policy %u\n", GetLastError());
    ok(GetLastError() == ERROR_INSUFFICIENT_BUFFER,
       "expected ERROR_INSUFFICIENT_BUFFER, got %u\n", GetLastError());

    feature = WINHTTP_OPTION_REDIRECT_POLICY_ALWAYS;
    SetLastError(0xdeadbeef);
    ret = WinHttpSetOption(session, WINHTTP_OPTION_REDIRECT_POLICY, &feature, sizeof(feature));
    ok(ret, "failed to set redirect policy %u\n", GetLastError());

    feature = 0xdeadbeef;
    size = sizeof(feature);
    SetLastError(0xdeadbeef);
    ret = WinHttpQueryOption(session, WINHTTP_OPTION_REDIRECT_POLICY, &feature, &size);
    ok(ret, "failed to query option %u\n", GetLastError());
    ok(feature == WINHTTP_OPTION_REDIRECT_POLICY_ALWAYS,
       "expected WINHTTP_OPTION_REDIRECT_POLICY_ALWAYS, got %#x\n", feature);

    feature = WINHTTP_DISABLE_COOKIES;
    SetLastError(0xdeadbeef);
    ret = WinHttpSetOption(session, WINHTTP_OPTION_DISABLE_FEATURE, &feature, sizeof(feature));
    ok(!ret, "should fail to set disable feature for a session\n");
    ok(GetLastError() == ERROR_WINHTTP_INCORRECT_HANDLE_TYPE,
       "expected ERROR_WINHTTP_INCORRECT_HANDLE_TYPE, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    connection = WinHttpConnect(session, test_winehq, INTERNET_DEFAULT_HTTP_PORT, 0);
    ok(connection != NULL, "WinHttpConnect failed to open a connection, error: %u\n", GetLastError());

    feature = WINHTTP_DISABLE_COOKIES;
    SetLastError(0xdeadbeef);
    ret = WinHttpSetOption(connection, WINHTTP_OPTION_DISABLE_FEATURE, &feature, sizeof(feature));
    ok(!ret, "should fail to set disable feature for a connection\n");
    ok(GetLastError() == ERROR_WINHTTP_INCORRECT_HANDLE_TYPE,
       "expected ERROR_WINHTTP_INCORRECT_HANDLE_TYPE, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    request = WinHttpOpenRequest(connection, NULL, NULL, NULL, WINHTTP_NO_REFERER,
                                 WINHTTP_DEFAULT_ACCEPT_TYPES, 0);
    if (request == NULL && GetLastError() == ERROR_WINHTTP_NAME_NOT_RESOLVED)
    {
        skip("Network unreachable, skipping the test\n");
        goto done;
    }

    feature = 0xdeadbeef;
    size = sizeof(feature);
    SetLastError(0xdeadbeef);
    ret = WinHttpQueryOption(request, WINHTTP_OPTION_DISABLE_FEATURE, &feature, &size);
    ok(!ret, "should fail to query disable feature for a request\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    feature = 0;
    size = sizeof(feature);
    SetLastError(0xdeadbeef);
    ret = WinHttpSetOption(request, WINHTTP_OPTION_DISABLE_FEATURE, &feature, sizeof(feature));
    ok(ret, "failed to set feature %u\n", GetLastError());

    feature = 0xffffffff;
    size = sizeof(feature);
    SetLastError(0xdeadbeef);
    ret = WinHttpSetOption(request, WINHTTP_OPTION_DISABLE_FEATURE, &feature, sizeof(feature));
    ok(ret, "failed to set feature %u\n", GetLastError());

    feature = WINHTTP_DISABLE_COOKIES;
    size = sizeof(feature);
    SetLastError(0xdeadbeef);
    ret = WinHttpSetOption(request, WINHTTP_OPTION_DISABLE_FEATURE, &feature, sizeof(feature));
    ok(ret, "failed to set feature %u\n", GetLastError());

    size = 0;
    SetLastError(0xdeadbeef);
    ret = WinHttpQueryOption(request, WINHTTP_OPTION_DISABLE_FEATURE, NULL, &size);
    ok(!ret, "should fail to query disable feature for a request\n");
    ok(GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpCloseHandle(request);
    ok(ret, "WinHttpCloseHandle failed on closing request: %u\n", GetLastError());

done:
    SetLastError(0xdeadbeef);
    ret = WinHttpCloseHandle(connection);
    ok(ret, "WinHttpCloseHandle failed on closing connection: %u\n", GetLastError());
    SetLastError(0xdeadbeef);
    ret = WinHttpCloseHandle(session);
    ok(ret, "WinHttpCloseHandle failed on closing session: %u\n", GetLastError());
}