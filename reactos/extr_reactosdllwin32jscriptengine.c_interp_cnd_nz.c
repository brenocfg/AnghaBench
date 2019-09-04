#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 unsigned int get_op_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmp_abs (int /*<<< orphan*/ *,unsigned int const) ; 
 int /*<<< orphan*/  jmp_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_popn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stack_top (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_boolean (int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static HRESULT interp_cnd_nz(script_ctx_t *ctx)
{
    const unsigned arg = get_op_uint(ctx, 0);
    BOOL b;
    HRESULT hres;

    TRACE("\n");

    hres = to_boolean(stack_top(ctx), &b);
    if(FAILED(hres))
        return hres;

    if(b) {
        jmp_abs(ctx, arg);
    }else {
        stack_popn(ctx, 1);
        jmp_next(ctx);
    }
    return S_OK;
}