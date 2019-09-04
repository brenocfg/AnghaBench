#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_7__ {struct TYPE_7__* prototype; } ;
typedef  TYPE_1__ jsdisp_t ;
typedef  char WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JSCLASS_FUNCTION ; 
 int /*<<< orphan*/  JS_E_FUNCTION_EXPECTED ; 
 int /*<<< orphan*/  disp_cmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 TYPE_1__* iface_to_jsdisp (int /*<<< orphan*/ ) ; 
 scalar_t__ is_class (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_propget_name (TYPE_1__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_release (TYPE_1__*) ; 
 int /*<<< orphan*/  jsval_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stack_push (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_disp (TYPE_1__*) ; 

__attribute__((used)) static HRESULT interp_instanceof(script_ctx_t *ctx)
{
    jsdisp_t *obj, *iter, *tmp = NULL;
    jsval_t prot, v;
    BOOL ret = FALSE;
    HRESULT hres;

    static const WCHAR prototypeW[] = {'p','r','o','t','o','t', 'y', 'p','e',0};

    v = stack_pop(ctx);
    if(!is_object_instance(v) || !get_object(v)) {
        jsval_release(v);
        return throw_type_error(ctx, JS_E_FUNCTION_EXPECTED, NULL);
    }

    obj = iface_to_jsdisp(get_object(v));
    IDispatch_Release(get_object(v));
    if(!obj) {
        FIXME("non-jsdisp objects not supported\n");
        return E_FAIL;
    }

    if(is_class(obj, JSCLASS_FUNCTION)) {
        hres = jsdisp_propget_name(obj, prototypeW, &prot);
    }else {
        hres = throw_type_error(ctx, JS_E_FUNCTION_EXPECTED, NULL);
    }
    jsdisp_release(obj);
    if(FAILED(hres))
        return hres;

    v = stack_pop(ctx);

    if(is_object_instance(prot)) {
        if(is_object_instance(v))
            tmp = iface_to_jsdisp(get_object(v));
        for(iter = tmp; !ret && iter; iter = iter->prototype) {
            hres = disp_cmp(get_object(prot), to_disp(iter), &ret);
            if(FAILED(hres))
                break;
        }

        if(tmp)
            jsdisp_release(tmp);
    }else {
        FIXME("prototype is not an object\n");
        hres = E_FAIL;
    }

    jsval_release(prot);
    jsval_release(v);
    if(FAILED(hres))
        return hres;

    return stack_push(ctx, jsval_bool(ret));
}