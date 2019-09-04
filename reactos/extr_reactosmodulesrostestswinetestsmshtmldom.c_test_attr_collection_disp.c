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
struct TYPE_3__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  IHTMLDOMAttribute ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  EXCEPINFO ;
typedef  TYPE_1__ DISPPARAMS ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IDispatchEx_GetDispID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IDispatchEx_InvokeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLDOMAttribute_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  IID_IHTMLDOMAttribute ; 
 int /*<<< orphan*/  INVOKE_PROPERTYGET ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 scalar_t__ VT_DISPATCH ; 
 int /*<<< orphan*/ * V_DISPATCH (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a2bstr (char*) ; 
 int /*<<< orphan*/  fdexNameCaseSensitive ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int /*<<< orphan*/  test_attr_node_name (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void test_attr_collection_disp(IDispatch *disp)
{
    IDispatchEx *dispex;
    IHTMLDOMAttribute *attr;
    DISPPARAMS dp = {NULL, NULL, 0, 0};
    VARIANT var;
    EXCEPINFO ei;
    DISPID id;
    BSTR bstr;
    HRESULT hres;

    hres = IDispatch_QueryInterface(disp, &IID_IDispatchEx, (void**)&dispex);
    ok(hres == S_OK, "QueryInterface failed: %08x\n", hres);

    bstr = a2bstr("0");
    hres = IDispatchEx_GetDispID(dispex, bstr, fdexNameCaseSensitive, &id);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);
    SysFreeString(bstr);

    VariantInit(&var);
    hres = IDispatchEx_InvokeEx(dispex, id, LOCALE_NEUTRAL, INVOKE_PROPERTYGET, &dp, &var, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&var) == VT_DISPATCH, "V_VT(var)=%d\n", V_VT(&var));
    ok(V_DISPATCH(&var) != NULL, "V_DISPATCH(var) == NULL\n");
    VariantClear(&var);

    bstr = a2bstr("attr1");
    hres = IDispatchEx_GetDispID(dispex, bstr, fdexNameCaseSensitive, &id);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);
    SysFreeString(bstr);

    VariantInit(&var);
    hres = IDispatchEx_InvokeEx(dispex, id, LOCALE_NEUTRAL, INVOKE_PROPERTYGET, &dp, &var, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&var) == VT_DISPATCH, "V_VT(var)=%d\n", V_VT(&var));
    ok(V_DISPATCH(&var) != NULL, "V_DISPATCH(var) == NULL\n");
    hres = IDispatch_QueryInterface(V_DISPATCH(&var), &IID_IHTMLDOMAttribute, (void**)&attr);
    ok(hres == S_OK, "QueryInterface failed: %08x\n", hres);

    test_attr_node_name(attr, "attr1");

    IHTMLDOMAttribute_Release(attr);
    VariantClear(&var);

    IDispatchEx_Release(dispex);
}