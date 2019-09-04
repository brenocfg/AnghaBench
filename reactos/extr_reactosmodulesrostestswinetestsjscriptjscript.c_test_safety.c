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
typedef  int HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int E_FAIL ; 
 int E_POINTER ; 
 scalar_t__ FAILED (int) ; 
 int /*<<< orphan*/  IID_IActiveScript ; 
 int /*<<< orphan*/  IID_IActiveScriptParse ; 
 int /*<<< orphan*/  IID_IObjectSafety ; 
 int /*<<< orphan*/  IID_NULL ; 
 int INTERFACESAFE_FOR_UNTRUSTED_CALLER ; 
 int INTERFACESAFE_FOR_UNTRUSTED_DATA ; 
 int INTERFACE_USES_DISPEX ; 
 int INTERFACE_USES_SECURITY_MANAGER ; 
 int IObjectSafety_GetInterfaceSafetyOptions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*,int*) ; 
 int /*<<< orphan*/  IObjectSafety_Release (int /*<<< orphan*/ *) ; 
 int IObjectSafety_SetInterfaceSafetyOptions (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 
 int IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int S_OK ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 

__attribute__((used)) static void test_safety(IUnknown *unk)
{
    IObjectSafety *safety;
    DWORD supported, enabled;
    HRESULT hres;

    hres = IUnknown_QueryInterface(unk, &IID_IObjectSafety, (void**)&safety);
    ok(hres == S_OK, "Could not get IObjectSafety: %08x\n", hres);
    if(FAILED(hres))
        return;

    hres = IObjectSafety_GetInterfaceSafetyOptions(safety, &IID_NULL, &supported, NULL);
    ok(hres == E_POINTER, "GetInterfaceSafetyOptions failed: %08x, expected E_POINTER\n", hres);
    hres = IObjectSafety_GetInterfaceSafetyOptions(safety, &IID_NULL, NULL, &enabled);
    ok(hres == E_POINTER, "GetInterfaceSafetyOptions failed: %08x, expected E_POINTER\n", hres);

    supported = enabled = 0xdeadbeef;
    hres = IObjectSafety_GetInterfaceSafetyOptions(safety, &IID_NULL, &supported, &enabled);
    ok(hres == S_OK, "GetInterfaceSafetyOptions failed: %08x\n", hres);
    ok(supported == (INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER),
       "supported=%x\n", supported);
    ok(enabled == INTERFACE_USES_DISPEX, "enabled=%x\n", enabled);

    supported = enabled = 0xdeadbeef;
    hres = IObjectSafety_GetInterfaceSafetyOptions(safety, &IID_IActiveScript, &supported, &enabled);
    ok(hres == S_OK, "GetInterfaceSafetyOptions failed: %08x\n", hres);
    ok(supported == (INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER),
       "supported=%x\n", supported);
    ok(enabled == INTERFACE_USES_DISPEX, "enabled=%x\n", enabled);

    supported = enabled = 0xdeadbeef;
    hres = IObjectSafety_GetInterfaceSafetyOptions(safety, &IID_IActiveScriptParse, &supported, &enabled);
    ok(hres == S_OK, "GetInterfaceSafetyOptions failed: %08x\n", hres);
    ok(supported == (INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER),
       "supported=%x\n", supported);
    ok(enabled == INTERFACE_USES_DISPEX, "enabled=%x\n", enabled);

    hres = IObjectSafety_SetInterfaceSafetyOptions(safety, &IID_IActiveScriptParse,
            INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER
                |INTERFACESAFE_FOR_UNTRUSTED_CALLER,
            INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER);
    ok(hres == E_FAIL, "SetInterfaceSafetyOptions failed: %08x, expected E_FAIL\n", hres);

    hres = IObjectSafety_SetInterfaceSafetyOptions(safety, &IID_IActiveScriptParse,
            INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER,
            INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER);
    ok(hres == S_OK, "SetInterfaceSafetyOptions failed: %08x\n", hres);

    supported = enabled = 0xdeadbeef;
    hres = IObjectSafety_GetInterfaceSafetyOptions(safety, &IID_IActiveScriptParse, &supported, &enabled);
    ok(hres == S_OK, "GetInterfaceSafetyOptions failed: %08x\n", hres);
    ok(supported == (INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER),
       "supported=%x\n", supported);
    ok(enabled == (INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER),
       "enabled=%x\n", enabled);

    hres = IObjectSafety_SetInterfaceSafetyOptions(safety, &IID_IActiveScriptParse, INTERFACESAFE_FOR_UNTRUSTED_DATA, 0);
    ok(hres == S_OK, "SetInterfaceSafetyOptions failed: %08x\n", hres);

    supported = enabled = 0xdeadbeef;
    hres = IObjectSafety_GetInterfaceSafetyOptions(safety, &IID_IActiveScriptParse, &supported, &enabled);
    ok(hres == S_OK, "GetInterfaceSafetyOptions failed: %08x\n", hres);
    ok(supported == (INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER),
       "supported=%x\n", supported);
    ok(enabled == (INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER), "enabled=%x\n", enabled);

    hres = IObjectSafety_SetInterfaceSafetyOptions(safety, &IID_IActiveScriptParse,
            INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER, 0);
    ok(hres == S_OK, "SetInterfaceSafetyOptions failed: %08x\n", hres);

    supported = enabled = 0xdeadbeef;
    hres = IObjectSafety_GetInterfaceSafetyOptions(safety, &IID_IActiveScriptParse, &supported, &enabled);
    ok(hres == S_OK, "GetInterfaceSafetyOptions failed: %08x\n", hres);
    ok(supported == (INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER),
       "supported=%x\n", supported);
    ok(enabled == INTERFACE_USES_DISPEX, "enabled=%x\n", enabled);

    hres = IObjectSafety_SetInterfaceSafetyOptions(safety, &IID_IActiveScriptParse,
            INTERFACE_USES_DISPEX, 0);
    ok(hres == S_OK, "SetInterfaceSafetyOptions failed: %08x\n", hres);

    supported = enabled = 0xdeadbeef;
    hres = IObjectSafety_GetInterfaceSafetyOptions(safety, &IID_IActiveScriptParse, &supported, &enabled);
    ok(hres == S_OK, "GetInterfaceSafetyOptions failed: %08x\n", hres);
    ok(supported == (INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER),
       "supported=%x\n", supported);
    ok(enabled == INTERFACE_USES_DISPEX, "enabled=%x\n", enabled);

    IObjectSafety_Release(safety);
}