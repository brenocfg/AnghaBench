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
typedef  int /*<<< orphan*/  script_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; int /*<<< orphan*/ * ctx; TYPE_1__ IDispatchEx_iface; } ;
typedef  TYPE_2__ ScriptDisp ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  ScriptDispVtbl ; 
 TYPE_2__* heap_alloc_zero (int) ; 

HRESULT create_script_disp(script_ctx_t *ctx, ScriptDisp **ret)
{
    ScriptDisp *script_disp;

    script_disp = heap_alloc_zero(sizeof(*script_disp));
    if(!script_disp)
        return E_OUTOFMEMORY;

    script_disp->IDispatchEx_iface.lpVtbl = &ScriptDispVtbl;
    script_disp->ref = 1;
    script_disp->ctx = ctx;

    *ret = script_disp;
    return S_OK;
}