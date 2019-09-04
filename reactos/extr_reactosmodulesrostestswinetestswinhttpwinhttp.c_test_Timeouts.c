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
typedef  int /*<<< orphan*/  value ;
typedef  int /*<<< orphan*/ * HINTERNET ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_SUCCESS ; 
 int ERROR_WINHTTP_INCORRECT_HANDLE_TYPE ; 
 int GetLastError () ; 
 int /*<<< orphan*/  SetLastError (int) ; 
 int /*<<< orphan*/  WINHTTP_OPTION_CONNECT_TIMEOUT ; 
 int /*<<< orphan*/  WINHTTP_OPTION_RECEIVE_TIMEOUT ; 
 int /*<<< orphan*/  WINHTTP_OPTION_RESOLVE_TIMEOUT ; 
 int /*<<< orphan*/  WINHTTP_OPTION_SEND_TIMEOUT ; 
 int /*<<< orphan*/  WinHttpCloseHandle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * WinHttpConnect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WinHttpOpen (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * WinHttpOpenRequest (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int WinHttpQueryOption (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*) ; 
 int WinHttpSetOption (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int) ; 
 int WinHttpSetTimeouts (int /*<<< orphan*/ *,int,int,int,int) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int /*<<< orphan*/  test_useragent ; 
 int /*<<< orphan*/  test_winehq ; 

__attribute__((used)) static void test_Timeouts (void)
{
    BOOL ret;
    DWORD value, size;
    HINTERNET ses, req, con;

    ses = WinHttpOpen(test_useragent, 0, NULL, NULL, 0);
    ok(ses != NULL, "failed to open session %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(ses, -2, 0, 0, 0);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(ses, 0, -2, 0, 0);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(ses, 0, 0, -2, 0);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(ses, 0, 0, 0, -2);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(ses, -1, -1, -1, -1);
    ok(ret, "%u\n", GetLastError());
    ok(GetLastError() == ERROR_SUCCESS || broken(GetLastError() == 0xdeadbeef) /* < win7 */,
       "expected ERROR_SUCCESS, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(ses, 0, 0, 0, 0);
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(ses, 0x0123, 0x4567, 0x89ab, 0xcdef);
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0x0123, "Expected 0x0123, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0x4567, "Expected 0x4567, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_SEND_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0x89ab, "Expected 0x89ab, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xcdef, "Expected 0xcdef, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0, "Expected 0, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0, "Expected 0, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_SEND_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_SEND_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0, "Expected 0, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0, "Expected 0, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeefdead;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeefdead;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeefdead;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_SEND_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_SEND_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeefdead;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    con = WinHttpConnect(ses, test_winehq, 0, 0);
    ok(con != NULL, "failed to open a connection %u\n", GetLastError());

    /* Timeout values should match the last one set for session */
    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(con, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(con, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(con, WINHTTP_OPTION_SEND_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(con, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(con, -2, 0, 0, 0);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(con, 0, -2, 0, 0);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(con, 0, 0, -2, 0);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(con, 0, 0, 0, -2);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(con, -1, -1, -1, -1);
    ok(!ret && GetLastError() == ERROR_WINHTTP_INCORRECT_HANDLE_TYPE,
       "expected ERROR_WINHTTP_INVALID_TYPE, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(con, 0, 0, 0, 0);
    ok(!ret && GetLastError() == ERROR_WINHTTP_INCORRECT_HANDLE_TYPE,
       "expected ERROR_WINHTTP_INVALID_TYPE, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0;
    ret = WinHttpSetOption(con, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, sizeof(value));
    ok(!ret && GetLastError() == ERROR_WINHTTP_INCORRECT_HANDLE_TYPE,
       "expected ERROR_WINHTTP_INVALID_TYPE, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0;
    ret = WinHttpSetOption(con, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, sizeof(value));
    ok(!ret && GetLastError() == ERROR_WINHTTP_INCORRECT_HANDLE_TYPE,
       "expected ERROR_WINHTTP_INVALID_TYPE, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0;
    ret = WinHttpSetOption(con, WINHTTP_OPTION_SEND_TIMEOUT, &value, sizeof(value));
    ok(!ret && GetLastError() == ERROR_WINHTTP_INCORRECT_HANDLE_TYPE,
       "expected ERROR_WINHTTP_INVALID_TYPE, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0;
    ret = WinHttpSetOption(con, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, sizeof(value));
    ok(!ret && GetLastError() == ERROR_WINHTTP_INCORRECT_HANDLE_TYPE,
       "expected ERROR_WINHTTP_INVALID_TYPE, got %u\n", GetLastError());

    /* Changing timeout values for session should affect the values for connection */
    SetLastError(0xdeadbeef);
    value = 0xdead;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(con, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xdead, "Expected 0xdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdead;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(con, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xdead, "Expected 0xdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdead;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_SEND_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(con, WINHTTP_OPTION_SEND_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xdead, "Expected 0xdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdead;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(con, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xdead, "Expected 0xdead, got %u\n", value);

    req = WinHttpOpenRequest(con, NULL, NULL, NULL, NULL, NULL, 0);
    ok(req != NULL, "failed to open a request %u\n", GetLastError());

    /* Timeout values should match the last one set for session */
    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xdead, "Expected 0xdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xdead, "Expected 0xdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_SEND_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xdead, "Expected 0xdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xdead, "Expected 0xdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(req, -2, 0, 0, 0);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(req, 0, -2, 0, 0);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(req, 0, 0, -2, 0);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(req, 0, 0, 0, -2);
    ok(!ret && GetLastError() == ERROR_INVALID_PARAMETER,
       "expected ERROR_INVALID_PARAMETER, got %u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(req, -1, -1, -1, -1);
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(req, 0, 0, 0, 0);
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    ret = WinHttpSetTimeouts(req, 0xcdef, 0x89ab, 0x4567, 0x0123);
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xcdef, "Expected 0xcdef, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0x89ab, "Expected 0x89ab, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_SEND_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0x4567, "Expected 0x4567, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0x0123, "Expected 0x0123, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0;
    ret = WinHttpSetOption(req, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0, "Expected 0, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0;
    ret = WinHttpSetOption(req, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0, "Expected 0, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0;
    ret = WinHttpSetOption(req, WINHTTP_OPTION_SEND_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_SEND_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0, "Expected 0, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0;
    ret = WinHttpSetOption(req, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0, "Expected 0, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeefdead;
    ret = WinHttpSetOption(req, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeefdead;
    ret = WinHttpSetOption(req, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeefdead;
    ret = WinHttpSetOption(req, WINHTTP_OPTION_SEND_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_SEND_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeefdead;
    ret = WinHttpSetOption(req, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    /* Changing timeout values for session should not affect the values for a request,
     * neither should the other way around.
     */
    SetLastError(0xdeadbeef);
    value = 0xbeefdead;
    ret = WinHttpSetOption(req, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xdead, "Expected 0xdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeefdead;
    ret = WinHttpSetOption(req, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xdead, "Expected 0xdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeefdead;
    ret = WinHttpSetOption(req, WINHTTP_OPTION_SEND_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_SEND_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xdead, "Expected 0xdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeefdead;
    ret = WinHttpSetOption(req, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(ses, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xdead, "Expected 0xdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeef;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_RESOLVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeef;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_CONNECT_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeef;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_SEND_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_SEND_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    SetLastError(0xdeadbeef);
    value = 0xbeef;
    ret = WinHttpSetOption(ses, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, sizeof(value));
    ok(ret, "%u\n", GetLastError());

    SetLastError(0xdeadbeef);
    value = 0xdeadbeef;
    size  = sizeof(DWORD);
    ret = WinHttpQueryOption(req, WINHTTP_OPTION_RECEIVE_TIMEOUT, &value, &size);
    ok(ret, "%u\n", GetLastError());
    ok(value == 0xbeefdead, "Expected 0xbeefdead, got %u\n", value);

    WinHttpCloseHandle(req);
    WinHttpCloseHandle(con);
    WinHttpCloseHandle(ses);
}