#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ while_end_label; scalar_t__ stack_use; struct TYPE_6__* next; } ;
typedef  TYPE_1__ statement_ctx_t ;
struct TYPE_7__ {TYPE_1__* stat_ctx; } ;
typedef  TYPE_2__ compile_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  OP_jmp ; 
 int /*<<< orphan*/  OP_pop ; 
 int /*<<< orphan*/  push_instr_addr (TYPE_2__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  push_instr_uint (TYPE_2__*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static HRESULT compile_exitdo_statement(compile_ctx_t *ctx)
{
    statement_ctx_t *iter;
    unsigned pop_cnt = 0;

    for(iter = ctx->stat_ctx; iter; iter = iter->next) {
        pop_cnt += iter->stack_use;
        if(iter->while_end_label)
            break;
    }
    if(!iter) {
        FIXME("Exit Do outside Do Loop\n");
        return E_FAIL;
    }

    if(pop_cnt) {
        HRESULT hres;

        hres = push_instr_uint(ctx, OP_pop, pop_cnt);
        if(FAILED(hres))
            return hres;
    }

    return push_instr_addr(ctx, OP_jmp, iter->while_end_label);
}