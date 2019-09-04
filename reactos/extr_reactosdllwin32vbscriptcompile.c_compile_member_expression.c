#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  identifier; int /*<<< orphan*/ * obj_expr; int /*<<< orphan*/  args; } ;
typedef  TYPE_1__ member_expression_t ;
typedef  int /*<<< orphan*/  expression_t ;
typedef  int /*<<< orphan*/  compile_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_icall ; 
 int /*<<< orphan*/  OP_icallv ; 
 int /*<<< orphan*/  OP_mcall ; 
 int /*<<< orphan*/  OP_mcallv ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compile_args (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lookup_const_decls (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_bstr_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static HRESULT compile_member_expression(compile_ctx_t *ctx, member_expression_t *expr, BOOL ret_val)
{
    unsigned arg_cnt = 0;
    HRESULT hres;

    if(ret_val && !expr->args) {
        expression_t *const_expr;

        const_expr = lookup_const_decls(ctx, expr->identifier, TRUE);
        if(const_expr)
            return compile_expression(ctx, const_expr);
    }

    hres = compile_args(ctx, expr->args, &arg_cnt);
    if(FAILED(hres))
        return hres;

    if(expr->obj_expr) {
        hres = compile_expression(ctx, expr->obj_expr);
        if(FAILED(hres))
            return hres;

        hres = push_instr_bstr_uint(ctx, ret_val ? OP_mcall : OP_mcallv, expr->identifier, arg_cnt);
    }else {
        hres = push_instr_bstr_uint(ctx, ret_val ? OP_icall : OP_icallv, expr->identifier, arg_cnt);
    }

    return hres;
}