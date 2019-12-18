#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_3__ {int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  IActiveScript ;
typedef  int HRESULT ;
typedef  TYPE_1__ DISPPARAMS ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_METHOD ; 
 int /*<<< orphan*/  DISPATCH_PROPERTYGET ; 
 int E_UNEXPECTED ; 
 int /*<<< orphan*/  IActiveScript_Release (int /*<<< orphan*/ *) ; 
 int IActiveScript_SetScriptState (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int IDispatchEx_GetDispID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IDispatchEx_InvokeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int IDispatch_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  SCRIPTSTATE_UNINITIALIZED ; 
 int S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int VT_DISPATCH ; 
 int VT_I4 ; 
 int /*<<< orphan*/  V_DISPATCH (int /*<<< orphan*/ *) ; 
 int V_I4 (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a2bstr (char*) ; 
 scalar_t__ broken (int) ; 
 int /*<<< orphan*/  ok (int,char*,int) ; 
 int parse_script_expr (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void test_invokeex(void)
{
    DISPID func_id, prop_id;
    DISPPARAMS dp = {NULL};
    IActiveScript *script;
    IDispatchEx *dispex;
    VARIANT v;
    BSTR str;
    HRESULT hres;

    hres = parse_script_expr("var o = {func: function() {return 3;}, prop: 6}; o", &v, &script);
    ok(hres == S_OK, "parse_script_expr failed: %08x\n", hres);
    ok(V_VT(&v) == VT_DISPATCH, "V_VT(v) = %d\n", V_VT(&v));

    hres = IDispatch_QueryInterface(V_DISPATCH(&v), &IID_IDispatchEx, (void**)&dispex);
    ok(hres == S_OK, "Could not get IDispatchEx iface: %08x\n", hres);
    VariantClear(&v);

    str = a2bstr("func");
    hres = IDispatchEx_GetDispID(dispex, str, 0, &func_id);
    SysFreeString(str);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);

    str = a2bstr("prop");
    hres = IDispatchEx_GetDispID(dispex, str, 0, &prop_id);
    SysFreeString(str);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);

    hres = IDispatchEx_InvokeEx(dispex, func_id, 0, DISPATCH_METHOD, &dp, &v, NULL, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&v) == VT_I4, "V_VT(v) = %d\n", V_VT(&v));
    ok(V_I4(&v) == 3, "V_I4(v) = %d\n", V_I4(&v));

    hres = IDispatchEx_InvokeEx(dispex, prop_id, 0, DISPATCH_PROPERTYGET, &dp, &v, NULL, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&v) == VT_I4, "V_VT(v) = %d\n", V_VT(&v));
    ok(V_I4(&v) == 6, "V_I4(v) = %d\n", V_I4(&v));

    hres = IActiveScript_SetScriptState(script, SCRIPTSTATE_UNINITIALIZED);
    ok(hres == S_OK, "SetScriptState(SCRIPTSTATE_STARTED) failed: %08x\n", hres);

    str = a2bstr("func");
    hres = IDispatchEx_GetDispID(dispex, str, 0, &func_id);
    SysFreeString(str);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);

    hres = IDispatchEx_InvokeEx(dispex, func_id, 0, DISPATCH_METHOD, &dp, &v, NULL, NULL);
    ok(hres == E_UNEXPECTED || broken(hres == 0x800a1393), "InvokeEx failed: %08x\n", hres);

    hres = IDispatchEx_InvokeEx(dispex, prop_id, 0, DISPATCH_PROPERTYGET, &dp, &v, NULL, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&v) == VT_I4, "V_VT(v) = %d\n", V_VT(&v));
    ok(V_I4(&v) == 6, "V_I4(v) = %d\n", V_I4(&v));

    IDispatchEx_Release(dispex);
    IActiveScript_Release(script);
}