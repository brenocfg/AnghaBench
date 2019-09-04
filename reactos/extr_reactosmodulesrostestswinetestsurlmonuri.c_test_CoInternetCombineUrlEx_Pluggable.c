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
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/ * BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_CALLED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CombineUrl ; 
 int /*<<< orphan*/  IUri_GetAbsoluteUri (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SET_EXPECT (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ *) ; 
 int URL_DONT_SIMPLIFY ; 
 int URL_DONT_UNESCAPE_EXTRA_INFO ; 
 int URL_FILE_USE_PATHURL ; 
 int /*<<< orphan*/  combine_baseW ; 
 int /*<<< orphan*/  combine_relativeW ; 
 int /*<<< orphan*/ * combine_resultW ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  pCoInternetCombineUrlEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pCreateUri (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_CoInternetCombineUrlEx_Pluggable(void) {
    HRESULT hr;
    IUri *base = NULL;

    hr = pCreateUri(combine_baseW, 0, 0, &base);
    ok(SUCCEEDED(hr), "Error: CreateUri returned 0x%08x.\n", hr);
    if(SUCCEEDED(hr)) {
        IUri *result = NULL;

        SET_EXPECT(CombineUrl);

        hr = pCoInternetCombineUrlEx(base, combine_relativeW, URL_DONT_SIMPLIFY|URL_FILE_USE_PATHURL|URL_DONT_UNESCAPE_EXTRA_INFO,
                                     &result, 0);
        ok(hr == S_OK, "Error: CoInternetCombineUrlEx returned 0x%08x, expected 0x%08x.\n", hr, S_OK);

        CHECK_CALLED(CombineUrl);

        if(SUCCEEDED(hr)) {
            BSTR received = NULL;
            hr = IUri_GetAbsoluteUri(result, &received);
            ok(hr == S_OK, "Error: Expected S_OK, but got 0x%08x instead.\n", hr);
            if(SUCCEEDED(hr)) {
                ok(!lstrcmpW(combine_resultW, received), "Error: Expected %s, but got %s.\n",
                    wine_dbgstr_w(combine_resultW), wine_dbgstr_w(received));
            }
            SysFreeString(received);
        }
        if(result) IUri_Release(result);
    }
    if(base) IUri_Release(base);
}