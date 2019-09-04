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
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int WORD ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  FunctionInstance ;

/* Variables and functions */
 int DISPATCH_JSCRIPT_CALLEREXECSSOURCE ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDispatch_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JS_E_FUNCTION_EXPECTED ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  call_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * function_this (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  throw_type_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT Function_call(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    FunctionInstance *function;
    IDispatch *this_obj = NULL;
    unsigned cnt = 0;
    HRESULT hres;

    TRACE("\n");

    if(!(function = function_this(jsthis)))
        return throw_type_error(ctx, JS_E_FUNCTION_EXPECTED, NULL);

    if(argc) {
        if(!is_undefined(argv[0]) && !is_null(argv[0])) {
            hres = to_object(ctx, argv[0], &this_obj);
            if(FAILED(hres))
                return hres;
        }

        cnt = argc-1;
    }

    hres = call_function(ctx, function, this_obj, cnt, argv+1, (flags & DISPATCH_JSCRIPT_CALLEREXECSSOURCE) != 0, r);

    if(this_obj)
        IDispatch_Release(this_obj);
    return hres;
}