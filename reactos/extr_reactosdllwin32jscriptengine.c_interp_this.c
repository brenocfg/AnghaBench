#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* call_ctx; } ;
typedef  TYPE_1__ script_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  this_obj; } ;
typedef  TYPE_2__ call_frame_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  IDispatch_AddRef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  jsval_disp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_push (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT interp_this(script_ctx_t *ctx)
{
    call_frame_t *frame = ctx->call_ctx;

    TRACE("\n");

    IDispatch_AddRef(frame->this_obj);
    return stack_push(ctx, jsval_disp(frame->this_obj));
}