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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  scope_chain_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_5__ {int /*<<< orphan*/  param_cnt; } ;
typedef  TYPE_1__ function_code_t ;
typedef  int /*<<< orphan*/  bytecode_t ;
struct TYPE_6__ {int /*<<< orphan*/  dispex; TYPE_1__* func_code; int /*<<< orphan*/  length; int /*<<< orphan*/ * code; int /*<<< orphan*/ * scope_chain; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ FunctionInstance ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  PROPF_CONSTR ; 
 int /*<<< orphan*/  PROPF_WRITABLE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  bytecode_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_function (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  create_object (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsdisp_define_data_property (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  prototypeW ; 
 int /*<<< orphan*/  scope_addref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_constructor_prop (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT create_source_function(script_ctx_t *ctx, bytecode_t *code, function_code_t *func_code,
        scope_chain_t *scope_chain, jsdisp_t **ret)
{
    FunctionInstance *function;
    jsdisp_t *prototype;
    HRESULT hres;

    hres = create_object(ctx, NULL, &prototype);
    if(FAILED(hres))
        return hres;

    hres = create_function(ctx, NULL, PROPF_CONSTR, FALSE, NULL, &function);
    if(SUCCEEDED(hres)) {
        hres = jsdisp_define_data_property(&function->dispex, prototypeW, PROPF_WRITABLE,
                                           jsval_obj(prototype));
        if(SUCCEEDED(hres))
            hres = set_constructor_prop(ctx, &function->dispex, prototype);
        if(FAILED(hres))
            jsdisp_release(&function->dispex);
    }
    jsdisp_release(prototype);
    if(FAILED(hres))
        return hres;

    if(scope_chain) {
        scope_addref(scope_chain);
        function->scope_chain = scope_chain;
    }

    bytecode_addref(code);
    function->code = code;
    function->func_code = func_code;
    function->length = function->func_code->param_cnt;

    *ret = &function->dispex;
    return S_OK;
}