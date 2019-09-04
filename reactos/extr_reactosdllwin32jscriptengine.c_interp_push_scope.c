#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* call_ctx; } ;
typedef  TYPE_2__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_6__ {int /*<<< orphan*/  scope; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scope_push (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_pop (TYPE_2__*) ; 
 int /*<<< orphan*/  to_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_object (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT interp_push_scope(script_ctx_t *ctx)
{
    IDispatch *disp;
    jsval_t v;
    HRESULT hres;

    TRACE("\n");

    v = stack_pop(ctx);
    hres = to_object(ctx, v, &disp);
    jsval_release(v);
    if(FAILED(hres))
        return hres;

    hres = scope_push(ctx->call_ctx->scope, to_jsdisp(disp), disp, &ctx->call_ctx->scope);
    IDispatch_Release(disp);
    return hres;
}