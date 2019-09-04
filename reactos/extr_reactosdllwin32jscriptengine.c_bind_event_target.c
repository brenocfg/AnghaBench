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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_5__ {int /*<<< orphan*/  IDispatchEx_iface; } ;
typedef  TYPE_1__ jsdisp_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; int /*<<< orphan*/  event_target; } ;
typedef  TYPE_2__ function_code_t ;
typedef  int /*<<< orphan*/  exprval_t ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  IBindEventHandler ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IBindEventHandler_BindHandler (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindEventHandler_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDispatch_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBindEventHandler ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_jsval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprval_to_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  identifier_eval (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT bind_event_target(script_ctx_t *ctx, function_code_t *func, jsdisp_t *func_obj)
{
    IBindEventHandler *target;
    exprval_t exprval;
    IDispatch *disp;
    jsval_t v;
    HRESULT hres;

    hres = identifier_eval(ctx, func->event_target, &exprval);
    if(FAILED(hres))
        return hres;

    hres = exprval_to_value(ctx, &exprval, &v);
    if(FAILED(hres))
        return hres;

    if(!is_object_instance(v)) {
        FIXME("Can't bind to %s\n", debugstr_jsval(v));
        jsval_release(v);
    }

    disp = get_object(v);
    hres = IDispatch_QueryInterface(disp, &IID_IBindEventHandler, (void**)&target);
    if(SUCCEEDED(hres)) {
        hres = IBindEventHandler_BindHandler(target, func->name, (IDispatch*)&func_obj->IDispatchEx_iface);
        IBindEventHandler_Release(target);
        if(FAILED(hres))
            WARN("BindEvent failed: %08x\n", hres);
    }else {
        FIXME("No IBindEventHandler, not yet supported binding\n");
    }

    IDispatch_Release(disp);
    return hres;
}