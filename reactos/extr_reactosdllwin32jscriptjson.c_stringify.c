#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  ctx; } ;
typedef  TYPE_1__ stringify_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  JSCLASS_ARRAY ; 
#define  JSV_BOOL 134 
#define  JSV_NULL 133 
#define  JSV_NUMBER 132 
#define  JSV_OBJECT 131 
#define  JSV_STRING 130 
#define  JSV_UNDEFINED 129 
#define  JSV_VARIANT 128 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  append_string (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_string_len (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ double_to_string (double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  falseW ; 
 int /*<<< orphan*/  get_bool (int /*<<< orphan*/ ) ; 
 double get_number (int /*<<< orphan*/ ) ; 
 scalar_t__ get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (scalar_t__) ; 
 int /*<<< orphan*/  is_callable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_finite (double) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 scalar_t__ jsdisp_get_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 scalar_t__ json_quote (TYPE_1__*,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsstr_flatten (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int jsval_type (int /*<<< orphan*/ ) ; 
 scalar_t__ maybe_to_primitive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nullW ; 
 scalar_t__ stringify_array (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ stringify_object (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  toJSONW ; 
 int /*<<< orphan*/  trueW ; 

__attribute__((used)) static HRESULT stringify(stringify_ctx_t *ctx, jsval_t val)
{
    jsval_t value;
    HRESULT hres;

    if(is_object_instance(val) && get_object(val)) {
        jsdisp_t *obj;
        DISPID id;

        obj = iface_to_jsdisp(get_object(val));
        if(!obj)
            return S_FALSE;

        hres = jsdisp_get_id(obj, toJSONW, 0, &id);
        jsdisp_release(obj);
        if(hres == S_OK)
            FIXME("Use toJSON.\n");
    }

    /* FIXME: Support replacer replacer. */

    hres = maybe_to_primitive(ctx->ctx, val, &value);
    if(FAILED(hres))
        return hres;

    switch(jsval_type(value)) {
    case JSV_NULL:
        if(!append_string(ctx, nullW))
            hres = E_OUTOFMEMORY;
        break;
    case JSV_BOOL:
        if(!append_string(ctx, get_bool(value) ? trueW : falseW))
            hres = E_OUTOFMEMORY;
        break;
    case JSV_STRING: {
        jsstr_t *str = get_string(value);
        const WCHAR *ptr = jsstr_flatten(str);
        if(ptr)
            hres = json_quote(ctx, ptr, jsstr_length(str));
        else
            hres = E_OUTOFMEMORY;
        break;
    }
    case JSV_NUMBER: {
        double n = get_number(value);
        if(is_finite(n)) {
            const WCHAR *ptr;
            jsstr_t *str;

            /* FIXME: Optimize. There is no need for jsstr_t here. */
            hres = double_to_string(n, &str);
            if(FAILED(hres))
                break;

            ptr = jsstr_flatten(str);
            assert(ptr != NULL);
            hres = ptr && !append_string_len(ctx, ptr, jsstr_length(str)) ? E_OUTOFMEMORY : S_OK;
            jsstr_release(str);
        }else {
            if(!append_string(ctx, nullW))
                hres = E_OUTOFMEMORY;
        }
        break;
    }
    case JSV_OBJECT: {
        jsdisp_t *obj;

        obj = iface_to_jsdisp(get_object(value));
        if(!obj) {
            hres = S_FALSE;
            break;
        }

        if(!is_callable(obj))
            hres = is_class(obj, JSCLASS_ARRAY) ? stringify_array(ctx, obj) : stringify_object(ctx, obj);
        else
            hres = S_FALSE;

        jsdisp_release(obj);
        break;
    }
    case JSV_UNDEFINED:
        hres = S_FALSE;
        break;
    case JSV_VARIANT:
        FIXME("VARIANT\n");
        hres = E_NOTIMPL;
        break;
    }

    jsval_release(value);
    return hres;
}