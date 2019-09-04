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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NO_HINT ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  get_string (int /*<<< orphan*/ ) ; 
 scalar_t__ is_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isnan (double) ; 
 scalar_t__ jsstr_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  to_primitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT less_eval(script_ctx_t *ctx, jsval_t lval, jsval_t rval, BOOL greater, BOOL *ret)
{
    double ln, rn;
    jsval_t l, r;
    HRESULT hres;

    hres = to_primitive(ctx, lval, &l, NO_HINT);
    if(FAILED(hres))
        return hres;

    hres = to_primitive(ctx, rval, &r, NO_HINT);
    if(FAILED(hres)) {
        jsval_release(l);
        return hres;
    }

    if(is_string(l) && is_string(r)) {
        *ret = (jsstr_cmp(get_string(l), get_string(r)) < 0) ^ greater;
        jsstr_release(get_string(l));
        jsstr_release(get_string(r));
        return S_OK;
    }

    hres = to_number(ctx, l, &ln);
    jsval_release(l);
    if(SUCCEEDED(hres))
        hres = to_number(ctx, r, &rn);
    jsval_release(r);
    if(FAILED(hres))
        return hres;

    *ret = !isnan(ln) && !isnan(rn) && ((ln < rn) ^ greater);
    return S_OK;
}