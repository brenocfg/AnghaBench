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
typedef  int /*<<< orphan*/  szString ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IEnumVARIANT ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int DISP_E_BADINDEX ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int IEnumVARIANT_Clone (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int IEnumVARIANT_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  IEnumVARIANT_Release (int /*<<< orphan*/ *) ; 
 int IEnumVARIANT_Reset (int /*<<< orphan*/ *) ; 
 int IEnumVARIANT_Skip (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  IID_IEnumVARIANT ; 
 int INSTALLSTATE_ADVERTISED ; 
 int INSTALLSTATE_DEFAULT ; 
 int IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int Installer_ProductState (int /*<<< orphan*/ *,int*) ; 
 int Installer_Products (int /*<<< orphan*/ **) ; 
 int MAX_PATH ; 
 int S_FALSE ; 
 int S_OK ; 
 int StringList_Count (int /*<<< orphan*/ *,int*) ; 
 int StringList_Item (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int StringList__NewEnum (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  VT_BSTR ; 
 int /*<<< orphan*/  V_BSTR (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcmpW (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  ok_w2 (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  szProductCode ; 

__attribute__((used)) static void test_Installer_Products(BOOL bProductInstalled)
{
    WCHAR szString[MAX_PATH];
    HRESULT hr;
    int idx;
    IUnknown *pUnk = NULL;
    IEnumVARIANT *pEnum = NULL;
    VARIANT var;
    ULONG celt;
    int iCount, iValue;
    IDispatch *pStringList = NULL;
    BOOL bProductFound = FALSE;

    /* Installer::Products */
    hr = Installer_Products(&pStringList);
    ok(hr == S_OK, "Installer_Products failed, hresult 0x%08x\n", hr);
    if (hr == S_OK)
    {
        /* StringList::_NewEnum */
        hr = StringList__NewEnum(pStringList, &pUnk);
        ok(hr == S_OK, "StringList_NewEnum failed, hresult 0x%08x\n", hr);
        if (hr == S_OK)
        {
            hr = IUnknown_QueryInterface(pUnk, &IID_IEnumVARIANT, (void **)&pEnum);
            ok (hr == S_OK, "IUnknown::QueryInterface returned 0x%08x\n", hr);
        }
        if (!pEnum)
            skip("IEnumVARIANT tests\n");

        /* StringList::Count */
        hr = StringList_Count(pStringList, &iCount);
        ok(hr == S_OK, "StringList_Count failed, hresult 0x%08x\n", hr);

        for (idx=0; idx<iCount; idx++)
        {
            /* StringList::Item */
            memset(szString, 0, sizeof(szString));
            hr = StringList_Item(pStringList, idx, szString);
            ok(hr == S_OK, "StringList_Item failed (idx %d, count %d), hresult 0x%08x\n", idx, iCount, hr);

            if (hr == S_OK)
            {
                /* Installer::ProductState */
                hr = Installer_ProductState(szString, &iValue);
                ok(hr == S_OK, "Installer_ProductState failed, hresult 0x%08x\n", hr);
                if (hr == S_OK)
                    ok(iValue == INSTALLSTATE_DEFAULT || iValue == INSTALLSTATE_ADVERTISED, "Installer_ProductState returned %d, expected %d or %d\n", iValue, INSTALLSTATE_DEFAULT, INSTALLSTATE_ADVERTISED);

                /* Not found our product code yet? Check */
                if (!bProductFound && !lstrcmpW(szString, szProductCode))
                    bProductFound = TRUE;

                /* IEnumVARIANT::Next */
                if (pEnum)
                {
                    hr = IEnumVARIANT_Next(pEnum, 1, &var, &celt);
                    ok(hr == S_OK, "IEnumVARIANT_Next failed (idx %d, count %d), hresult 0x%08x\n", idx, iCount, hr);
                    ok(celt == 1, "%d items were retrieved, expected 1\n", celt);
                    ok(V_VT(&var) == VT_BSTR, "IEnumVARIANT_Next returned variant of type %d, expected %d\n", V_VT(&var), VT_BSTR);
                    ok_w2("%s returned by StringList_Item does not match %s returned by IEnumVARIANT_Next\n", szString, V_BSTR(&var));
                    VariantClear(&var);
                }
            }
        }

        if (bProductInstalled)
        {
            ok(bProductInstalled == bProductFound, "Product expected to %s installed but product code was %s\n",
               bProductInstalled ? "be" : "not be",
               bProductFound ? "found" : "not found");
        }

        if (pEnum)
        {
            IEnumVARIANT *pEnum2 = NULL;

            if (0) /* Crashes on Windows XP */
            {
                /* IEnumVARIANT::Clone, NULL pointer */
                IEnumVARIANT_Clone(pEnum, NULL);
            }

            /* IEnumVARIANT::Clone */
            hr = IEnumVARIANT_Clone(pEnum, &pEnum2);
            ok(hr == S_OK, "IEnumVARIANT_Clone failed, hresult 0x%08x\n", hr);
            if (hr == S_OK)
            {
                /* IEnumVARIANT::Clone is supposed to save the position, but it actually just goes back to the beginning */

                /* IEnumVARIANT::Next of the clone */
                if (iCount)
                {
                    hr = IEnumVARIANT_Next(pEnum2, 1, &var, &celt);
                    ok(hr == S_OK, "IEnumVARIANT_Next failed, hresult 0x%08x\n", hr);
                    ok(celt == 1, "%d items were retrieved, expected 0\n", celt);
                    ok(V_VT(&var) == VT_BSTR, "IEnumVARIANT_Next returned variant of type %d, expected %d\n", V_VT(&var), VT_BSTR);
                    VariantClear(&var);
                }
                else
                    skip("IEnumVARIANT::Next of clone will not return success with 0 products\n");

                IEnumVARIANT_Release(pEnum2);
            }

            /* IEnumVARIANT::Skip should fail */
            hr = IEnumVARIANT_Skip(pEnum, 1);
            ok(hr == S_FALSE, "IEnumVARIANT_Skip failed, hresult 0x%08x\n", hr);

            /* IEnumVARIANT::Next, NULL variant pointer */
            hr = IEnumVARIANT_Next(pEnum, 1, NULL, &celt);
            ok(hr == S_FALSE, "IEnumVARIANT_Next failed, hresult 0x%08x\n", hr);
            ok(celt == 0, "%d items were retrieved, expected 0\n", celt);

            /* IEnumVARIANT::Next, should not return any more items */
            hr = IEnumVARIANT_Next(pEnum, 1, &var, &celt);
            ok(hr == S_FALSE, "IEnumVARIANT_Next failed, hresult 0x%08x\n", hr);
            ok(celt == 0, "%d items were retrieved, expected 0\n", celt);
            VariantClear(&var);

            /* IEnumVARIANT::Reset */
            hr = IEnumVARIANT_Reset(pEnum);
            ok(hr == S_OK, "IEnumVARIANT_Reset failed, hresult 0x%08x\n", hr);

            if (iCount)
            {
                /* IEnumVARIANT::Skip to the last product */
                hr = IEnumVARIANT_Skip(pEnum, iCount-1);
                ok(hr == S_OK, "IEnumVARIANT_Skip failed, hresult 0x%08x\n", hr);

                /* IEnumVARIANT::Next should match the very last retrieved value, also makes sure it works with
                 * NULL celt pointer. */
                hr = IEnumVARIANT_Next(pEnum, 1, &var, NULL);
                ok(hr == S_OK, "IEnumVARIANT_Next failed (idx %d, count %d), hresult 0x%08x\n", idx, iCount, hr);
                ok(V_VT(&var) == VT_BSTR, "IEnumVARIANT_Next returned variant of type %d, expected %d\n", V_VT(&var), VT_BSTR);
                ok_w2("%s returned by StringList_Item does not match %s returned by IEnumVARIANT_Next\n", szString, V_BSTR(&var));
                VariantClear(&var);
            }
            else
                skip("IEnumVARIANT::Skip impossible for 0 products\n");
        }

        /* StringList::Item using an invalid index */
        memset(szString, 0, sizeof(szString));
        hr = StringList_Item(pStringList, iCount, szString);
        ok(hr == DISP_E_BADINDEX, "StringList_Item for an invalid index did not return DISP_E_BADINDEX, hresult 0x%08x\n", hr);

        if (pEnum) IEnumVARIANT_Release(pEnum);
        if (pUnk) IUnknown_Release(pUnk);
        IDispatch_Release(pStringList);
    }
}