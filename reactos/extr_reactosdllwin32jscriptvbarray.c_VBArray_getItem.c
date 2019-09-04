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
typedef  int /*<<< orphan*/  VARIANT ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ DISP_E_BADINDEX ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  JS_E_SUBSCRIPT_OUT_OF_RANGE ; 
 int /*<<< orphan*/  JS_E_VBARRAY_EXPECTED ; 
 unsigned int SafeArrayGetDim (int /*<<< orphan*/ ) ; 
 scalar_t__ SafeArrayGetElement (int /*<<< orphan*/ ,int*,void*) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  VariantClear (int /*<<< orphan*/ *) ; 
 int* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (int*) ; 
 scalar_t__ throw_range_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ to_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ variant_to_jsval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* vbarray_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT VBArray_getItem(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    VBArrayInstance *vbarray;
    int i, *indexes;
    VARIANT out;
    HRESULT hres;

    TRACE("\n");

    vbarray = vbarray_this(vthis);
    if(!vbarray)
        return throw_type_error(ctx, JS_E_VBARRAY_EXPECTED, NULL);

    if(argc < SafeArrayGetDim(vbarray->safearray))
        return throw_range_error(ctx, JS_E_SUBSCRIPT_OUT_OF_RANGE, NULL);

    indexes = heap_alloc(sizeof(int)*argc);
    if(!indexes)
        return E_OUTOFMEMORY;

    for(i=0; i<argc; i++) {
        hres = to_int32(ctx, argv[i], indexes+i);
        if(FAILED(hres)) {
            heap_free(indexes);
            return hres;
        }
    }

    hres = SafeArrayGetElement(vbarray->safearray, indexes, (void*)&out);
    heap_free(indexes);
    if(hres == DISP_E_BADINDEX)
        return throw_range_error(ctx, JS_E_SUBSCRIPT_OUT_OF_RANGE, NULL);
    else if(FAILED(hres))
        return hres;

    if(r) {
        hres = variant_to_jsval(&out, r);
        VariantClear(&out);
    }
    return hres;
}