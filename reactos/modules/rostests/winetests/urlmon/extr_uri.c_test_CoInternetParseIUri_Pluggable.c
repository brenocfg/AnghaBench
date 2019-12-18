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
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUri ;
typedef  scalar_t__ HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PARSE_CANONICALIZE ; 
 int /*<<< orphan*/  ParseUrl ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int URL_ESCAPE_UNSAFE ; 
 int URL_UNESCAPE ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 scalar_t__ pCoInternetParseIUri (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 scalar_t__ pCreateUri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  parse_action ; 
 int parse_flags ; 
 int /*<<< orphan*/ * parse_resultW ; 
 int /*<<< orphan*/  parse_urlW ; 
 scalar_t__ wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_CoInternetParseIUri_Pluggable(void) {
    HRESULT hr;
    IUri *uri = NULL;

    hr = pCreateUri(parse_urlW, 0, 0, &uri);
    ok(SUCCEEDED(hr), "Error: Expected CreateUri to succeed, but got 0x%08x.\n", hr);
    if(SUCCEEDED(hr)) {
        WCHAR result[200];
        DWORD result_len;

        SET_EXPECT(ParseUrl);

        parse_action = PARSE_CANONICALIZE;
        parse_flags = URL_UNESCAPE|URL_ESCAPE_UNSAFE;

        hr = pCoInternetParseIUri(uri, parse_action, parse_flags, result, 200, &result_len, 0);
        ok(hr == S_OK, "Error: CoInternetParseIUri returned 0x%08x, expected 0x%08x.\n", hr, S_OK);

        CHECK_CALLED(ParseUrl);

        if(SUCCEEDED(hr)) {
            ok(result_len == lstrlenW(parse_resultW), "Error: Expected %d, but got %d.\n",
                lstrlenW(parse_resultW), result_len);
            ok(!lstrcmpW(result, parse_resultW), "Error: Expected %s, but got %s.\n",
                wine_dbgstr_w(parse_resultW), wine_dbgstr_w(result));
        }
    }
    if(uri) IUri_Release(uri);
}