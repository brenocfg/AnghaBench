#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  v; } ;
typedef  TYPE_1__ variant_val_t ;
typedef  int /*<<< orphan*/  exec_ctx_t ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  VarEqv (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_val (TYPE_1__*) ; 
 int /*<<< orphan*/  stack_pop_val (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_eqv(exec_ctx_t *ctx)
{
    variant_val_t r, l;
    VARIANT v;
    HRESULT hres;

    TRACE("\n");

    hres = stack_pop_val(ctx, &r);
    if(FAILED(hres))
        return hres;

    hres = stack_pop_val(ctx, &l);
    if(SUCCEEDED(hres)) {
        hres = VarEqv(l.v, r.v, &v);
        release_val(&l);
    }
    release_val(&r);
    if(FAILED(hres))
        return hres;

    return stack_push(ctx, &v);
}