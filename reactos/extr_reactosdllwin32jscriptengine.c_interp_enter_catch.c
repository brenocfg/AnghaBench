#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* call_ctx; } ;
typedef  TYPE_2__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_7__ {int /*<<< orphan*/  scope; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  create_dispex (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_op_bstr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_propput_name (int /*<<< orphan*/ *,int /*<<< orphan*/  const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scope_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_pop (TYPE_2__*) ; 
 int /*<<< orphan*/  to_disp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_enter_catch(script_ctx_t *ctx)
{
    const BSTR ident = get_op_bstr(ctx, 0);
    jsdisp_t *scope_obj;
    jsval_t v;
    HRESULT hres;

    hres = create_dispex(ctx, NULL, NULL, &scope_obj);
    if(FAILED(hres))
        return hres;

    v = stack_pop(ctx);
    hres = jsdisp_propput_name(scope_obj, ident, v);
    jsval_release(v);
    if(SUCCEEDED(hres))
        hres = scope_push(ctx->call_ctx->scope, scope_obj, to_disp(scope_obj), &ctx->call_ctx->scope);
    jsdisp_release(scope_obj);
    return hres;
}