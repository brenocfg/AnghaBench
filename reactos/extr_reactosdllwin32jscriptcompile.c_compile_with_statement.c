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
struct TYPE_5__ {int /*<<< orphan*/  statement; int /*<<< orphan*/  expr; } ;
typedef  TYPE_1__ with_statement_t ;
struct TYPE_6__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ statement_ctx_t ;
typedef  int /*<<< orphan*/  compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  OP_pop_scope ; 
 int /*<<< orphan*/  OP_push_scope ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_statement (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_with_statement(compiler_ctx_t *ctx, with_statement_t *stat)
{
    statement_ctx_t stat_ctx = {0, TRUE, FALSE};
    HRESULT hres;

    hres = compile_expression(ctx, stat->expr, TRUE);
    if(FAILED(hres))
        return hres;

    if(!push_instr(ctx, OP_push_scope))
        return E_OUTOFMEMORY;

    hres = compile_statement(ctx, &stat_ctx, stat->statement);
    if(FAILED(hres))
        return hres;

    if(!push_instr(ctx, OP_pop_scope))
        return E_OUTOFMEMORY;

    return S_OK;
}