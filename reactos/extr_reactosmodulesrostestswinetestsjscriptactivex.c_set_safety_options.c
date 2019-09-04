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
typedef  int /*<<< orphan*/  IObjectSafety ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  IID_IActiveScriptParse ; 
 int /*<<< orphan*/  IID_IObjectSafety ; 
 int INTERFACESAFE_FOR_UNTRUSTED_DATA ; 
 int INTERFACE_USES_DISPEX ; 
 int INTERFACE_USES_SECURITY_MANAGER ; 
 scalar_t__ IObjectSafety_GetInterfaceSafetyOptions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IObjectSafety_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IObjectSafety_SetInterfaceSafetyOptions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 scalar_t__ IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int,...) ; 

__attribute__((used)) static void set_safety_options(IUnknown *unk, BOOL use_sec_mgr)
{
    IObjectSafety *safety;
    DWORD supported, enabled, options_all, options_set;
    HRESULT hres;

    hres = IUnknown_QueryInterface(unk, &IID_IObjectSafety, (void**)&safety);
    ok(hres == S_OK, "Could not get IObjectSafety: %08x\n", hres);
    if(FAILED(hres))
        return;

    options_all = INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER;
    if(use_sec_mgr)
        options_set = options_all;
    else
        options_set = INTERFACE_USES_DISPEX;

    hres = IObjectSafety_SetInterfaceSafetyOptions(safety, &IID_IActiveScriptParse, options_all, options_set);
    ok(hres == S_OK, "SetInterfaceSafetyOptions failed: %08x\n", hres);

    supported = enabled = 0xdeadbeef;
    hres = IObjectSafety_GetInterfaceSafetyOptions(safety, &IID_IActiveScriptParse, &supported, &enabled);
    ok(hres == S_OK, "GetInterfaceSafetyOptions failed: %08x\n", hres);
    ok(supported == options_all, "supported=%x, expected %x\n", supported, options_all);
    ok(enabled == options_set, "enabled=%x, expected %x\n", enabled, options_set);

    IObjectSafety_Release(safety);
}