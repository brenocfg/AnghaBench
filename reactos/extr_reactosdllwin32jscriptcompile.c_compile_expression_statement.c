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
struct TYPE_7__ {int /*<<< orphan*/  expr; } ;
typedef  TYPE_1__ expression_statement_t ;
struct TYPE_8__ {int /*<<< orphan*/  from_eval; } ;
typedef  TYPE_2__ compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_setret ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  compile_expression (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ push_instr (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_expression_statement(compiler_ctx_t *ctx, expression_statement_t *stat)
{
    HRESULT hres;

    hres = compile_expression(ctx, stat->expr, ctx->from_eval);
    if(FAILED(hres))
        return hres;

    return !ctx->from_eval || push_instr(ctx, OP_setret) ? S_OK : E_OUTOFMEMORY;
}