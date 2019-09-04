#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_4__* expression; } ;
typedef  TYPE_1__ unary_expression_t ;
typedef  int /*<<< orphan*/  jsop_t ;
struct TYPE_7__ {int /*<<< orphan*/  identifier; } ;
typedef  TYPE_2__ identifier_expression_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
struct TYPE_8__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ EXPR_IDENT ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_typeof ; 
 int /*<<< orphan*/  OP_typeofid ; 
 int /*<<< orphan*/  OP_typeofident ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_memberid_expression (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_memberid_expr (scalar_t__) ; 
 scalar_t__ push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_bstr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_typeof_expression(compiler_ctx_t *ctx, unary_expression_t *expr)
{
    jsop_t op;
    HRESULT hres;

    if(is_memberid_expr(expr->expression->type)) {
        if(expr->expression->type == EXPR_IDENT)
            return push_instr_bstr(ctx, OP_typeofident, ((identifier_expression_t*)expr->expression)->identifier);

        op = OP_typeofid;
        hres = compile_memberid_expression(ctx, expr->expression, 0);
    }else {
        op = OP_typeof;
        hres = compile_expression(ctx, expr->expression, TRUE);
    }
    if(FAILED(hres))
        return hres;

    return push_instr(ctx, op) ? S_OK : E_OUTOFMEMORY;
}