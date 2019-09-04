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
struct TYPE_9__ {int version; scalar_t__ global; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  ActiveXObjectW ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INFINITY ; 
 int /*<<< orphan*/  InfinityW ; 
 int /*<<< orphan*/  JSGlobal_info ; 
 int /*<<< orphan*/  JSONW ; 
 int /*<<< orphan*/  MathW ; 
 int /*<<< orphan*/  NAN ; 
 int /*<<< orphan*/  NaNW ; 
 unsigned int PROPF_WRITABLE ; 
 int SCRIPTLANGUAGEVERSION_ES5 ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  create_activex_constr (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  create_dispex (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  create_json (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  create_math (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  create_object_prototype (TYPE_1__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  init_constructors (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_define_data_property (scalar_t__,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/  undefinedW ; 

HRESULT init_global(script_ctx_t *ctx)
{
    unsigned const_flags = ctx->version >= SCRIPTLANGUAGEVERSION_ES5 ? 0 : PROPF_WRITABLE;
    jsdisp_t *math, *object_prototype, *constr;
    HRESULT hres;

    if(ctx->global)
        return S_OK;

    hres = create_dispex(ctx, &JSGlobal_info, NULL, &ctx->global);
    if(FAILED(hres))
        return hres;

    hres = create_object_prototype(ctx, &object_prototype);
    if(FAILED(hres))
        return hres;

    hres = init_constructors(ctx, object_prototype);
    jsdisp_release(object_prototype);
    if(FAILED(hres))
        return hres;

    hres = create_math(ctx, &math);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, MathW, PROPF_WRITABLE, jsval_obj(math));
    jsdisp_release(math);
    if(FAILED(hres))
        return hres;

    if(ctx->version >= 2) {
        jsdisp_t *json;

        hres = create_json(ctx, &json);
        if(FAILED(hres))
            return hres;

        hres = jsdisp_define_data_property(ctx->global, JSONW, PROPF_WRITABLE, jsval_obj(json));
        jsdisp_release(json);
        if(FAILED(hres))
            return hres;
    }

    hres = create_activex_constr(ctx, &constr);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, ActiveXObjectW, PROPF_WRITABLE,
                                       jsval_obj(constr));
    jsdisp_release(constr);
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, undefinedW, const_flags, jsval_undefined());
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, NaNW, const_flags, jsval_number(NAN));
    if(FAILED(hres))
        return hres;

    hres = jsdisp_define_data_property(ctx->global, InfinityW, const_flags, jsval_number(INFINITY));
    return hres;
}