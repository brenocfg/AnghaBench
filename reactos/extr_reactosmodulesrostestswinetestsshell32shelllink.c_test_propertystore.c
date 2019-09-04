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
typedef  int /*<<< orphan*/  IShellLinkW ;
typedef  int /*<<< orphan*/  IShellLinkA ;
typedef  int /*<<< orphan*/  IPropertyStoreCache ;
typedef  int /*<<< orphan*/  IPropertyStore ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_ShellLink ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ E_NOINTERFACE ; 
 int /*<<< orphan*/  IID_IPropertyStore ; 
 int /*<<< orphan*/  IID_IPropertyStoreCache ; 
 int /*<<< orphan*/  IID_IShellLinkA ; 
 int /*<<< orphan*/  IID_IShellLinkW ; 
 scalar_t__ IPropertyStore_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IPropertyStore_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IShellLinkA_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellLinkA_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IShellLinkW_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IShellLinkW_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  win_skip (char*) ; 

__attribute__((used)) static void test_propertystore(void)
{
    IShellLinkA *linkA;
    IShellLinkW *linkW;
    IPropertyStore *ps;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER,
                         &IID_IShellLinkA, (void**)&linkA);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IShellLinkA_QueryInterface(linkA, &IID_IShellLinkW, (void**)&linkW);
    ok(hr == S_OK, "got 0x%08x\n", hr);

    hr = IShellLinkA_QueryInterface(linkA, &IID_IPropertyStore, (void**)&ps);
    if (hr == S_OK) {
        IPropertyStoreCache *pscache;

        IPropertyStore_Release(ps);

        hr = IShellLinkW_QueryInterface(linkW, &IID_IPropertyStore, (void**)&ps);
        ok(hr == S_OK, "got 0x%08x\n", hr);

        hr = IPropertyStore_QueryInterface(ps, &IID_IPropertyStoreCache, (void**)&pscache);
        ok(hr == E_NOINTERFACE, "got 0x%08x\n", hr);

        IPropertyStore_Release(ps);
    }
    else
        win_skip("IShellLink doesn't support IPropertyStore.\n");

    IShellLinkA_Release(linkA);
    IShellLinkW_Release(linkW);
}