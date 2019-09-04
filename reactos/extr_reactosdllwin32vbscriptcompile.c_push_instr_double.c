#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vbsop_t ;
struct TYPE_8__ {int /*<<< orphan*/  code; } ;
typedef  TYPE_2__ compile_ctx_t ;
struct TYPE_7__ {double* dbl; } ;
struct TYPE_9__ {TYPE_1__ arg1; } ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 double* compiler_alloc (int /*<<< orphan*/ ,int) ; 
 TYPE_5__* instr_ptr (TYPE_2__*,unsigned int) ; 
 unsigned int push_instr (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT push_instr_double(compile_ctx_t *ctx, vbsop_t op, double arg)
{
    unsigned instr;
    double *d;

    d = compiler_alloc(ctx->code, sizeof(double));
    if(!d)
        return E_OUTOFMEMORY;

    instr = push_instr(ctx, op);
    if(!instr)
        return E_OUTOFMEMORY;

    *d = arg;
    instr_ptr(ctx, instr)->arg1.dbl = d;
    return S_OK;
}