#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__* stack; scalar_t__* vars; scalar_t__* args; int /*<<< orphan*/  heap; scalar_t__* arrays; TYPE_1__* func; scalar_t__ this_obj; int /*<<< orphan*/  dynamic_vars; scalar_t__ ret_val; } ;
typedef  TYPE_2__ exec_ctx_t ;
struct TYPE_4__ {unsigned int arg_cnt; unsigned int var_cnt; } ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatch_Release (scalar_t__) ; 
 int /*<<< orphan*/  SafeArrayDestroy (scalar_t__) ; 
 int /*<<< orphan*/  VariantClear (scalar_t__*) ; 
 int /*<<< orphan*/  heap_free (scalar_t__*) ; 
 int /*<<< orphan*/  heap_pool_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_dynamic_vars (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_exec(exec_ctx_t *ctx)
{
    unsigned i;

    VariantClear(&ctx->ret_val);
    release_dynamic_vars(ctx->dynamic_vars);

    if(ctx->this_obj)
        IDispatch_Release(ctx->this_obj);

    if(ctx->args) {
        for(i=0; i < ctx->func->arg_cnt; i++)
            VariantClear(ctx->args+i);
    }

    if(ctx->vars) {
        for(i=0; i < ctx->func->var_cnt; i++)
            VariantClear(ctx->vars+i);
    }

    if(ctx->arrays) {
        for(i=0; i < ctx->func->var_cnt; i++) {
            if(ctx->arrays[i])
                SafeArrayDestroy(ctx->arrays[i]);
        }
        heap_free(ctx->arrays);
    }

    heap_pool_free(&ctx->heap);
    heap_free(ctx->args);
    heap_free(ctx->vars);
    heap_free(ctx->stack);
}