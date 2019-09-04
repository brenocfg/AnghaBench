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
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NO_HINT ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ get_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 scalar_t__ is_bool (int /*<<< orphan*/ ) ; 
 scalar_t__ is_null (int /*<<< orphan*/ ) ; 
 scalar_t__ is_number (int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 scalar_t__ is_string (int /*<<< orphan*/ ) ; 
 scalar_t__ is_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_null () ; 
 int /*<<< orphan*/  jsval_number (int) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_strict_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jsval_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  to_primitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT equal_values(script_ctx_t *ctx, jsval_t lval, jsval_t rval, BOOL *ret)
{
    if(jsval_type(lval) == jsval_type(rval) || (is_number(lval) && is_number(rval)))
       return jsval_strict_equal(lval, rval, ret);

    /* FIXME: NULL disps should be handled in more general way */
    if(is_object_instance(lval) && !get_object(lval))
        return equal_values(ctx, jsval_null(), rval, ret);
    if(is_object_instance(rval) && !get_object(rval))
        return equal_values(ctx, lval, jsval_null(), ret);

    if((is_null(lval) && is_undefined(rval)) || (is_undefined(lval) && is_null(rval))) {
        *ret = TRUE;
        return S_OK;
    }

    if(is_string(lval) && is_number(rval)) {
        double n;
        HRESULT hres;

        hres = to_number(ctx, lval, &n);
        if(FAILED(hres))
            return hres;

        /* FIXME: optimize */
        return equal_values(ctx, jsval_number(n), rval, ret);
    }

    if(is_string(rval) && is_number(lval)) {
        double n;
        HRESULT hres;

        hres = to_number(ctx, rval, &n);
        if(FAILED(hres))
            return hres;

        /* FIXME: optimize */
        return equal_values(ctx, lval, jsval_number(n), ret);
    }

    if(is_bool(rval))
        return equal_values(ctx, lval, jsval_number(get_bool(rval) ? 1 : 0), ret);

    if(is_bool(lval))
        return equal_values(ctx, jsval_number(get_bool(lval) ? 1 : 0), rval, ret);


    if(is_object_instance(rval) && (is_string(lval) || is_number(lval))) {
        jsval_t prim;
        HRESULT hres;

        hres = to_primitive(ctx, rval, &prim, NO_HINT);
        if(FAILED(hres))
            return hres;

        hres = equal_values(ctx, lval, prim, ret);
        jsval_release(prim);
        return hres;
    }


    if(is_object_instance(lval) && (is_string(rval) || is_number(rval))) {
        jsval_t prim;
        HRESULT hres;

        hres = to_primitive(ctx, lval, &prim, NO_HINT);
        if(FAILED(hres))
            return hres;

        hres = equal_values(ctx, prim, rval, ret);
        jsval_release(prim);
        return hres;
    }


    *ret = FALSE;
    return S_OK;
}