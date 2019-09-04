#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  typeinfo; void* builtin_props; void* builtin_prop_cnt; TYPE_1__* ctx; } ;
struct TYPE_5__ {int /*<<< orphan*/  err_obj; TYPE_3__ err_desc; int /*<<< orphan*/  script_obj; int /*<<< orphan*/  global_obj; TYPE_3__ global_desc; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 void* ARRAY_SIZE (void*) ; 
 int /*<<< orphan*/  ErrObj_tid ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GlobalObj_tid ; 
 int /*<<< orphan*/  create_script_disp (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_vbdisp (TYPE_3__*,int /*<<< orphan*/ *) ; 
 void* err_props ; 
 int /*<<< orphan*/  get_typeinfo (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 void* global_props ; 

HRESULT init_global(script_ctx_t *ctx)
{
    HRESULT hres;

    ctx->global_desc.ctx = ctx;
    ctx->global_desc.builtin_prop_cnt = ARRAY_SIZE(global_props);
    ctx->global_desc.builtin_props = global_props;

    hres = get_typeinfo(GlobalObj_tid, &ctx->global_desc.typeinfo);
    if(FAILED(hres))
        return hres;

    hres = create_vbdisp(&ctx->global_desc, &ctx->global_obj);
    if(FAILED(hres))
        return hres;

    hres = create_script_disp(ctx, &ctx->script_obj);
    if(FAILED(hres))
        return hres;

    ctx->err_desc.ctx = ctx;
    ctx->err_desc.builtin_prop_cnt = ARRAY_SIZE(err_props);
    ctx->err_desc.builtin_props = err_props;

    hres = get_typeinfo(ErrObj_tid, &ctx->err_desc.typeinfo);
    if(FAILED(hres))
        return hres;

    return create_vbdisp(&ctx->err_desc, &ctx->err_obj);
}