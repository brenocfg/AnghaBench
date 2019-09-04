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
typedef  int /*<<< orphan*/  IUnknown ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_NewMenu ; 
 scalar_t__ CoCreateInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IContextMenu ; 
 int /*<<< orphan*/  IID_IContextMenu2 ; 
 int /*<<< orphan*/  IID_IContextMenu3 ; 
 int /*<<< orphan*/  IID_IObjectWithSite ; 
 int /*<<< orphan*/  IID_IShellExtInit ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__) ; 
 int /*<<< orphan*/  skip (char*) ; 

__attribute__((used)) static void test_newmenu(void)
{
    IUnknown *unk, *unk2;
    HRESULT hr;

    hr = CoCreateInstance(&CLSID_NewMenu, NULL, CLSCTX_INPROC_SERVER, &IID_IUnknown, (void **)&unk);
    ok(hr == S_OK, "Failed to create NewMenu object, hr %#x.\n", hr);
    if (hr != S_OK)
    {
        skip("NewMenu is not supported.\n");
        return;
    }

    hr = IUnknown_QueryInterface(unk, &IID_IShellExtInit, (void **)&unk2);
    ok(hr == S_OK, "Failed to get IShellExtInit, hr %#x.\n", hr);
    IUnknown_Release(unk2);

    hr = IUnknown_QueryInterface(unk, &IID_IContextMenu, (void **)&unk2);
    ok(hr == S_OK, "Failed to get IContextMenu, hr %#x.\n", hr);
    IUnknown_Release(unk2);

    hr = IUnknown_QueryInterface(unk, &IID_IContextMenu2, (void **)&unk2);
    ok(hr == S_OK, "Failed to get IContextMenu2, hr %#x.\n", hr);
    IUnknown_Release(unk2);

    hr = IUnknown_QueryInterface(unk, &IID_IContextMenu3, (void **)&unk2);
    ok(hr == S_OK, "Failed to get IContextMenu3, hr %#x.\n", hr);
    IUnknown_Release(unk2);

    hr = IUnknown_QueryInterface(unk, &IID_IObjectWithSite, (void **)&unk2);
    ok(hr == S_OK, "Failed to get IObjectWithSite, hr %#x.\n", hr);
    IUnknown_Release(unk2);

    IUnknown_Release(unk);
}