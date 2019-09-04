#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  disp; } ;
struct TYPE_6__ {int flags; TYPE_1__ u; } ;
typedef  TYPE_2__ vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int WORD ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FunctionInstance ;

/* Variables and functions */
 int DISPATCH_JSCRIPT_CALLEREXECSSOURCE ; 
 int /*<<< orphan*/  DISPATCH_METHOD ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JSCLASS_ARGUMENTS ; 
 int /*<<< orphan*/  JSCLASS_ARRAY ; 
 int /*<<< orphan*/  JS_E_FUNCTION_EXPECTED ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int VDISP_JSDISP ; 
 int /*<<< orphan*/  array_to_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  call_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disp_call_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * function_this (TYPE_2__*) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_null (int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT Function_apply(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv, jsval_t *r)
{
    FunctionInstance *function;
    jsval_t *args = NULL;
    unsigned i, cnt = 0;
    IDispatch *this_obj = NULL;
    HRESULT hres = S_OK;

    TRACE("\n");

    if(!(function = function_this(jsthis)) && (jsthis->flags & VDISP_JSDISP))
        return throw_type_error(ctx, JS_E_FUNCTION_EXPECTED, NULL);

    if(argc) {
        if(!is_undefined(argv[0]) && !is_null(argv[0])) {
            hres = to_object(ctx, argv[0], &this_obj);
            if(FAILED(hres))
                return hres;
        }
    }

    if(argc >= 2) {
        jsdisp_t *arg_array = NULL;

        if(is_object_instance(argv[1])) {
            arg_array = iface_to_jsdisp(get_object(argv[1]));
            if(arg_array &&
               (!is_class(arg_array, JSCLASS_ARRAY) && !is_class(arg_array, JSCLASS_ARGUMENTS) )) {
                jsdisp_release(arg_array);
                arg_array = NULL;
            }
        }

        if(arg_array) {
            hres = array_to_args(ctx, arg_array, &cnt, &args);
            jsdisp_release(arg_array);
        }else {
            FIXME("throw TypeError\n");
            hres = E_FAIL;
        }
    }

    if(SUCCEEDED(hres)) {
        if(function) {
            hres = call_function(ctx, function, this_obj, cnt, args, (flags & DISPATCH_JSCRIPT_CALLEREXECSSOURCE) != 0, r);
        }else {
            jsval_t res;
            hres = disp_call_value(ctx, jsthis->u.disp, this_obj, DISPATCH_METHOD, cnt, args, &res);
            if(SUCCEEDED(hres)) {
                if(r)
                    *r = res;
                else
                    jsval_release(res);
            }
        }
    }

    if(this_obj)
        IDispatch_Release(this_obj);
    for(i=0; i < cnt; i++)
        jsval_release(args[i]);
    heap_free(args);
    return hres;
}