#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int resume_next; TYPE_3__* script; TYPE_2__* instr; } ;
typedef  TYPE_4__ exec_ctx_t ;
struct TYPE_8__ {int /*<<< orphan*/  err_number; } ;
struct TYPE_6__ {int uint; } ;
struct TYPE_7__ {TYPE_1__ arg1; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int const) ; 

__attribute__((used)) static HRESULT interp_errmode(exec_ctx_t *ctx)
{
    const int err_mode = ctx->instr->arg1.uint;

    TRACE("%d\n", err_mode);

    ctx->resume_next = err_mode;
    ctx->script->err_number = S_OK;
    return S_OK;
}