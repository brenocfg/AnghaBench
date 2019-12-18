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
typedef  int /*<<< orphan*/  ei ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_3__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  EXCEPINFO ;
typedef  TYPE_1__ DISPPARAMS ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_PROPERTYGET ; 
 scalar_t__ IDispatchEx_GetDispID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IDispatchEx_InvokeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 scalar_t__ VT_DISPATCH ; 
 int /*<<< orphan*/ * V_DISPATCH (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  a2bstr (char*) ; 
 int /*<<< orphan*/  fdexNameCaseSensitive ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_script_dispatch(IDispatchEx *dispex)
{
    DISPPARAMS dp = {NULL,NULL,0,0};
    EXCEPINFO ei;
    BSTR str;
    DISPID id;
    VARIANT v;
    HRESULT hres;

    str = a2bstr("ActiveXObject");
    hres = IDispatchEx_GetDispID(dispex, str, fdexNameCaseSensitive, &id);
    SysFreeString(str);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);

    str = a2bstr("Math");
    hres = IDispatchEx_GetDispID(dispex, str, fdexNameCaseSensitive, &id);
    SysFreeString(str);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);

    memset(&ei, 0, sizeof(ei));
    hres = IDispatchEx_InvokeEx(dispex, id, 0, DISPATCH_PROPERTYGET, &dp, &v, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&v) == VT_DISPATCH, "V_VT(v) = %d\n", V_VT(&v));
    ok(V_DISPATCH(&v) != NULL, "V_DISPATCH(v) = NULL\n");
    VariantClear(&v);

    str = a2bstr("String");
    hres = IDispatchEx_GetDispID(dispex, str, fdexNameCaseSensitive, &id);
    SysFreeString(str);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);

    memset(&ei, 0, sizeof(ei));
    hres = IDispatchEx_InvokeEx(dispex, id, 0, DISPATCH_PROPERTYGET, &dp, &v, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&v) == VT_DISPATCH, "V_VT(v) = %d\n", V_VT(&v));
    ok(V_DISPATCH(&v) != NULL, "V_DISPATCH(v) = NULL\n");
    VariantClear(&v);
}