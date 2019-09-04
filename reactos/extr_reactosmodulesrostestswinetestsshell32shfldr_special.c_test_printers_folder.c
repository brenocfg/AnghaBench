#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ uType; int /*<<< orphan*/ * pOleStr; } ;
struct TYPE_5__ {scalar_t__ fmt; TYPE_1__ str; } ;
typedef  TYPE_2__ SHELLDETAILS ;
typedef  int SHCOLSTATEF ;
typedef  int /*<<< orphan*/ * LPITEMIDLIST ;
typedef  int /*<<< orphan*/  IShellFolder2 ;
typedef  int /*<<< orphan*/  IPersistFolder2 ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_Printers ; 
 int /*<<< orphan*/  CSIDL_PRINTERS ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  CoInitialize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CoUninitialize () ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  IID_IPersistFolder2 ; 
 int /*<<< orphan*/  IID_IShellFolder2 ; 
 int /*<<< orphan*/  ILFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ILIsEqual (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistFolder2_GetCurFolder (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IPersistFolder2_Initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IPersistFolder2_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IShellFolder2_GetDefaultColumnState (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  IShellFolder2_GetDetailsOf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  IShellFolder2_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellFolder2_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ LVCFMT_LEFT ; 
 int SHCOLSTATE_ONBYDEFAULT ; 
 int SHCOLSTATE_TYPE_INT ; 
 int SHCOLSTATE_TYPE_STR ; 
 scalar_t__ SHELL_OsIsUnicode () ; 
 int /*<<< orphan*/  SHFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SHGetSpecialFolderLocation (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ STRRET_WSTR ; 
 int /*<<< orphan*/  S_FALSE ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_printers_folder(void)
{
    IShellFolder2 *folder;
    IPersistFolder2 *pf;
    SHELLDETAILS details;
    SHCOLSTATEF state;
    LPITEMIDLIST pidl1, pidl2;
    HRESULT hr;
    INT i;

    CoInitialize( NULL );

    hr = CoCreateInstance(&CLSID_Printers, NULL, CLSCTX_INPROC_SERVER, &IID_IShellFolder2, (void**)&folder);
    if (hr != S_OK)
    {
        win_skip("Failed to created IShellFolder2 for Printers folder\n");
        CoUninitialize();
        return;
    }

if (0)
{
    /* crashes on XP */
    IShellFolder2_GetDetailsOf(folder, NULL, 0, NULL);
    IShellFolder2_GetDefaultColumnState(folder, 0, NULL);
    IPersistFolder2_GetCurFolder(pf, NULL);
}

    /* 5 columns defined */
    hr = IShellFolder2_GetDetailsOf(folder, NULL, 6, &details);
    ok(hr == E_NOTIMPL, "got 0x%08x\n", hr);

    hr = IShellFolder2_GetDefaultColumnState(folder, 6, &state);
    ok(broken(hr == E_NOTIMPL) || hr == E_INVALIDARG /* Win7 */, "got 0x%08x\n", hr);

    details.str.pOleStr = NULL;
    hr = IShellFolder2_GetDetailsOf(folder, NULL, 0, &details);
    ok(hr == S_OK || broken(hr == E_NOTIMPL) /* W2K */, "got 0x%08x\n", hr);
    if (SHELL_OsIsUnicode()) SHFree(details.str.pOleStr);

    /* test every column if method is implemented */
    if (hr == S_OK)
    {
        ok(details.str.uType == STRRET_WSTR, "got %d\n", details.str.uType);

        for(i = 0; i < 6; i++)
        {
            hr = IShellFolder2_GetDetailsOf(folder, NULL, i, &details);
            ok(hr == S_OK, "got 0x%08x\n", hr);

            /* all columns are left-aligned */
            ok(details.fmt == LVCFMT_LEFT, "got 0x%x\n", details.fmt);
            /* can't be on w9x at this point, IShellFolder2 unsupported there,
               check present for running Wine with w9x setup */
            if (SHELL_OsIsUnicode()) SHFree(details.str.pOleStr);

            hr = IShellFolder2_GetDefaultColumnState(folder, i, &state);
            ok(hr == S_OK, "got 0x%08x\n", hr);
            /* all columns are string except document count */
            if (i == 1)
                ok(state == (SHCOLSTATE_TYPE_INT | SHCOLSTATE_ONBYDEFAULT), "got 0x%x\n", state);
            else
                ok(state == (SHCOLSTATE_TYPE_STR | SHCOLSTATE_ONBYDEFAULT), "got 0x%x\n", state);
        }
    }

    /* default pidl */
    hr = IShellFolder2_QueryInterface(folder, &IID_IPersistFolder2, (void**)&pf);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    /* not initialized */
    pidl1 = (void*)0xdeadbeef;
    hr = IPersistFolder2_GetCurFolder(pf, &pidl1);
    ok(hr == S_FALSE, "got 0x%08x\n", hr);
    ok(pidl1 == NULL, "got %p\n", pidl1);

    hr = SHGetSpecialFolderLocation(NULL, CSIDL_PRINTERS, &pidl2);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IPersistFolder2_Initialize(pf, pidl2);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IPersistFolder2_GetCurFolder(pf, &pidl1);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    ok(ILIsEqual(pidl1, pidl2), "expected same PIDL\n");
    IPersistFolder2_Release(pf);

    ILFree(pidl1);
    ILFree(pidl2);
    IShellFolder2_Release(folder);

    CoUninitialize();
}