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
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  JS_E_VBARRAY_EXPECTED ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SafeArrayGetDim (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* vbarray_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT VBArray_dimensions(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    VBArrayInstance *vbarray;

    TRACE("\n");

    vbarray = vbarray_this(vthis);
    if(!vbarray)
        return throw_type_error(ctx, JS_E_VBARRAY_EXPECTED, NULL);

    if(r)
        *r = jsval_number(SafeArrayGetDim(vbarray->safearray));
    return S_OK;
}