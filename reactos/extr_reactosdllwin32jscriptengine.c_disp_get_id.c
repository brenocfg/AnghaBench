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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;
typedef  scalar_t__ DISPID ;
typedef  scalar_t__ BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IDispatchEx_GetDispID (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_GetIDsOfNames (int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*,int,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  IID_NULL ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 scalar_t__ SysAllocString (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  SysFreeString (scalar_t__) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int fdexNameCaseSensitive ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_get_id (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int,scalar_t__*) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  make_grfdex (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT disp_get_id(script_ctx_t *ctx, IDispatch *disp, const WCHAR *name, BSTR name_bstr, DWORD flags, DISPID *id)
{
    IDispatchEx *dispex;
    jsdisp_t *jsdisp;
    BSTR bstr;
    HRESULT hres;

    jsdisp = iface_to_jsdisp(disp);
    if(jsdisp) {
        hres = jsdisp_get_id(jsdisp, name, flags, id);
        jsdisp_release(jsdisp);
        return hres;
    }

    if(name_bstr) {
        bstr = name_bstr;
    }else {
        bstr = SysAllocString(name);
        if(!bstr)
            return E_OUTOFMEMORY;
    }

    *id = 0;
    hres = IDispatch_QueryInterface(disp, &IID_IDispatchEx, (void**)&dispex);
    if(SUCCEEDED(hres)) {
        hres = IDispatchEx_GetDispID(dispex, bstr, make_grfdex(ctx, flags|fdexNameCaseSensitive), id);
        IDispatchEx_Release(dispex);
    }else {
        TRACE("using IDispatch\n");
        hres = IDispatch_GetIDsOfNames(disp, &IID_NULL, &bstr, 1, 0, id);
    }

    if(name_bstr != bstr)
        SysFreeString(bstr);
    return hres;
}