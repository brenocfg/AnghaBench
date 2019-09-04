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
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 unsigned int get_op_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jmp_abs (int /*<<< orphan*/ *,unsigned int const) ; 
 int /*<<< orphan*/  jmp_next (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_strict_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  stack_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_popn (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stack_top (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_case(script_ctx_t *ctx)
{
    const unsigned arg = get_op_uint(ctx, 0);
    jsval_t v;
    BOOL b;
    HRESULT hres;

    TRACE("\n");

    v = stack_pop(ctx);
    hres = jsval_strict_equal(stack_top(ctx), v, &b);
    jsval_release(v);
    if(FAILED(hres))
        return hres;

    if(b) {
        stack_popn(ctx, 1);
        jmp_abs(ctx, arg);
    }else {
        jmp_next(ctx);
    }
    return S_OK;
}