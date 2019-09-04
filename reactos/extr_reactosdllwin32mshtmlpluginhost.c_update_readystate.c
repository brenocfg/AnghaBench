#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/ * member_1; int /*<<< orphan*/ * member_0; } ;
struct TYPE_5__ {int /*<<< orphan*/  plugin_unk; } ;
typedef  TYPE_1__ PluginHost ;
typedef  int /*<<< orphan*/  IDispatchEx ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ DISPPARAMS ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_PROPERTYGET ; 
 int /*<<< orphan*/  DISPID_READYSTATE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IDispatchEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_Invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int /*<<< orphan*/  IID_IDispatchEx ; 
 int /*<<< orphan*/  IID_NULL ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void update_readystate(PluginHost *host)
{
    DISPPARAMS params = {NULL,NULL,0,0};
    IDispatchEx *dispex;
    IDispatch *disp;
    ULONG err = 0;
    VARIANT v;
    HRESULT hres;

    hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IDispatchEx, (void**)&dispex);
    if(SUCCEEDED(hres)) {
        FIXME("Use IDispatchEx\n");
        IDispatchEx_Release(dispex);
    }

    hres = IUnknown_QueryInterface(host->plugin_unk, &IID_IDispatch, (void**)&disp);
    if(FAILED(hres))
        return;

    hres = IDispatch_Invoke(disp, DISPID_READYSTATE, &IID_NULL, 0, DISPATCH_PROPERTYGET, &params, &v, NULL, &err);
    IDispatch_Release(disp);
    if(SUCCEEDED(hres)) {
        /* FIXME: make plugin readystate affect document readystate */
        TRACE("readystate = %s\n", debugstr_variant(&v));
        VariantClear(&v);
    }
}