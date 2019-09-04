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
struct TYPE_5__ {unsigned int instr; TYPE_1__* code; } ;
typedef  TYPE_2__ exec_ctx_t ;
struct TYPE_4__ {unsigned int instrs; } ;

/* Variables and functions */

__attribute__((used)) static inline void instr_jmp(exec_ctx_t *ctx, unsigned addr)
{
    ctx->instr = ctx->code->instrs + addr;
}