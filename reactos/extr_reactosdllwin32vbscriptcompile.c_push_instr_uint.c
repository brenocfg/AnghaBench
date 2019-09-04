#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vbsop_t ;
typedef  int /*<<< orphan*/  compile_ctx_t ;
struct TYPE_3__ {unsigned int uint; } ;
struct TYPE_4__ {TYPE_1__ arg1; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* instr_ptr (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int push_instr (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT push_instr_uint(compile_ctx_t *ctx, vbsop_t op, unsigned arg)
{
    unsigned ret;

    ret = push_instr(ctx, op);
    if(!ret)
        return E_OUTOFMEMORY;

    instr_ptr(ctx, ret)->arg1.uint = arg;
    return S_OK;
}