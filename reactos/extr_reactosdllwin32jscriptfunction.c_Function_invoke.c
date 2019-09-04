#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int WORD ;
struct TYPE_7__ {int /*<<< orphan*/  ctx; } ;
struct TYPE_6__ {TYPE_5__ dispex; scalar_t__ value_proc; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ FunctionInstance ;
typedef  int BOOL ;

/* Variables and functions */
 int DISPATCH_CONSTRUCT ; 
 int DISPATCH_JSCRIPT_CALLEREXECSSOURCE ; 
 int DISPATCH_JSCRIPT_INTERNAL_MASK ; 
 int DISPATCH_METHOD ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  JSCLASS_FUNCTION ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  create_object (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ **) ; 
 TYPE_1__* function_from_jsdisp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  invoke_source (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  invoke_value_proc (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int is_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * to_disp (int /*<<< orphan*/ *) ; 

HRESULT Function_invoke(jsdisp_t *func_this, IDispatch *jsthis, WORD flags, unsigned argc, jsval_t *argv, jsval_t *r)
{
    const BOOL caller_execs_source = (flags & DISPATCH_JSCRIPT_CALLEREXECSSOURCE) != 0;
    FunctionInstance *function;

    TRACE("func %p this %p\n", func_this, jsthis);

    assert(is_class(func_this, JSCLASS_FUNCTION));
    function = function_from_jsdisp(func_this);

    flags &= ~DISPATCH_JSCRIPT_INTERNAL_MASK;
    if(function->value_proc)
        return invoke_value_proc(function->dispex.ctx, function, jsthis, flags, argc, argv, r);

    if(flags == DISPATCH_CONSTRUCT) {
        jsdisp_t *this_obj;
        HRESULT hres;

        hres = create_object(function->dispex.ctx, &function->dispex, &this_obj);
        if(FAILED(hres))
            return hres;

        hres = invoke_source(function->dispex.ctx, function, to_disp(this_obj), argc, argv, TRUE, caller_execs_source, r);
        jsdisp_release(this_obj);
        return hres;
    }

    assert(flags == DISPATCH_METHOD);
    return invoke_source(function->dispex.ctx, function, jsthis, argc, argv, FALSE, caller_execs_source, r);
}