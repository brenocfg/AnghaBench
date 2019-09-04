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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_3__ {int /*<<< orphan*/  safearray; } ;
typedef  TYPE_1__ VBArrayInstance ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ DISP_E_BADINDEX ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  JS_E_SUBSCRIPT_OUT_OF_RANGE ; 
 int /*<<< orphan*/  JS_E_VBARRAY_EXPECTED ; 
 scalar_t__ S_OK ; 
 scalar_t__ SafeArrayGetLBound (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  jsval_number (int) ; 
 scalar_t__ throw_range_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ to_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 TYPE_1__* vbarray_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT VBArray_lbound(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    VBArrayInstance *vbarray;
    int dim;
    HRESULT hres;

    TRACE("\n");

    vbarray = vbarray_this(vthis);
    if(!vbarray)
        return throw_type_error(ctx, JS_E_VBARRAY_EXPECTED, NULL);

    if(argc) {
        hres = to_int32(ctx, argv[0], &dim);
        if(FAILED(hres))
            return hres;
    } else
        dim = 1;

    hres = SafeArrayGetLBound(vbarray->safearray, dim, &dim);
    if(hres == DISP_E_BADINDEX)
        return throw_range_error(ctx, JS_E_SUBSCRIPT_OUT_OF_RANGE, NULL);
    else if(FAILED(hres))
        return hres;

    if(r)
        *r = jsval_number(dim);
    return S_OK;
}