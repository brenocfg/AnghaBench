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

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINT_NUMBER ; 
#define  JSV_BOOL 134 
#define  JSV_NULL 133 
#define  JSV_NUMBER 132 
#define  JSV_OBJECT 131 
#define  JSV_STRING 130 
#define  JSV_UNDEFINED 129 
#define  JSV_VARIANT 128 
 double NAN ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_variant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_bool (int /*<<< orphan*/ ) ; 
 double get_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_variant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int jsval_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  str_to_number (int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  to_primitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HRESULT to_number(script_ctx_t *ctx, jsval_t val, double *ret)
{
    switch(jsval_type(val)) {
    case JSV_UNDEFINED:
        *ret = NAN;
        return S_OK;
    case JSV_NULL:
        *ret = 0;
        return S_OK;
    case JSV_NUMBER:
        *ret = get_number(val);
        return S_OK;
    case JSV_STRING:
        return str_to_number(get_string(val), ret);
    case JSV_OBJECT: {
        jsval_t prim;
        HRESULT hres;

        hres = to_primitive(ctx, val, &prim, HINT_NUMBER);
        if(FAILED(hres))
            return hres;

        hres = to_number(ctx, prim, ret);
        jsval_release(prim);
        return hres;
    }
    case JSV_BOOL:
        *ret = get_bool(val) ? 1 : 0;
        return S_OK;
    case JSV_VARIANT:
        FIXME("unimplemented for variant %s\n", debugstr_variant(get_variant(val)));
        return E_NOTIMPL;
    };

    assert(0);
    return E_FAIL;
}