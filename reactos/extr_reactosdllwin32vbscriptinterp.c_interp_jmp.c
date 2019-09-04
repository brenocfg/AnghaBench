#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_2__* instr; } ;
typedef  TYPE_3__ exec_ctx_t ;
struct TYPE_6__ {unsigned int uint; } ;
struct TYPE_7__ {TYPE_1__ arg1; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int const) ; 
 int /*<<< orphan*/  instr_jmp (TYPE_3__*,unsigned int const) ; 

__attribute__((used)) static HRESULT interp_jmp(exec_ctx_t *ctx)
{
    const unsigned arg = ctx->instr->arg1.uint;

    TRACE("%u\n", arg);

    instr_jmp(ctx, arg);
    return S_OK;
}