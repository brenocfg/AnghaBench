#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int member_0; scalar_t__ for_end_label; } ;
typedef  TYPE_3__ statement_ctx_t ;
struct TYPE_11__ {int /*<<< orphan*/  body; scalar_t__ step_expr; scalar_t__ to_expr; scalar_t__ from_expr; int /*<<< orphan*/  identifier; } ;
typedef  TYPE_4__ forto_statement_t ;
typedef  int /*<<< orphan*/  compile_ctx_t ;
struct TYPE_9__ {void* bstr; scalar_t__ uint; } ;
struct TYPE_8__ {void* bstr; scalar_t__ uint; } ;
struct TYPE_12__ {TYPE_2__ arg1; TYPE_1__ arg2; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  void* BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_assign_ident ; 
 int /*<<< orphan*/  OP_incc ; 
 int /*<<< orphan*/  OP_jmp ; 
 int /*<<< orphan*/  OP_pop ; 
 int /*<<< orphan*/  OP_short ; 
 int /*<<< orphan*/  OP_step ; 
 int /*<<< orphan*/  OP_val ; 
 int /*<<< orphan*/  S_OK ; 
 void* alloc_bstr_arg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ alloc_label (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  compile_expression (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  compile_statement (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_catch (int /*<<< orphan*/ *,int) ; 
 TYPE_5__* instr_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  label_set_addr (int /*<<< orphan*/ *,scalar_t__) ; 
 unsigned int push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_addr (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  push_instr_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  push_instr_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static HRESULT compile_forto_statement(compile_ctx_t *ctx, forto_statement_t *stat)
{
    statement_ctx_t loop_ctx = {2};
    unsigned step_instr, instr;
    BSTR identifier;
    HRESULT hres;

    identifier = alloc_bstr_arg(ctx, stat->identifier);
    if(!identifier)
        return E_OUTOFMEMORY;

    hres = compile_expression(ctx, stat->from_expr);
    if(FAILED(hres))
        return hres;

    /* FIXME: Assign should happen after both expressions evaluation. */
    instr = push_instr(ctx, OP_assign_ident);
    if(!instr)
        return E_OUTOFMEMORY;
    instr_ptr(ctx, instr)->arg1.bstr = identifier;
    instr_ptr(ctx, instr)->arg2.uint = 0;

    hres = compile_expression(ctx, stat->to_expr);
    if(FAILED(hres))
        return hres;

    if(!push_instr(ctx, OP_val))
        return E_OUTOFMEMORY;

    if(stat->step_expr) {
        hres = compile_expression(ctx, stat->step_expr);
        if(FAILED(hres))
            return hres;

        if(!push_instr(ctx, OP_val))
            return E_OUTOFMEMORY;
    }else {
        hres = push_instr_int(ctx, OP_short, 1);
        if(FAILED(hres))
            return hres;
    }

    loop_ctx.for_end_label = alloc_label(ctx);
    if(!loop_ctx.for_end_label)
        return E_OUTOFMEMORY;

    step_instr = push_instr(ctx, OP_step);
    if(!step_instr)
        return E_OUTOFMEMORY;
    instr_ptr(ctx, step_instr)->arg2.bstr = identifier;
    instr_ptr(ctx, step_instr)->arg1.uint = loop_ctx.for_end_label;

    if(!emit_catch(ctx, 2))
        return E_OUTOFMEMORY;

    hres = compile_statement(ctx, &loop_ctx, stat->body);
    if(FAILED(hres))
        return hres;

    /* FIXME: Error handling can't be done compatible with native using OP_incc here. */
    instr = push_instr(ctx, OP_incc);
    if(!instr)
        return E_OUTOFMEMORY;
    instr_ptr(ctx, instr)->arg1.bstr = identifier;

    hres = push_instr_addr(ctx, OP_jmp, step_instr);
    if(FAILED(hres))
        return hres;

    hres = push_instr_uint(ctx, OP_pop, 2);
    if(FAILED(hres))
        return hres;

    label_set_addr(ctx, loop_ctx.for_end_label);

    /* FIXME: reconsider after OP_incc fixup. */
    if(!emit_catch(ctx, 0))
        return E_OUTOFMEMORY;

    return S_OK;
}