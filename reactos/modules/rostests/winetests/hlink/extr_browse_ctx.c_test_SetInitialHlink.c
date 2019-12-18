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
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IHlinkBrowseContext ;
typedef  int /*<<< orphan*/  IHlink ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ CO_E_ALREADYINITIALIZED ; 
 int /*<<< orphan*/  CoTaskMemFree (char*) ; 
 scalar_t__ CreateBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ CreateItemMoniker (char*,char*,int /*<<< orphan*/ **) ; 
 scalar_t__ E_FAIL ; 
 int /*<<< orphan*/  HLID_CURRENT ; 
 int /*<<< orphan*/  HLID_NEXT ; 
 int /*<<< orphan*/  HLID_PREVIOUS ; 
 int /*<<< orphan*/  HLINKGETREF_DEFAULT ; 
 scalar_t__ HlinkCreateBrowseContext (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHlinkBrowseContext_GetHlink (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IHlinkBrowseContext_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IHlinkBrowseContext_SetInitialHlink (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ IHlink_GetMonikerReference (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IHlink_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IHlinkBrowseContext ; 
 scalar_t__ IMoniker_GetDisplayName (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  lstrcmpW (char*,char*) ; 
 int /*<<< orphan*/  ok (int,char*,scalar_t__,...) ; 
 int /*<<< orphan*/  wine_dbgstr_w (char*) ; 

__attribute__((used)) static void test_SetInitialHlink(void)
{
    IHlinkBrowseContext *bc;
    IHlink *found_hlink;
    IMoniker *dummy, *found_moniker;
    IBindCtx *bindctx;
    WCHAR one[] = {'1',0};
    WCHAR five[] = {'5',0};
    WCHAR *found_name, *exp_name;
    HRESULT hres;

    hres = CreateBindCtx(0, &bindctx);
    ok(hres == S_OK, "CreateBindCtx failed: 0x%08x\n", hres);

    hres = CreateItemMoniker(one, five, &dummy);
    ok(hres == S_OK, "CreateItemMoniker failed: 0x%08x\n", hres);

    hres = IMoniker_GetDisplayName(dummy, bindctx, NULL, &exp_name);
    ok(hres == S_OK, "GetDisplayName failed: 0x%08x\n", hres);

    hres = HlinkCreateBrowseContext(NULL, &IID_IHlinkBrowseContext, (void**)&bc);
    ok(hres == S_OK, "HlinkCreateBrowseContext failed: 0x%08x\n", hres);

    hres = IHlinkBrowseContext_SetInitialHlink(bc, dummy, one, NULL);
    ok(hres == S_OK, "SetInitialHlink failed: 0x%08x\n", hres);

    hres = IHlinkBrowseContext_SetInitialHlink(bc, dummy, one, NULL);
    ok(hres == CO_E_ALREADYINITIALIZED, "got 0x%08x\n", hres);

    hres = IHlinkBrowseContext_SetInitialHlink(bc, dummy, five, NULL);
    ok(hres == CO_E_ALREADYINITIALIZED, "got 0x%08x\n", hres);

    /* there's only one */
    hres = IHlinkBrowseContext_GetHlink(bc, HLID_PREVIOUS, &found_hlink);
    ok(hres == E_FAIL, "got 0x%08x\n", hres);

    hres = IHlinkBrowseContext_GetHlink(bc, HLID_NEXT, &found_hlink);
    ok(hres == E_FAIL, "got 0x%08x\n", hres);

    hres = IHlinkBrowseContext_GetHlink(bc, HLID_CURRENT, &found_hlink);
    ok(hres == S_OK, "GetHlink failed: 0x%08x\n", hres);

    hres = IHlink_GetMonikerReference(found_hlink, HLINKGETREF_DEFAULT, &found_moniker, NULL);
    ok(hres == S_OK, "GetMonikerReference failed: 0x%08x\n", hres);

    hres = IMoniker_GetDisplayName(found_moniker, bindctx, NULL, &found_name);
    ok(hres == S_OK, "GetDisplayName failed: 0x%08x\n", hres);
    ok(!lstrcmpW(found_name, exp_name), "Found display name should have been %s, was: %s\n", wine_dbgstr_w(exp_name), wine_dbgstr_w(found_name));

    CoTaskMemFree(exp_name);
    CoTaskMemFree(found_name);

    IBindCtx_Release(bindctx);
    IMoniker_Release(found_moniker);
    IHlink_Release(found_hlink);
    IHlinkBrowseContext_Release(bc);
    IMoniker_Release(dummy);
}