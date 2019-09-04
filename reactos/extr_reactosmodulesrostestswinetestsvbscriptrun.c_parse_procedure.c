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
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  IActiveScriptParseProcedure2 ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ IActiveScriptParseProcedure2_ParseProcedureText (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ **) ; 
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int SCRIPTPROC_HOSTMANAGESSOURCE ; 
 int SCRIPTPROC_IMPLICIT_PARENTS ; 
 int SCRIPTPROC_IMPLICIT_THIS ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  a2bstr (char const*) ; 
 int /*<<< orphan*/  emptyW ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 

__attribute__((used)) static IDispatchEx *parse_procedure(IActiveScriptParseProcedure2 *parse_proc, const char *src)
{
    IDispatchEx *dispex;
    IDispatch *disp;
    BSTR str;
    HRESULT hres;

    static const WCHAR delimiterW[] = {'\"',0};

    str = a2bstr(src);
    hres = IActiveScriptParseProcedure2_ParseProcedureText(parse_proc, str, NULL, emptyW, NULL, NULL, delimiterW, 0, 0,
            SCRIPTPROC_HOSTMANAGESSOURCE|SCRIPTPROC_IMPLICIT_THIS|SCRIPTPROC_IMPLICIT_PARENTS, &disp);
    SysFreeString(str);
    ok(hres == S_OK, "ParseProcedureText failed: %08x\n", hres);
    ok(disp != NULL, "disp = NULL\n");

    hres = IDispatch_QueryInterface(disp, &IID_IDispatchEx, (void**)&dispex);
    IDispatch_Release(disp);
    ok(hres == S_OK, "Could not get IDispatchEx iface: %08x\n", hres);

    return dispex;
}