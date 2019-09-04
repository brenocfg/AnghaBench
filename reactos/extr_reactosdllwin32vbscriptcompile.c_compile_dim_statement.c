#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_3__* dim_decls; } ;
typedef  TYPE_2__ dim_statement_t ;
struct TYPE_14__ {struct TYPE_14__* next; int /*<<< orphan*/  name; scalar_t__ is_array; } ;
typedef  TYPE_3__ dim_decl_t ;
struct TYPE_15__ {TYPE_3__* dim_decls_tail; TYPE_3__* dim_decls; TYPE_1__* func; } ;
typedef  TYPE_4__ compile_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  array_cnt; int /*<<< orphan*/  var_cnt; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_dim ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_catch (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_args_name (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_const_decls (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lookup_dim_decls (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  push_instr_bstr_uint (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT compile_dim_statement(compile_ctx_t *ctx, dim_statement_t *stat)
{
    dim_decl_t *dim_decl = stat->dim_decls;

    while(1) {
        if(lookup_dim_decls(ctx, dim_decl->name) || lookup_args_name(ctx, dim_decl->name)
           || lookup_const_decls(ctx, dim_decl->name, FALSE)) {
            FIXME("dim %s name redefined\n", debugstr_w(dim_decl->name));
            return E_FAIL;
        }

        ctx->func->var_cnt++;

        if(dim_decl->is_array) {
            HRESULT hres = push_instr_bstr_uint(ctx, OP_dim, dim_decl->name, ctx->func->array_cnt++);
            if(FAILED(hres))
                return hres;

            if(!emit_catch(ctx, 0))
                return E_OUTOFMEMORY;
        }

        if(!dim_decl->next)
            break;
        dim_decl = dim_decl->next;
    }

    if(ctx->dim_decls_tail)
        ctx->dim_decls_tail->next = stat->dim_decls;
    else
        ctx->dim_decls = stat->dim_decls;
    ctx->dim_decls_tail = dim_decl;
    return S_OK;
}