#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsop_t ;
struct TYPE_8__ {int /*<<< orphan*/  code_off; } ;
typedef  TYPE_1__ compiler_ctx_t ;
struct TYPE_9__ {int /*<<< orphan*/  expression2; int /*<<< orphan*/  expression1; } ;
typedef  TYPE_2__ binary_expression_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compile_expression (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int push_instr (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_arg_uint (TYPE_1__*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_logical_expression(compiler_ctx_t *ctx, binary_expression_t *expr, jsop_t op)
{
    unsigned instr;
    HRESULT hres;

    hres = compile_expression(ctx, expr->expression1, TRUE);
    if(FAILED(hres))
        return hres;

    instr = push_instr(ctx, op);
    if(!instr)
        return E_OUTOFMEMORY;

    hres = compile_expression(ctx, expr->expression2, TRUE);
    if(FAILED(hres))
        return hres;

    set_arg_uint(ctx, instr, ctx->code_off);
    return S_OK;
}