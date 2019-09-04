#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_2__* call_ctx; } ;
typedef  TYPE_1__ script_ctx_t ;
struct TYPE_10__ {int /*<<< orphan*/  bytecode; int /*<<< orphan*/  ret; scalar_t__ this_obj; scalar_t__ variable_obj; scalar_t__ function_instance; struct TYPE_10__* prev_frame; scalar_t__ pop_locals; scalar_t__ pop_variables; TYPE_4__* scope; scalar_t__ arguments_obj; TYPE_4__* base_scope; int /*<<< orphan*/  stack_base; } ;
typedef  TYPE_2__ call_frame_t ;
struct TYPE_11__ {int ref; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatch_Release (scalar_t__) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  detach_arguments_object (scalar_t__) ; 
 int /*<<< orphan*/  detach_variable_object (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_2__*) ; 
 int /*<<< orphan*/  jsdisp_release (scalar_t__) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_bytecode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scope_release (TYPE_4__*) ; 
 int /*<<< orphan*/  stack_popn (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void pop_call_frame(script_ctx_t *ctx)
{
    call_frame_t *frame = ctx->call_ctx;

    frame->stack_base -= frame->pop_locals + frame->pop_variables;

    assert(frame->scope == frame->base_scope);

    /* If current scope will be kept alive, we need to transfer local variables to its variable object. */
    if(frame->scope && frame->scope->ref > 1) {
        HRESULT hres = detach_variable_object(ctx, frame, TRUE);
        if(FAILED(hres))
            ERR("Failed to detach variable object: %08x\n", hres);
    }

    if(frame->arguments_obj)
        detach_arguments_object(frame->arguments_obj);
    if(frame->scope)
        scope_release(frame->scope);

    if(frame->pop_variables)
        stack_popn(ctx, frame->pop_variables);
    stack_popn(ctx, frame->pop_locals);

    ctx->call_ctx = frame->prev_frame;

    if(frame->function_instance)
        jsdisp_release(frame->function_instance);
    if(frame->variable_obj)
        jsdisp_release(frame->variable_obj);
    if(frame->this_obj)
        IDispatch_Release(frame->this_obj);
    jsval_release(frame->ret);
    release_bytecode(frame->bytecode);
    heap_free(frame);
}