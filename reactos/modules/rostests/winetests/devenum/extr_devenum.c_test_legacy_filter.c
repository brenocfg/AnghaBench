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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  IPropertyBag ;
typedef  int /*<<< orphan*/  IParseDisplayName ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IFilterMapper ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CHARS_IN_GUID ; 
 int /*<<< orphan*/  CLSCTX_INPROC ; 
 int /*<<< orphan*/  CLSID_CDeviceMoniker ; 
 int /*<<< orphan*/  CLSID_FilterMapper2 ; 
 int /*<<< orphan*/  CLSID_LegacyAmFilterCategory ; 
 int /*<<< orphan*/  CLSID_TestFilter ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IFilterMapper_RegisterFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  IFilterMapper_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IFilterMapper_UnregisterFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IID_IFilterMapper ; 
 int /*<<< orphan*/  IID_IParseDisplayName ; 
 int /*<<< orphan*/  IID_IPropertyBag ; 
 scalar_t__ IMoniker_BindToStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IParseDisplayName_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPropertyBag_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPropertyBag_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  StringFromGUID2 (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ VFW_E_BAD_KEY ; 
 char* V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  backslashW ; 
 int /*<<< orphan*/ * check_display_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  clsidW ; 
 int /*<<< orphan*/  cmW ; 
 int /*<<< orphan*/  deviceW ; 
 int find_moniker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  friendly_name ; 
 int /*<<< orphan*/  lstrcatW (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lstrcmpW (char*,char*) ; 
 int /*<<< orphan*/  lstrcpyW (char*,int /*<<< orphan*/ ) ; 
 int lstrlenW (char*) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_legacy_filter(void)
{
    static const WCHAR nameW[] = {'t','e','s','t',0};
    IParseDisplayName *parser;
    IPropertyBag *prop_bag;
    IFilterMapper *mapper;
    IMoniker *mon;
    WCHAR buffer[200];
    VARIANT var;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_CDeviceMoniker, NULL, CLSCTX_INPROC, &IID_IParseDisplayName, (void **)&parser);
    ok(hr == S_OK, "Failed to create ParseDisplayName: %#x\n", hr);

    hr = CoCreateInstance(&CLSID_FilterMapper2, NULL, CLSCTX_INPROC, &IID_IFilterMapper, (void **)&mapper);
    ok(hr == S_OK, "Failed to create FilterMapper: %#x\n", hr);

    hr = IFilterMapper_RegisterFilter(mapper, CLSID_TestFilter, nameW, 0xdeadbeef);
    if (hr == VFW_E_BAD_KEY)
    {
        win_skip("not enough permissions to register filters\n");
        goto end;
    }
    ok(hr == S_OK, "RegisterFilter failed: %#x\n", hr);

    lstrcpyW(buffer, deviceW);
    lstrcatW(buffer, cmW);
    StringFromGUID2(&CLSID_LegacyAmFilterCategory, buffer + lstrlenW(buffer), CHARS_IN_GUID);
    lstrcatW(buffer, backslashW);
    StringFromGUID2(&CLSID_TestFilter, buffer + lstrlenW(buffer), CHARS_IN_GUID);

    mon = check_display_name(parser, buffer);
    ok(find_moniker(&CLSID_LegacyAmFilterCategory, mon), "filter should be registered\n");

    hr = IMoniker_BindToStorage(mon, NULL, NULL, &IID_IPropertyBag, (void **)&prop_bag);
    ok(hr == S_OK, "BindToStorage failed: %#x\n", hr);

    VariantInit(&var);
    hr = IPropertyBag_Read(prop_bag, friendly_name, &var, NULL);
    ok(hr == S_OK, "Read failed: %#x\n", hr);

    StringFromGUID2(&CLSID_TestFilter, buffer, CHARS_IN_GUID);
    ok(!lstrcmpW(buffer, V_BSTR(&var)), "expected %s, got %s\n",
        wine_dbgstr_w(buffer), wine_dbgstr_w(V_BSTR(&var)));

    VariantClear(&var);
    hr = IPropertyBag_Read(prop_bag, clsidW, &var, NULL);
    ok(hr == S_OK, "Read failed: %#x\n", hr);
    ok(!lstrcmpW(buffer, V_BSTR(&var)), "expected %s, got %s\n",
        wine_dbgstr_w(buffer), wine_dbgstr_w(V_BSTR(&var)));

    VariantClear(&var);
    IPropertyBag_Release(prop_bag);

    hr = IFilterMapper_UnregisterFilter(mapper, CLSID_TestFilter);
    ok(hr == S_OK, "UnregisterFilter failed: %#x\n", hr);

    ok(!find_moniker(&CLSID_LegacyAmFilterCategory, mon), "filter should not be registered\n");
    IMoniker_Release(mon);

end:
    IFilterMapper_Release(mapper);
    IParseDisplayName_Release(parser);
}