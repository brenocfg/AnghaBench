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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  disp_delete_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT interp_delete(script_ctx_t *ctx)
{
    jsval_t objv, namev;
    IDispatch *obj;
    jsstr_t *name;
    BOOL ret;
    HRESULT hres;

    TRACE("\n");

    namev = stack_pop(ctx);
    objv = stack_pop(ctx);

    hres = to_object(ctx, objv, &obj);
    jsval_release(objv);
    if(FAILED(hres)) {
        jsval_release(namev);
        return hres;
    }

    hres = to_string(ctx, namev, &name);
    jsval_release(namev);
    if(FAILED(hres)) {
        IDispatch_Release(obj);
        return hres;
    }

    hres = disp_delete_name(ctx, obj, name, &ret);
    IDispatch_Release(obj);
    jsstr_release(name);
    if(FAILED(hres))
        return hres;

    return stack_push(ctx, jsval_bool(ret));
}