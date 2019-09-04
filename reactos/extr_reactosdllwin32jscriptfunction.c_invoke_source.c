#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ state; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_8__ {int /*<<< orphan*/  dispex; int /*<<< orphan*/  scope_chain; int /*<<< orphan*/  func_code; int /*<<< orphan*/  code; } ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ FunctionInstance ;
typedef  int /*<<< orphan*/  DWORD ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  EXEC_CONSTRUCTOR ; 
 int /*<<< orphan*/  EXEC_RETURN_TO_INTERP ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_UNEXPECTED ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ SCRIPTSTATE_CLOSED ; 
 scalar_t__ SCRIPTSTATE_UNINITIALIZED ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  create_dispex (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  exec_source (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT invoke_source(script_ctx_t *ctx, FunctionInstance *function, IDispatch *this_obj, unsigned argc, jsval_t *argv,
        BOOL is_constructor, BOOL caller_execs_source, jsval_t *r)
{
    jsdisp_t *var_disp;
    DWORD exec_flags = 0;
    HRESULT hres;

    if(ctx->state == SCRIPTSTATE_UNINITIALIZED || ctx->state == SCRIPTSTATE_CLOSED) {
        WARN("Script engine state does not allow running code.\n");
        return E_UNEXPECTED;
    }

    if(!function->func_code) {
        FIXME("no source\n");
        return E_FAIL;
    }

    hres = create_dispex(ctx, NULL, NULL, &var_disp);
    if(FAILED(hres))
        return hres;

    if(caller_execs_source)
        exec_flags |= EXEC_RETURN_TO_INTERP;
    if(is_constructor)
        exec_flags |= EXEC_CONSTRUCTOR;
    hres = exec_source(ctx, exec_flags, function->code, function->func_code, function->scope_chain, this_obj,
            &function->dispex, var_disp, argc, argv, r);

    jsdisp_release(var_disp);
    return hres;
}