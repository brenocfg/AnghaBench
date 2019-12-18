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
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int ARRAY_SIZE (char const*) ; 
 int /*<<< orphan*/  ASSOCSTR_EXECUTABLE ; 
 int /*<<< orphan*/  ASSOCSTR_FRIENDLYAPPNAME ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_NO_ASSOCIATION ; 
 int E_FAIL ; 
 int E_INVALIDARG ; 
 int E_UNEXPECTED ; 
 int HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int MAX_PATH ; 
 int S_FALSE ; 
 int S_OK ; 
 int /*<<< orphan*/ * badBad ; 
 int /*<<< orphan*/ * dotBad ; 
 int /*<<< orphan*/ * dotHtml ; 
 int /*<<< orphan*/  expect_hr (int,int) ; 
 int /*<<< orphan*/  invalid ; 
 int /*<<< orphan*/  lstrcmpiW (char*,char const*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  open ; 
 int pAssocQueryStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_getstring_bad(void)
{
    static const WCHAR openwith[] = {'O','p','e','n','W','i','t','h','.','e','x','e',0};
    WCHAR buf[MAX_PATH];
    HRESULT hr;
    DWORD len;

    if (!pAssocQueryStringW)
    {
        win_skip("AssocQueryStringW() is missing\n");
        return;
    }

    len = 0xdeadbeef;
    hr = pAssocQueryStringW(0, ASSOCSTR_EXECUTABLE, NULL, open, NULL, &len);
    expect_hr(E_INVALIDARG, hr);
    ok(len == 0xdeadbeef, "got %u\n", len);

    len = 0xdeadbeef;
    hr = pAssocQueryStringW(0, ASSOCSTR_EXECUTABLE, badBad, open, NULL, &len);
    ok(hr == E_FAIL ||
       hr == HRESULT_FROM_WIN32(ERROR_NO_ASSOCIATION), /* Win9x/WinMe/NT4/W2K/Vista/W2K8 */
       "Unexpected result : %08x\n", hr);
    ok(len == 0xdeadbeef, "got %u\n", len);

    len = ARRAY_SIZE(buf);
    hr = pAssocQueryStringW(0, ASSOCSTR_EXECUTABLE, dotBad, open, buf, &len);
    ok(hr == E_FAIL ||
       hr == HRESULT_FROM_WIN32(ERROR_NO_ASSOCIATION) /* Win9x/WinMe/NT4/W2K/Vista/W2K8 */ ||
       hr == S_OK /* Win8 */,
       "Unexpected result : %08x\n", hr);
    if (hr == S_OK)
    {
        ok(len < ARRAY_SIZE(buf), "got %u\n", len);
        ok(!lstrcmpiW(buf + len - ARRAY_SIZE(openwith), openwith), "wrong data\n");
    }

    len = 0xdeadbeef;
    hr = pAssocQueryStringW(0, ASSOCSTR_EXECUTABLE, dotHtml, invalid, NULL, &len);
    ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) ||
       hr == HRESULT_FROM_WIN32(ERROR_NO_ASSOCIATION), /* Win9x/WinMe/NT4/W2K/Vista/W2K8 */
       "Unexpected result : %08x\n", hr);
    ok(len == 0xdeadbeef, "got %u\n", len);

    hr = pAssocQueryStringW(0, ASSOCSTR_EXECUTABLE, dotHtml, open, NULL, NULL);
    ok(hr == E_UNEXPECTED ||
       hr == E_INVALIDARG, /* Win9x/WinMe/NT4/W2K/Vista/W2K8 */
       "Unexpected result : %08x\n", hr);

    len = 0xdeadbeef;
    hr = pAssocQueryStringW(0, ASSOCSTR_FRIENDLYAPPNAME, NULL, open, NULL, &len);
    expect_hr(E_INVALIDARG, hr);
    ok(len == 0xdeadbeef, "got %u\n", len);

    len = 0xdeadbeef;
    hr = pAssocQueryStringW(0, ASSOCSTR_FRIENDLYAPPNAME, badBad, open, NULL, &len);
    ok(hr == E_FAIL ||
       hr == HRESULT_FROM_WIN32(ERROR_NO_ASSOCIATION), /* Win9x/WinMe/NT4/W2K/Vista/W2K8 */
       "Unexpected result : %08x\n", hr);
    ok(len == 0xdeadbeef, "got %u\n", len);

    len = 0xdeadbeef;
    hr = pAssocQueryStringW(0, ASSOCSTR_FRIENDLYAPPNAME, dotBad, open, NULL, &len);
    ok(hr == E_FAIL ||
       hr == HRESULT_FROM_WIN32(ERROR_NO_ASSOCIATION) /* Win9x/WinMe/NT4/W2K/Vista/W2K8 */ ||
       hr == HRESULT_FROM_WIN32(ERROR_NOT_FOUND) /* Win8 */ ||
       hr == S_FALSE, /* Win10 */
       "Unexpected result : %08x\n", hr);
    ok((hr == S_FALSE && len < ARRAY_SIZE(buf)) || len == 0xdeadbeef,
       "got hr=%08x and len=%u\n", hr, len);

    len = 0xdeadbeef;
    hr = pAssocQueryStringW(0, ASSOCSTR_FRIENDLYAPPNAME, dotHtml, invalid, NULL, &len);
    ok(hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) ||
       hr == HRESULT_FROM_WIN32(ERROR_NO_ASSOCIATION) || /* W2K/Vista/W2K8 */
       hr == E_FAIL, /* Win9x/WinMe/NT4 */
       "Unexpected result : %08x\n", hr);
    ok(len == 0xdeadbeef, "got %u\n", len);

    hr = pAssocQueryStringW(0, ASSOCSTR_FRIENDLYAPPNAME, dotHtml, open, NULL, NULL);
    ok(hr == E_UNEXPECTED ||
       hr == E_INVALIDARG, /* Win9x/WinMe/NT4/W2K/Vista/W2K8 */
       "Unexpected result : %08x\n", hr);
}