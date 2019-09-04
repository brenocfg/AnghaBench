#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* call_ctx; } ;
typedef  TYPE_1__ script_ctx_t ;
struct TYPE_8__ {int flags; int /*<<< orphan*/  this_obj; int /*<<< orphan*/  ret; } ;
typedef  TYPE_2__ call_frame_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int EXEC_CONSTRUCTOR ; 
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 unsigned int get_op_uint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmp_abs (TYPE_1__*,int) ; 
 int /*<<< orphan*/  jsval_disp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  steal_ret (TYPE_2__*) ; 

__attribute__((used)) static HRESULT interp_ret(script_ctx_t *ctx)
{
    const unsigned clear_ret = get_op_uint(ctx, 0);
    call_frame_t *frame = ctx->call_ctx;

    TRACE("\n");

    if(clear_ret)
        jsval_release(steal_ret(frame));

    if((frame->flags & EXEC_CONSTRUCTOR) && !is_object_instance(frame->ret)) {
        jsval_release(frame->ret);
        IDispatch_AddRef(frame->this_obj);
        frame->ret = jsval_disp(frame->this_obj);
    }

    jmp_abs(ctx, -1);
    return S_OK;
}