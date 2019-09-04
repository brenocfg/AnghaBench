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
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_METHOD ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 double get_number (int /*<<< orphan*/ ) ; 
 scalar_t__ is_number (int /*<<< orphan*/ ) ; 
 scalar_t__ is_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_call_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int jsstr_cmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT sort_cmp(script_ctx_t *ctx, jsdisp_t *cmp_func, jsval_t v1, jsval_t v2, INT *cmp)
{
    HRESULT hres;

    if(cmp_func) {
        jsval_t args[2];
        jsval_t res;
        double n;

        args[0] = v1;
        args[1] = v2;

        hres = jsdisp_call_value(cmp_func, NULL, DISPATCH_METHOD, 2, args, &res);
        if(FAILED(hres))
            return hres;

        hres = to_number(ctx, res, &n);
        jsval_release(res);
        if(FAILED(hres))
            return hres;

        if(n == 0)
            *cmp = 0;
        *cmp = n > 0.0 ? 1 : -1;
    }else if(is_undefined(v1)) {
        *cmp = is_undefined(v2) ? 0 : 1;
    }else if(is_undefined(v2)) {
        *cmp = -1;
    }else if(is_number(v1) && is_number(v2)) {
        double d = get_number(v1)-get_number(v2);
        if(d > 0.0)
            *cmp = 1;
        else
            *cmp = d < -0.0 ? -1 : 0;
    }else {
        jsstr_t *x, *y;

        hres = to_string(ctx, v1, &x);
        if(FAILED(hres))
            return hres;

        hres = to_string(ctx, v2, &y);
        if(SUCCEEDED(hres)) {
            *cmp = jsstr_cmp(x, y);
            jsstr_release(y);
        }
        jsstr_release(x);
        if(FAILED(hres))
            return hres;
    }

    return S_OK;
}