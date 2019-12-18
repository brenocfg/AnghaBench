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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  VARIANT ;
struct TYPE_3__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IHTMLDOMNode ;
typedef  int /*<<< orphan*/  IHTMLDOMChildrenCollection ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int HRESULT ;
typedef  int /*<<< orphan*/  EXCEPINFO ;
typedef  TYPE_1__ DISPPARAMS ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int DISP_E_UNKNOWNNAME ; 
 int IDispatchEx_GetDispID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int IDispatchEx_InvokeEx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int IHTMLDOMChildrenCollection_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IHTMLDOMNode_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  INVOKE_PROPERTYGET ; 
 int /*<<< orphan*/  LOCALE_NEUTRAL ; 
 int S_OK ; 
 int /*<<< orphan*/  SysAllocString (char const*) ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 scalar_t__ VT_DISPATCH ; 
 int /*<<< orphan*/ * V_DISPATCH (int /*<<< orphan*/ *) ; 
 int V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fdexNameCaseSensitive ; 
 int /*<<< orphan*/ * get_node_iface (int /*<<< orphan*/ *) ; 
 int get_node_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static void test_child_col_disp(IHTMLDOMChildrenCollection *col)
{
    IDispatchEx *dispex;
    IHTMLDOMNode *node;
    DISPPARAMS dp = {NULL, NULL, 0, 0};
    VARIANT var;
    EXCEPINFO ei;
    LONG type;
    DISPID id;
    BSTR bstr;
    HRESULT hres;

    static const WCHAR w0[] = {'0',0};
    static const WCHAR w100[] = {'1','0','0',0};

    hres = IHTMLDOMChildrenCollection_QueryInterface(col, &IID_IDispatchEx, (void**)&dispex);
    ok(hres == S_OK, "Could not get IDispatchEx: %08x\n", hres);

    bstr = SysAllocString(w0);
    hres = IDispatchEx_GetDispID(dispex, bstr, fdexNameCaseSensitive, &id);
    ok(hres == S_OK, "GetDispID failed: %08x\n", hres);
    SysFreeString(bstr);

    VariantInit(&var);
    hres = IDispatchEx_InvokeEx(dispex, id, LOCALE_NEUTRAL, INVOKE_PROPERTYGET, &dp, &var, &ei, NULL);
    ok(hres == S_OK, "InvokeEx failed: %08x\n", hres);
    ok(V_VT(&var) == VT_DISPATCH, "V_VT(var)=%d\n", V_VT(&var));
    ok(V_DISPATCH(&var) != NULL, "V_DISPATCH(var) == NULL\n");
    node = get_node_iface((IUnknown*)V_DISPATCH(&var));
    type = get_node_type((IUnknown*)node);
    ok(type == 3, "type=%d\n", type);
    IHTMLDOMNode_Release(node);
    VariantClear(&var);

    bstr = SysAllocString(w100);
    hres = IDispatchEx_GetDispID(dispex, bstr, fdexNameCaseSensitive, &id);
    ok(hres == DISP_E_UNKNOWNNAME, "GetDispID failed: %08x, expected DISP_E_UNKNOWNNAME\n", hres);
    SysFreeString(bstr);

    IDispatchEx_Release(dispex);
}