#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * error_constr; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  ErrorInst_info ; 
 int /*<<< orphan*/  Error_info ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dispex_from_constr (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT alloc_error(script_ctx_t *ctx, jsdisp_t *prototype,
        jsdisp_t *constr, jsdisp_t **ret)
{
    jsdisp_t *err;
    HRESULT hres;

    err = heap_alloc_zero(sizeof(*err));
    if(!err)
        return E_OUTOFMEMORY;

    if(prototype)
        hres = init_dispex(err, ctx, &Error_info, prototype);
    else
        hres = init_dispex_from_constr(err, ctx, &ErrorInst_info,
            constr ? constr : ctx->error_constr);
    if(FAILED(hres)) {
        heap_free(err);
        return hres;
    }

    *ret = err;
    return S_OK;
}