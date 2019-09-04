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
struct TYPE_7__ {TYPE_1__* jscaller; struct TYPE_7__* stack; int /*<<< orphan*/  stack_top; scalar_t__ last_match; int /*<<< orphan*/  tmp_heap; scalar_t__ cc; int /*<<< orphan*/  acc; scalar_t__ ref; } ;
typedef  TYPE_2__ script_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  IServiceProvider_iface; int /*<<< orphan*/ * ctx; } ;

/* Variables and functions */
 int /*<<< orphan*/  IServiceProvider_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_ei (TYPE_2__*) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  heap_pool_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (scalar_t__) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_cc (scalar_t__) ; 

void script_release(script_ctx_t *ctx)
{
    if(--ctx->ref)
        return;

    jsval_release(ctx->acc);
    clear_ei(ctx);
    if(ctx->cc)
        release_cc(ctx->cc);
    heap_pool_free(&ctx->tmp_heap);
    if(ctx->last_match)
        jsstr_release(ctx->last_match);
    assert(!ctx->stack_top);
    heap_free(ctx->stack);

    ctx->jscaller->ctx = NULL;
    IServiceProvider_Release(&ctx->jscaller->IServiceProvider_iface);

    heap_free(ctx);
}