#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  script; } ;
typedef  TYPE_1__ exec_ctx_t ;
typedef  int WORD ;
typedef  int /*<<< orphan*/  VARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int DISPATCH_PROPERTYPUTREF ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 scalar_t__ VT_DISPATCH ; 
 int /*<<< orphan*/  V_DISPATCH (int /*<<< orphan*/ *) ; 
 scalar_t__ V_VT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VariantCopyInd (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_disp_value (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT assign_value(exec_ctx_t *ctx, VARIANT *dst, VARIANT *src, WORD flags)
{
    HRESULT hres;

    hres = VariantCopyInd(dst, src);
    if(FAILED(hres))
        return hres;

    if(V_VT(dst) == VT_DISPATCH && !(flags & DISPATCH_PROPERTYPUTREF)) {
        VARIANT value;

        hres = get_disp_value(ctx->script, V_DISPATCH(dst), &value);
        IDispatch_Release(V_DISPATCH(dst));
        if(FAILED(hres))
            return hres;

        *dst = value;
    }

    return S_OK;
}