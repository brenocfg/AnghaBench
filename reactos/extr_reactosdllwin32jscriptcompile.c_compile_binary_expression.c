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
typedef  int /*<<< orphan*/  jsop_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
struct TYPE_3__ {int /*<<< orphan*/  expression2; int /*<<< orphan*/  expression1; } ;
typedef  TYPE_1__ binary_expression_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_binary_expression(compiler_ctx_t *ctx, binary_expression_t *expr, jsop_t op)
{
    HRESULT hres;

    hres = compile_expression(ctx, expr->expression1, TRUE);
    if(FAILED(hres))
        return hres;

    hres = compile_expression(ctx, expr->expression2, TRUE);
    if(FAILED(hres))
        return hres;

    return push_instr(ctx, op) ? S_OK : E_OUTOFMEMORY;
}