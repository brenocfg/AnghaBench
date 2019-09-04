#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ else_stat; scalar_t__ if_stat; int /*<<< orphan*/  expr; } ;
typedef  TYPE_1__ if_statement_t ;
struct TYPE_10__ {int /*<<< orphan*/  code_off; } ;
typedef  TYPE_2__ compiler_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_jmp ; 
 int /*<<< orphan*/  OP_jmp_z ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  compile_expression (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_statement (TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned int push_instr (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_arg_uint (TYPE_2__*,unsigned int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_if_statement(compiler_ctx_t *ctx, if_statement_t *stat)
{
    unsigned jmp_else;
    HRESULT hres;

    hres = compile_expression(ctx, stat->expr, TRUE);
    if(FAILED(hres))
        return hres;

    jmp_else = push_instr(ctx, OP_jmp_z);
    if(!jmp_else)
        return E_OUTOFMEMORY;

    hres = compile_statement(ctx, NULL, stat->if_stat);
    if(FAILED(hres))
        return hres;

    if(stat->else_stat) {
        unsigned jmp_end;

        jmp_end = push_instr(ctx, OP_jmp);
        if(!jmp_end)
            return E_OUTOFMEMORY;

        set_arg_uint(ctx, jmp_else, ctx->code_off);

        hres = compile_statement(ctx, NULL, stat->else_stat);
        if(FAILED(hres))
            return hres;

        set_arg_uint(ctx, jmp_end, ctx->code_off);
    }else {
        set_arg_uint(ctx, jmp_else, ctx->code_off);
    }

    return S_OK;
}