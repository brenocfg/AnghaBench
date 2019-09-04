#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {scalar_t__ else_stat; TYPE_3__* elseifs; scalar_t__ if_stat; int /*<<< orphan*/  expr; } ;
typedef  TYPE_2__ if_statement_t ;
struct TYPE_18__ {scalar_t__ stat; int /*<<< orphan*/  expr; struct TYPE_18__* next; } ;
typedef  TYPE_3__ elseif_decl_t ;
struct TYPE_19__ {int /*<<< orphan*/  instr_cnt; } ;
typedef  TYPE_4__ compile_ctx_t ;
struct TYPE_16__ {int /*<<< orphan*/  uint; } ;
struct TYPE_20__ {TYPE_1__ arg1; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_jmp ; 
 int /*<<< orphan*/  OP_jmp_false ; 
 int /*<<< orphan*/  S_OK ; 
 unsigned int alloc_label (TYPE_4__*) ; 
 int /*<<< orphan*/  compile_expression (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  compile_statement (TYPE_4__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  emit_catch (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* instr_ptr (TYPE_4__*,unsigned int) ; 
 int /*<<< orphan*/  label_set_addr (TYPE_4__*,unsigned int) ; 
 unsigned int push_instr (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_addr (TYPE_4__*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static HRESULT compile_if_statement(compile_ctx_t *ctx, if_statement_t *stat)
{
    unsigned cnd_jmp, endif_label = 0;
    elseif_decl_t *elseif_decl;
    HRESULT hres;

    hres = compile_expression(ctx, stat->expr);
    if(FAILED(hres))
        return hres;

    cnd_jmp = push_instr(ctx, OP_jmp_false);
    if(!cnd_jmp)
        return E_OUTOFMEMORY;

    if(!emit_catch(ctx, 0))
        return E_OUTOFMEMORY;

    hres = compile_statement(ctx, NULL, stat->if_stat);
    if(FAILED(hres))
        return hres;

    if(stat->else_stat || stat->elseifs) {
        endif_label = alloc_label(ctx);
        if(!endif_label)
            return E_OUTOFMEMORY;

        hres = push_instr_addr(ctx, OP_jmp, endif_label);
        if(FAILED(hres))
            return hres;
    }

    for(elseif_decl = stat->elseifs; elseif_decl; elseif_decl = elseif_decl->next) {
        instr_ptr(ctx, cnd_jmp)->arg1.uint = ctx->instr_cnt;

        hres = compile_expression(ctx, elseif_decl->expr);
        if(FAILED(hres))
            return hres;

        cnd_jmp = push_instr(ctx, OP_jmp_false);
        if(!cnd_jmp)
            return E_OUTOFMEMORY;

        if(!emit_catch(ctx, 0))
            return E_OUTOFMEMORY;

        hres = compile_statement(ctx, NULL, elseif_decl->stat);
        if(FAILED(hres))
            return hres;

        hres = push_instr_addr(ctx, OP_jmp, endif_label);
        if(FAILED(hres))
            return hres;
    }

    instr_ptr(ctx, cnd_jmp)->arg1.uint = ctx->instr_cnt;

    if(stat->else_stat) {
        hres = compile_statement(ctx, NULL, stat->else_stat);
        if(FAILED(hres))
            return hres;
    }

    if(endif_label)
        label_set_addr(ctx, endif_label);
    return S_OK;
}