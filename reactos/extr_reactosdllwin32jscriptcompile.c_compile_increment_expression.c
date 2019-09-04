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
struct TYPE_5__ {TYPE_2__* expression; } ;
typedef  TYPE_1__ unary_expression_t ;
typedef  int /*<<< orphan*/  jsop_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  type; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_ILLEGAL_ASSIGN ; 
 int /*<<< orphan*/  OP_throw_ref ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_memberid_expression (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fdexNameEnsure ; 
 int /*<<< orphan*/  is_memberid_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  push_instr_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_increment_expression(compiler_ctx_t *ctx, unary_expression_t *expr, jsop_t op, int n)
{
    HRESULT hres;

    if(!is_memberid_expr(expr->expression->type)) {
        hres = compile_expression(ctx, expr->expression, TRUE);
        if(FAILED(hres))
            return hres;

        return push_instr_uint(ctx, OP_throw_ref, JS_E_ILLEGAL_ASSIGN);
    }

    hres = compile_memberid_expression(ctx, expr->expression, fdexNameEnsure);
    if(FAILED(hres))
        return hres;

    return push_instr_int(ctx, op, n);
}