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
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOCSTR_EXECUTABLE ; 
 int /*<<< orphan*/  ASSOCSTR_FRIENDLYAPPNAME ; 
 int /*<<< orphan*/  ERROR_FILE_NOT_FOUND ; 
 int /*<<< orphan*/  ERROR_NOT_FOUND ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 scalar_t__ HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  HeapFree (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  dotHtml ; 
 int /*<<< orphan*/  expect (int,int) ; 
 int /*<<< orphan*/  expect_hr (scalar_t__,scalar_t__) ; 
 int lstrlenW (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  open ; 
 scalar_t__ pAssocQueryStringW (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_getstring_basic(void)
{
    HRESULT hr;
    WCHAR * friendlyName;
    WCHAR * executableName;
    DWORD len, len2, slen;

    if (!pAssocQueryStringW)
    {
        win_skip("AssocQueryStringW() is missing\n");
        return;
    }

    hr = pAssocQueryStringW(0, ASSOCSTR_EXECUTABLE, dotHtml, open, NULL, &len);
    expect_hr(S_FALSE, hr);
    if (hr != S_FALSE)
    {
        skip("failed to get initial len\n");
        return;
    }

    executableName = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                               len * sizeof(WCHAR));
    if (!executableName)
    {
        skip("failed to allocate memory\n");
        return;
    }

    len2 = len;
    hr = pAssocQueryStringW(0, ASSOCSTR_EXECUTABLE, dotHtml, open,
                           executableName, &len2);
    expect_hr(S_OK, hr);
    slen = lstrlenW(executableName) + 1;
    expect(len, len2);
    expect(len, slen);

    hr = pAssocQueryStringW(0, ASSOCSTR_FRIENDLYAPPNAME, dotHtml, open, NULL,
                           &len);
    ok(hr == S_FALSE ||
       hr == HRESULT_FROM_WIN32(ERROR_FILE_NOT_FOUND) /* Win9x/NT4 */ ||
       hr == HRESULT_FROM_WIN32(ERROR_NOT_FOUND), /* Win8 */
       "Unexpected result : %08x\n", hr);
    if (hr != S_FALSE)
    {
        HeapFree(GetProcessHeap(), 0, executableName);
        skip("failed to get initial len\n");
        return;
    }

    friendlyName = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY,
                               len * sizeof(WCHAR));
    if (!friendlyName)
    {
        HeapFree(GetProcessHeap(), 0, executableName);
        skip("failed to allocate memory\n");
        return;
    }

    len2 = len;
    hr = pAssocQueryStringW(0, ASSOCSTR_FRIENDLYAPPNAME, dotHtml, open,
                           friendlyName, &len2);
    expect_hr(S_OK, hr);
    slen = lstrlenW(friendlyName) + 1;
    expect(len, len2);
    expect(len, slen);

    HeapFree(GetProcessHeap(), 0, executableName);
    HeapFree(GetProcessHeap(), 0, friendlyName);
}