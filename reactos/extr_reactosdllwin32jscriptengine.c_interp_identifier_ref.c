#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  global; } ;
typedef  TYPE_1__ script_ctx_t ;
struct TYPE_12__ {scalar_t__ type; } ;
typedef  TYPE_2__ exprval_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 scalar_t__ EXPRVAL_INVALID ; 
 scalar_t__ EXPRVAL_JSVAL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_OBJECT_EXPECTED ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  exprval_release (TYPE_2__*) ; 
 int /*<<< orphan*/  exprval_set_disp_ref (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exprval_set_exception (TYPE_2__*,int /*<<< orphan*/ ) ; 
 unsigned int fdexNameEnsure ; 
 int /*<<< orphan*/  identifier_eval (TYPE_1__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  jsdisp_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_push_exprval (TYPE_1__*,TYPE_2__*) ; 
 int /*<<< orphan*/  to_disp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT interp_identifier_ref(script_ctx_t *ctx, BSTR identifier, unsigned flags)
{
    exprval_t exprval;
    HRESULT hres;

    hres = identifier_eval(ctx, identifier, &exprval);
    if(FAILED(hres))
        return hres;

    if(exprval.type == EXPRVAL_INVALID && (flags & fdexNameEnsure)) {
        DISPID id;

        hres = jsdisp_get_id(ctx->global, identifier, fdexNameEnsure, &id);
        if(FAILED(hres))
            return hres;

        exprval_set_disp_ref(&exprval, to_disp(ctx->global), id);
    }

    if(exprval.type == EXPRVAL_JSVAL || exprval.type == EXPRVAL_INVALID) {
        WARN("invalid ref\n");
        exprval_release(&exprval);
        exprval_set_exception(&exprval, JS_E_OBJECT_EXPECTED);
    }

    return stack_push_exprval(ctx, &exprval);
}