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
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  scalar_t__ hint_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_METHOD ; 
 int /*<<< orphan*/  DISPID_VALUE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ HINT_NUMBER ; 
 scalar_t__ HINT_STRING ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSCLASS_DATE ; 
 int /*<<< orphan*/  JS_E_TO_PRIMITIVE ; 
 scalar_t__ NO_HINT ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  disp_propget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ ) ; 
 scalar_t__ is_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_call (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_get_id (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_null () ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

HRESULT to_primitive(script_ctx_t *ctx, jsval_t val, jsval_t *ret, hint_t hint)
{
    if(is_object_instance(val)) {
        jsdisp_t *jsdisp;
        jsval_t prim;
        DISPID id;
        HRESULT hres;

        static const WCHAR toStringW[] = {'t','o','S','t','r','i','n','g',0};
        static const WCHAR valueOfW[] = {'v','a','l','u','e','O','f',0};

        if(!get_object(val)) {
            *ret = jsval_null();
            return S_OK;
        }

        jsdisp = iface_to_jsdisp(get_object(val));
        if(!jsdisp)
            return disp_propget(ctx, get_object(val), DISPID_VALUE, ret);

        if(hint == NO_HINT)
            hint = is_class(jsdisp, JSCLASS_DATE) ? HINT_STRING : HINT_NUMBER;

        /* Native implementation doesn't throw TypeErrors, returns strange values */

        hres = jsdisp_get_id(jsdisp, hint == HINT_STRING ? toStringW : valueOfW, 0, &id);
        if(SUCCEEDED(hres)) {
            hres = jsdisp_call(jsdisp, id, DISPATCH_METHOD, 0, NULL, &prim);
            if(FAILED(hres)) {
                WARN("call error - forwarding exception\n");
                jsdisp_release(jsdisp);
                return hres;
            }else if(!is_object_instance(prim)) {
                jsdisp_release(jsdisp);
                *ret = prim;
                return S_OK;
            }else {
                IDispatch_Release(get_object(prim));
            }
        }

        hres = jsdisp_get_id(jsdisp, hint == HINT_STRING ? valueOfW : toStringW, 0, &id);
        if(SUCCEEDED(hres)) {
            hres = jsdisp_call(jsdisp, id, DISPATCH_METHOD, 0, NULL, &prim);
            if(FAILED(hres)) {
                WARN("call error - forwarding exception\n");
                jsdisp_release(jsdisp);
                return hres;
            }else if(!is_object_instance(prim)) {
                jsdisp_release(jsdisp);
                *ret = prim;
                return S_OK;
            }else {
                IDispatch_Release(get_object(prim));
            }
        }

        jsdisp_release(jsdisp);

        WARN("failed\n");
        return throw_type_error(ctx, JS_E_TO_PRIMITIVE, NULL);
    }

    return jsval_copy(val, ret);

}