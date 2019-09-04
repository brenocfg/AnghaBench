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
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
struct TYPE_3__ {int /*<<< orphan*/  value; } ;
typedef  TYPE_1__ NumberInstance ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DOUBLE ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JS_E_NUMBER_EXPECTED ; 
 int /*<<< orphan*/  JS_E_PRECISION_OUT_OF_RANGE ; 
 int /*<<< orphan*/  S_OK ; 
 int floor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_finite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log10 (int /*<<< orphan*/ ) ; 
 TYPE_1__* number_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * number_to_exponential (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * number_to_fixed (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  throw_range_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_int32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT Number_toPrecision(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    NumberInstance *number;
    INT prec = 0, size;
    jsstr_t *str;
    DOUBLE val;
    HRESULT hres;

    if(!(number = number_this(jsthis)))
        return throw_type_error(ctx, JS_E_NUMBER_EXPECTED, NULL);

    if(argc) {
        hres = to_int32(ctx, argv[0], &prec);
        if(FAILED(hres))
            return hres;

        if(prec<1 || prec>21)
            return throw_range_error(ctx, JS_E_PRECISION_OUT_OF_RANGE, NULL);
    }

    val = number->value;
    if(!is_finite(val) || !prec) {
        hres = to_string(ctx, jsval_number(val), &str);
        if(FAILED(hres))
            return hres;
    }else {
        if(val != 0)
            size = floor(log10(val>0 ? val : -val)) + 1;
        else
            size = 1;

        if(size > prec)
            str = number_to_exponential(val, prec-1);
        else
            str = number_to_fixed(val, prec-size);
        if(!str)
            return E_OUTOFMEMORY;
    }

    if(r)
        *r = jsval_string(str);
    else
        jsstr_release(str);
    return S_OK;
}