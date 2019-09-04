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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  void* LPVOID ;
typedef  int /*<<< orphan*/  IPropertyBag ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IEnumMoniker ;
typedef  int /*<<< orphan*/  ICreateDevEnum ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC ; 
 scalar_t__ CLSIDFromString (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLSID_ActiveMovieCategories ; 
 int /*<<< orphan*/  CLSID_CDeviceMoniker ; 
 int /*<<< orphan*/  CLSID_SystemDeviceEnum ; 
 int /*<<< orphan*/  CLSID_VideoCompressorCategory ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_INVALIDARG ; 
 scalar_t__ E_POINTER ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ICreateDevEnum_CreateClassEnumerator (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ICreateDevEnum_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumMoniker_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_ICreateDevEnum ; 
 int /*<<< orphan*/  IID_IPropertyBag ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IMoniker_BindToObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ IMoniker_BindToStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IMoniker_GetClassID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IPropertyBag_Read (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPropertyBag_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ VT_BSTR ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clsidW ; 
 int /*<<< orphan*/  fcc_handlerW ; 
 int /*<<< orphan*/  friendly_name ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mrleW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  trace (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wine_dbgstr_guid (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wine_dbgstr_w (int /*<<< orphan*/ ) ; 
 int winetest_debug ; 

__attribute__((used)) static void test_devenum(IBindCtx *bind_ctx)
{
    IEnumMoniker *enum_cat, *enum_moniker;
    ICreateDevEnum* create_devenum;
    IPropertyBag *prop_bag;
    IMoniker *moniker;
    BOOL have_mrle = FALSE;
    GUID cat_guid, clsid;
    VARIANT var;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_SystemDeviceEnum, NULL, CLSCTX_INPROC,
                           &IID_ICreateDevEnum, (LPVOID*)&create_devenum);
    ok(hr == S_OK, "Failed to create devenum: %#x\n", hr);

    hr = ICreateDevEnum_CreateClassEnumerator(create_devenum, &CLSID_ActiveMovieCategories, &enum_cat, 0);
    ok(hr == S_OK, "Failed to enum categories: %#x\n", hr);

    while (IEnumMoniker_Next(enum_cat, 1, &moniker, NULL) == S_OK)
    {
        hr = IMoniker_BindToStorage(moniker, bind_ctx, NULL, &IID_IPropertyBag, (void **)&prop_bag);
        ok(hr == S_OK, "IMoniker_BindToStorage failed: %#x\n", hr);

        VariantInit(&var);
        hr = IPropertyBag_Read(prop_bag, friendly_name, &var, NULL);
        ok(hr == S_OK, "Failed to read FriendlyName: %#x\n", hr);

        if (winetest_debug > 1)
            trace("%s:\n", wine_dbgstr_w(V_BSTR(&var)));

        VariantClear(&var);
        hr = IPropertyBag_Read(prop_bag, clsidW, &var, NULL);
        ok(hr == S_OK, "Failed to read CLSID: %#x\n", hr);

        hr = CLSIDFromString(V_BSTR(&var), &cat_guid);
        ok(hr == S_OK, "got %#x\n", hr);

        IPropertyBag_Release(prop_bag);
        IMoniker_Release(moniker);

        hr = ICreateDevEnum_CreateClassEnumerator(create_devenum, &cat_guid, &enum_moniker, 0);
        ok(SUCCEEDED(hr), "Failed to enum devices: %#x\n", hr);

        if (hr == S_OK)
        {
            while (IEnumMoniker_Next(enum_moniker, 1, &moniker, NULL) == S_OK)
            {
                hr = IMoniker_GetClassID(moniker, NULL);
                ok(hr == E_INVALIDARG, "IMoniker_GetClassID should failed %x\n", hr);

                hr = IMoniker_GetClassID(moniker, &clsid);
                ok(hr == S_OK, "IMoniker_GetClassID failed with error %x\n", hr);
                ok(IsEqualGUID(&clsid, &CLSID_CDeviceMoniker),
                   "Expected CLSID_CDeviceMoniker got %s\n", wine_dbgstr_guid(&clsid));

                VariantInit(&var);
                hr = IMoniker_BindToStorage(moniker, bind_ctx, NULL, &IID_IPropertyBag, (LPVOID*)&prop_bag);
                ok(hr == S_OK, "IMoniker_BindToStorage failed with error %x\n", hr);

                hr = IPropertyBag_Read(prop_bag, friendly_name, &var, NULL);
                ok(hr == S_OK, "IPropertyBag_Read failed: %#x\n", hr);

                if (winetest_debug > 1)
                    trace("  %s\n", wine_dbgstr_w(V_BSTR(&var)));

                if (IsEqualGUID(&CLSID_VideoCompressorCategory, &cat_guid)) {
                    /* Test well known compressor to ensure that we really enumerate codecs */
                    hr = IPropertyBag_Read(prop_bag, fcc_handlerW, &var, NULL);
                    if (SUCCEEDED(hr)) {
                        ok(V_VT(&var) == VT_BSTR, "V_VT(var) = %d\n", V_VT(&var));
                        if(!lstrcmpW(V_BSTR(&var), mrleW))
                            have_mrle = TRUE;
                        VariantClear(&var);
                    }
                }

                hr = IMoniker_BindToObject(moniker, bind_ctx, NULL, &IID_IUnknown, NULL);
                ok(hr == E_POINTER, "got %#x\n", hr);

                IPropertyBag_Release(prop_bag);
                IMoniker_Release(moniker);
            }
            IEnumMoniker_Release(enum_moniker);
        }
    }

    ICreateDevEnum_Release(create_devenum);

    /* 64-bit windows are missing mrle codec */
    if(sizeof(void*) == 4)
        ok(have_mrle, "mrle codec not found\n");
}