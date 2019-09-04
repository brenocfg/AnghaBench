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
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  JSCLASS_BOOLEAN ; 
 int /*<<< orphan*/  JSCLASS_NUMBER ; 
 int /*<<< orphan*/  JSCLASS_STRING ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  bool_obj_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ ) ; 
 scalar_t__ is_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (double) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT maybe_to_primitive(script_ctx_t *ctx, jsval_t val, jsval_t *r)
{
    jsdisp_t *obj;
    HRESULT hres;

    if(!is_object_instance(val) || !get_object(val) || !(obj = iface_to_jsdisp(get_object(val))))
        return jsval_copy(val, r);

    if(is_class(obj, JSCLASS_NUMBER)) {
        double n;
        hres = to_number(ctx, val, &n);
        jsdisp_release(obj);
        if(SUCCEEDED(hres))
            *r = jsval_number(n);
        return hres;
    }

    if(is_class(obj, JSCLASS_STRING)) {
        jsstr_t *str;
        hres = to_string(ctx, val, &str);
        jsdisp_release(obj);
        if(SUCCEEDED(hres))
            *r = jsval_string(str);
        return hres;
    }

    if(is_class(obj, JSCLASS_BOOLEAN)) {
        *r = jsval_bool(bool_obj_value(obj));
        jsdisp_release(obj);
        return S_OK;
    }

    *r = jsval_obj(obj);
    return S_OK;
}