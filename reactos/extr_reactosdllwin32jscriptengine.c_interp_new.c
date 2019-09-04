#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  acc; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int DISPATCH_CONSTRUCT ; 
 int DISPATCH_JSCRIPT_CALLEREXECSSOURCE ; 
 int /*<<< orphan*/  JS_E_INVALID_ACTION ; 
 int /*<<< orphan*/  JS_E_INVALID_PROPERTY ; 
 int /*<<< orphan*/  JS_E_OBJECT_EXPECTED ; 
 int /*<<< orphan*/  TRACE (char*,unsigned int const) ; 
 int /*<<< orphan*/  clear_acc (TYPE_1__*) ; 
 int /*<<< orphan*/  disp_call_value (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 unsigned int get_op_uint (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_null (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stack_args (TYPE_1__*,unsigned int const) ; 
 int /*<<< orphan*/  stack_topn (TYPE_1__*,unsigned int const) ; 
 int /*<<< orphan*/  throw_type_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT interp_new(script_ctx_t *ctx)
{
    const unsigned argc = get_op_uint(ctx, 0);
    jsval_t constr;

    TRACE("%d\n", argc);

    constr = stack_topn(ctx, argc);

    /* NOTE: Should use to_object here */

    if(is_null(constr))
        return throw_type_error(ctx, JS_E_OBJECT_EXPECTED, NULL);
    else if(!is_object_instance(constr))
        return throw_type_error(ctx, JS_E_INVALID_ACTION, NULL);
    else if(!get_object(constr))
        return throw_type_error(ctx, JS_E_INVALID_PROPERTY, NULL);

    clear_acc(ctx);
    return disp_call_value(ctx, get_object(constr), NULL, DISPATCH_CONSTRUCT | DISPATCH_JSCRIPT_CALLEREXECSSOURCE,
                           argc, stack_args(ctx, argc), &ctx->acc);
}