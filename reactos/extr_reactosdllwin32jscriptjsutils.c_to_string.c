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
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HINT_STRING ; 
#define  JSV_BOOL 133 
#define  JSV_NULL 132 
#define  JSV_NUMBER 131 
#define  JSV_OBJECT 130 
#define  JSV_STRING 129 
#define  JSV_UNDEFINED 128 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  debugstr_jsval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  double_to_string (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsstr_addref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsstr_alloc (char const*) ; 
 int /*<<< orphan*/ * jsstr_undefined () ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int jsval_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_primitive (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

HRESULT to_string(script_ctx_t *ctx, jsval_t val, jsstr_t **str)
{
    static const WCHAR nullW[] = {'n','u','l','l',0};
    static const WCHAR trueW[] = {'t','r','u','e',0};
    static const WCHAR falseW[] = {'f','a','l','s','e',0};

    switch(jsval_type(val)) {
    case JSV_UNDEFINED:
        *str = jsstr_undefined();
        return S_OK;
    case JSV_NULL:
        *str = jsstr_alloc(nullW);
        break;
    case JSV_NUMBER:
        return double_to_string(get_number(val), str);
    case JSV_STRING:
        *str = jsstr_addref(get_string(val));
        break;
    case JSV_OBJECT: {
        jsval_t prim;
        HRESULT hres;

        hres = to_primitive(ctx, val, &prim, HINT_STRING);
        if(FAILED(hres))
            return hres;

        hres = to_string(ctx, prim, str);
        jsval_release(prim);
        return hres;
    }
    case JSV_BOOL:
        *str = jsstr_alloc(get_bool(val) ? trueW : falseW);
        break;
    default:
        FIXME("unsupported %s\n", debugstr_jsval(val));
        return E_NOTIMPL;
    }

    return *str ? S_OK : E_OUTOFMEMORY;
}