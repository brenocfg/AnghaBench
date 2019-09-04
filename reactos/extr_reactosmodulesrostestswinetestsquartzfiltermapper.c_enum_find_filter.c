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
typedef  float WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  ULONG ;
typedef  int /*<<< orphan*/  LPVOID ;
typedef  int /*<<< orphan*/  IPropertyBag ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IEnumMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ IEnumMoniker_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IPropertyBag ; 
 int /*<<< orphan*/  IMoniker_BindToStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPropertyBag_Read (int /*<<< orphan*/ *,float const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPropertyBag_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ S_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ ,float const*) ; 
 int /*<<< orphan*/  ok (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static BOOL enum_find_filter(const WCHAR *wszFilterName, IEnumMoniker *pEnum)
{
    IMoniker *pMoniker = NULL;
    BOOL found = FALSE;
    ULONG nb;
    HRESULT hr;
    static const WCHAR wszFriendlyName[] = {'F','r','i','e','n','d','l','y','N','a','m','e',0};

    while(!found && IEnumMoniker_Next(pEnum, 1, &pMoniker, &nb) == S_OK)
    {
        IPropertyBag * pPropBagCat = NULL;
        VARIANT var;

        VariantInit(&var);

        hr = IMoniker_BindToStorage(pMoniker, NULL, NULL, &IID_IPropertyBag, (LPVOID*)&pPropBagCat);
        ok(SUCCEEDED(hr), "IMoniker_BindToStorage failed with %x\n", hr);

        hr = IPropertyBag_Read(pPropBagCat, wszFriendlyName, &var, NULL);
        ok(SUCCEEDED(hr), "IPropertyBag_Read failed with %x\n", hr);

        if (!lstrcmpW(V_BSTR(&var), wszFilterName))
            found = TRUE;

        IPropertyBag_Release(pPropBagCat);
        IMoniker_Release(pMoniker);
        VariantClear(&var);
    }

    return found;
}