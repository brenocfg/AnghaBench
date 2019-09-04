#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ jsop_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
struct TYPE_7__ {TYPE_3__* argument_list; TYPE_4__* expression; } ;
typedef  TYPE_1__ call_expression_t ;
struct TYPE_8__ {TYPE_4__* expression2; TYPE_4__* expression1; } ;
typedef  TYPE_2__ binary_expression_t ;
struct TYPE_9__ {TYPE_4__* expr; struct TYPE_9__* next; } ;
typedef  TYPE_3__ argument_t ;
struct TYPE_10__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ EXPR_CALL ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  FIXME (char*,scalar_t__) ; 
 unsigned int JS_E_ILLEGAL_ASSIGN ; 
 scalar_t__ OP_LAST ; 
 scalar_t__ OP_assign ; 
 int /*<<< orphan*/  OP_assign_call ; 
 scalar_t__ OP_refval ; 
 int /*<<< orphan*/  OP_throw_ref ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  compile_memberid_expression (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdexNameEnsure ; 
 scalar_t__ is_memberid_expr (scalar_t__) ; 
 int /*<<< orphan*/  push_instr (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  push_instr_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static HRESULT compile_assign_expression(compiler_ctx_t *ctx, binary_expression_t *expr, jsop_t op)
{
    BOOL use_throw_path = FALSE;
    unsigned arg_cnt = 0;
    HRESULT hres;

    if(expr->expression1->type == EXPR_CALL) {
        call_expression_t *call_expr = (call_expression_t*)expr->expression1;
        argument_t *arg;

        if(op != OP_LAST) {
            FIXME("op %d not supported on parametrized assign expressions\n", op);
            return E_NOTIMPL;
        }

        if(is_memberid_expr(call_expr->expression->type) && call_expr->argument_list) {
            hres = compile_memberid_expression(ctx, call_expr->expression, fdexNameEnsure);
            if(FAILED(hres))
                return hres;

            for(arg = call_expr->argument_list; arg; arg = arg->next) {
                hres = compile_expression(ctx, arg->expr, TRUE);
                if(FAILED(hres))
                    return hres;
                arg_cnt++;
            }
        }else {
            use_throw_path = TRUE;
        }
    }else if(is_memberid_expr(expr->expression1->type)) {
        hres = compile_memberid_expression(ctx, expr->expression1, fdexNameEnsure);
        if(FAILED(hres))
            return hres;
    }else {
        use_throw_path = TRUE;
    }

    if(use_throw_path) {
        /* Illegal assignment: evaluate and throw */
        hres = compile_expression(ctx, expr->expression1, TRUE);
        if(FAILED(hres))
            return hres;

        hres = compile_expression(ctx, expr->expression2, TRUE);
        if(FAILED(hres))
            return hres;

        if(op != OP_LAST && !push_instr(ctx, op))
            return E_OUTOFMEMORY;

        return push_instr_uint(ctx, OP_throw_ref, JS_E_ILLEGAL_ASSIGN);
    }

    if(op != OP_LAST && !push_instr(ctx, OP_refval))
        return E_OUTOFMEMORY;

    hres = compile_expression(ctx, expr->expression2, TRUE);
    if(FAILED(hres))
        return hres;

    if(op != OP_LAST && !push_instr(ctx, op))
        return E_OUTOFMEMORY;

    if(arg_cnt)
        return push_instr_uint(ctx, OP_assign_call, arg_cnt);

    if(!push_instr(ctx, OP_assign))
        return E_OUTOFMEMORY;

    return S_OK;
}