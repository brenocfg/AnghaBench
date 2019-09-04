#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  object_constr; } ;
typedef  TYPE_2__ script_ctx_t ;
struct TYPE_14__ {int /*<<< orphan*/ * arguments_obj; TYPE_1__* base_scope; int /*<<< orphan*/  argc; int /*<<< orphan*/  function_instance; } ;
typedef  TYPE_3__ call_frame_t ;
typedef  char WCHAR ;
struct TYPE_15__ {int /*<<< orphan*/  jsdisp; TYPE_10__* function; int /*<<< orphan*/  argc; TYPE_3__* frame; } ;
struct TYPE_12__ {int /*<<< orphan*/  jsobj; } ;
struct TYPE_11__ {int /*<<< orphan*/  dispex; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ ArgumentsInstance ;

/* Variables and functions */
 int /*<<< orphan*/  Arguments_info ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int PROPF_CONFIGURABLE ; 
 int PROPF_WRITABLE ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  argumentsW ; 
 TYPE_10__* function_from_jsdisp (int /*<<< orphan*/ ) ; 
 TYPE_4__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_4__*) ; 
 int /*<<< orphan*/  init_dispex_from_constr (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_addref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_define_data_property (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_propput (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 char const* lengthW ; 

HRESULT setup_arguments_object(script_ctx_t *ctx, call_frame_t *frame)
{
    ArgumentsInstance *args;
    HRESULT hres;

    static const WCHAR caleeW[] = {'c','a','l','l','e','e',0};

    args = heap_alloc_zero(sizeof(*args));
    if(!args)
        return E_OUTOFMEMORY;

    hres = init_dispex_from_constr(&args->jsdisp, ctx, &Arguments_info, ctx->object_constr);
    if(FAILED(hres)) {
        heap_free(args);
        return hres;
    }

    args->function = function_from_jsdisp(jsdisp_addref(frame->function_instance));
    args->argc = frame->argc;
    args->frame = frame;

    hres = jsdisp_define_data_property(&args->jsdisp, lengthW, PROPF_WRITABLE | PROPF_CONFIGURABLE,
                                       jsval_number(args->argc));
    if(SUCCEEDED(hres))
        hres = jsdisp_define_data_property(&args->jsdisp, caleeW, PROPF_WRITABLE | PROPF_CONFIGURABLE,
                                           jsval_obj(&args->function->dispex));
    if(SUCCEEDED(hres))
        hres = jsdisp_propput(frame->base_scope->jsobj, argumentsW, PROPF_WRITABLE, jsval_obj(&args->jsdisp));
    if(FAILED(hres)) {
        jsdisp_release(&args->jsdisp);
        return hres;
    }

    frame->arguments_obj = &args->jsdisp;
    return S_OK;
}