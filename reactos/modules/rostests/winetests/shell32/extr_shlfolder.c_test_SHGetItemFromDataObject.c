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
typedef  int UINT ;
typedef  int SHCONTF ;
typedef  int /*<<< orphan*/  LPITEMIDLIST ;
typedef  int /*<<< orphan*/  LPCITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellView ;
typedef  int /*<<< orphan*/  IShellItem ;
typedef  int /*<<< orphan*/  IShellFolder ;
typedef  int /*<<< orphan*/  IEnumIDList ;
typedef  int /*<<< orphan*/  IDataObject ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DOGIF_DEFAULT ; 
 int /*<<< orphan*/  DOGIF_NO_HDROP ; 
 int /*<<< orphan*/  DOGIF_NO_URL ; 
 int /*<<< orphan*/  DOGIF_ONLY_IF_ONE ; 
 int /*<<< orphan*/  DOGIF_TRAVERSE_LINK ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_INVALIDARG ; 
 int /*<<< orphan*/  IDataObject_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IEnumIDList_Next (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumIDList_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDataObject ; 
 int /*<<< orphan*/  IID_IShellItem ; 
 int /*<<< orphan*/  IID_IShellView ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ ) ; 
 scalar_t__ IShellFolder_CreateViewObject (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ IShellFolder_EnumObjects (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ **) ; 
 scalar_t__ IShellFolder_GetUIObjectOf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellFolder_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellItem_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellView_Release (int /*<<< orphan*/ *) ; 
 int SHCONTF_FOLDERS ; 
 int SHCONTF_INCLUDEHIDDEN ; 
 int SHCONTF_NONFOLDERS ; 
 int /*<<< orphan*/  SHGetDesktopFolder (int /*<<< orphan*/ **) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 scalar_t__ pSHGetItemFromDataObject (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  skip (char*) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_SHGetItemFromDataObject(void)
{
    IShellFolder *psfdesktop;
    IShellItem *psi;
    IShellView *psv;
    HRESULT hres;

    if(!pSHGetItemFromDataObject)
    {
        win_skip("No SHGetItemFromDataObject.\n");
        return;
    }

    if(0)
    {
        /* Crashes under win7 */
        pSHGetItemFromDataObject(NULL, 0, &IID_IShellItem, NULL);
    }

    hres = pSHGetItemFromDataObject(NULL, 0, &IID_IShellItem, (void**)&psv);
    ok(hres == E_INVALIDARG, "got 0x%08x\n", hres);

    SHGetDesktopFolder(&psfdesktop);

    hres = IShellFolder_CreateViewObject(psfdesktop, NULL, &IID_IShellView, (void**)&psv);
    ok(hres == S_OK, "got 0x%08x\n", hres);
    if(SUCCEEDED(hres))
    {
        IEnumIDList *peidl;
        IDataObject *pdo;
        SHCONTF enum_flags;

        enum_flags = SHCONTF_NONFOLDERS | SHCONTF_FOLDERS | SHCONTF_INCLUDEHIDDEN;
        hres = IShellFolder_EnumObjects(psfdesktop, NULL, enum_flags, &peidl);
        ok(hres == S_OK, "got 0x%08x\n", hres);
        if(SUCCEEDED(hres))
        {
            LPITEMIDLIST apidl[5];
            UINT count = 0, i;

            for(count = 0; count < 5; count++)
                if(IEnumIDList_Next(peidl, 1, &apidl[count], NULL) != S_OK)
                    break;

            if(count)
            {
                hres = IShellFolder_GetUIObjectOf(psfdesktop, NULL, 1, (LPCITEMIDLIST*)apidl,
                                                  &IID_IDataObject, NULL, (void**)&pdo);
                ok(hres == S_OK, "got 0x%08x\n", hres);
                if(SUCCEEDED(hres))
                {
                    hres = pSHGetItemFromDataObject(pdo, DOGIF_DEFAULT, &IID_IShellItem, (void**)&psi);
                    ok(hres == S_OK, "got 0x%08x\n", hres);
                    if(SUCCEEDED(hres)) IShellItem_Release(psi);
                    hres = pSHGetItemFromDataObject(pdo, DOGIF_TRAVERSE_LINK, &IID_IShellItem, (void**)&psi);
                    ok(hres == S_OK, "got 0x%08x\n", hres);
                    if(SUCCEEDED(hres)) IShellItem_Release(psi);
                    hres = pSHGetItemFromDataObject(pdo, DOGIF_NO_HDROP, &IID_IShellItem, (void**)&psi);
                    ok(hres == S_OK, "got 0x%08x\n", hres);
                    if(SUCCEEDED(hres)) IShellItem_Release(psi);
                    hres = pSHGetItemFromDataObject(pdo, DOGIF_NO_URL, &IID_IShellItem, (void**)&psi);
                    ok(hres == S_OK, "got 0x%08x\n", hres);
                    if(SUCCEEDED(hres)) IShellItem_Release(psi);
                    hres = pSHGetItemFromDataObject(pdo, DOGIF_ONLY_IF_ONE, &IID_IShellItem, (void**)&psi);
                    ok(hres == S_OK, "got 0x%08x\n", hres);
                    if(SUCCEEDED(hres)) IShellItem_Release(psi);

                    IDataObject_Release(pdo);
                }
            }
            else
                skip("No file(s) found - skipping single-file test.\n");

            if(count > 1)
            {
                hres = IShellFolder_GetUIObjectOf(psfdesktop, NULL, count, (LPCITEMIDLIST*)apidl,
                                                  &IID_IDataObject, NULL, (void**)&pdo);
                ok(hres == S_OK, "got 0x%08x\n", hres);
                if(SUCCEEDED(hres))
                {
                    hres = pSHGetItemFromDataObject(pdo, DOGIF_DEFAULT, &IID_IShellItem, (void**)&psi);
                    ok(hres == S_OK, "got 0x%08x\n", hres);
                    if(SUCCEEDED(hres)) IShellItem_Release(psi);
                    hres = pSHGetItemFromDataObject(pdo, DOGIF_TRAVERSE_LINK, &IID_IShellItem, (void**)&psi);
                    ok(hres == S_OK, "got 0x%08x\n", hres);
                    if(SUCCEEDED(hres)) IShellItem_Release(psi);
                    hres = pSHGetItemFromDataObject(pdo, DOGIF_NO_HDROP, &IID_IShellItem, (void**)&psi);
                    ok(hres == S_OK, "got 0x%08x\n", hres);
                    if(SUCCEEDED(hres)) IShellItem_Release(psi);
                    hres = pSHGetItemFromDataObject(pdo, DOGIF_NO_URL, &IID_IShellItem, (void**)&psi);
                    ok(hres == S_OK, "got 0x%08x\n", hres);
                    if(SUCCEEDED(hres)) IShellItem_Release(psi);
                    hres = pSHGetItemFromDataObject(pdo, DOGIF_ONLY_IF_ONE, &IID_IShellItem, (void**)&psi);
                    ok(hres == E_FAIL, "got 0x%08x\n", hres);
                    if(SUCCEEDED(hres)) IShellItem_Release(psi);
                    IDataObject_Release(pdo);
                }
            }
            else
                skip("zero or one file found - skipping multi-file test.\n");

            for(i = 0; i < count; i++)
                ILFree(apidl[i]);

            IEnumIDList_Release(peidl);
        }

        IShellView_Release(psv);
    }

    IShellFolder_Release(psfdesktop);
}