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
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  dispex_prop_t ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ DISP_E_MEMBERNOTFOUND ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int FALSE ; 
 scalar_t__ IDispatchEx_DeleteMemberByDispID (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 scalar_t__ S_OK ; 
 scalar_t__ delete_prop (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/ * get_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 

HRESULT disp_delete(IDispatch *disp, DISPID id, BOOL *ret)
{
    IDispatchEx *dispex;
    jsdisp_t *jsdisp;
    HRESULT hres;

    jsdisp = iface_to_jsdisp(disp);
    if(jsdisp) {
        dispex_prop_t *prop;

        prop = get_prop(jsdisp, id);
        if(prop)
            hres = delete_prop(prop, ret);
        else
            hres = DISP_E_MEMBERNOTFOUND;

        jsdisp_release(jsdisp);
        return hres;
    }

    hres = IDispatch_QueryInterface(disp, &IID_IDispatchEx, (void**)&dispex);
    if(FAILED(hres)) {
        *ret = FALSE;
        return S_OK;
    }

    hres = IDispatchEx_DeleteMemberByDispID(dispex, id);
    IDispatchEx_Release(dispex);
    if(FAILED(hres))
        return hres;

    *ret = hres == S_OK;
    return S_OK;
}