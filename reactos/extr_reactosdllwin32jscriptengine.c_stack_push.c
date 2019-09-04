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
struct TYPE_3__ {int stack_size; int stack_top; int /*<<< orphan*/ * stack; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * heap_alloc (int) ; 
 int /*<<< orphan*/ * heap_realloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT stack_push(script_ctx_t *ctx, jsval_t v)
{
    if(!ctx->stack_size) {
        ctx->stack = heap_alloc(16*sizeof(*ctx->stack));
        if(!ctx->stack)
            return E_OUTOFMEMORY;
        ctx->stack_size = 16;
    }else if(ctx->stack_size == ctx->stack_top) {
        jsval_t *new_stack;

        new_stack = heap_realloc(ctx->stack, ctx->stack_size*2*sizeof(*new_stack));
        if(!new_stack) {
            jsval_release(v);
            return E_OUTOFMEMORY;
        }

        ctx->stack = new_stack;
        ctx->stack_size *= 2;
    }

    ctx->stack[ctx->stack_top++] = v;
    return S_OK;
}