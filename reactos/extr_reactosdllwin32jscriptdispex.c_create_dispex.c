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
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  builtin_info_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  const dispex_info ; 
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 

HRESULT create_dispex(script_ctx_t *ctx, const builtin_info_t *builtin_info, jsdisp_t *prototype, jsdisp_t **dispex)
{
    jsdisp_t *ret;
    HRESULT hres;

    ret = heap_alloc_zero(sizeof(jsdisp_t));
    if(!ret)
        return E_OUTOFMEMORY;

    hres = init_dispex(ret, ctx, builtin_info ? builtin_info : &dispex_info, prototype);
    if(FAILED(hres)) {
        heap_free(ret);
        return hres;
    }

    *dispex = ret;
    return S_OK;
}