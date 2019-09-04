#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {size_t buf_len; unsigned int stack_top; scalar_t__* gap; } ;
typedef  TYPE_1__ stringify_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_16__ {int /*<<< orphan*/  IDispatchEx_iface; } ;
typedef  TYPE_2__ jsdisp_t ;
typedef  scalar_t__ HRESULT ;
typedef  int /*<<< orphan*/  DISPID ;
typedef  int /*<<< orphan*/  BSTR ;

/* Variables and functions */
 int /*<<< orphan*/  DISPID_STARTENUM ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ IDispatchEx_GetMemberName (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ IDispatchEx_GetNextDispID (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  SysFreeString (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SysStringLen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  append_char (TYPE_1__*,char) ; 
 int /*<<< orphan*/  append_string (TYPE_1__*,scalar_t__*) ; 
 int /*<<< orphan*/  fdexEnumDefault ; 
 scalar_t__ is_on_stack (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ is_undefined (int /*<<< orphan*/ ) ; 
 scalar_t__ jsdisp_propget (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ json_quote (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 scalar_t__ stringify (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stringify_pop_obj (TYPE_1__*) ; 
 int /*<<< orphan*/  stringify_push_obj (TYPE_1__*,TYPE_2__*) ; 

__attribute__((used)) static HRESULT stringify_object(stringify_ctx_t *ctx, jsdisp_t *obj)
{
    DISPID dispid = DISPID_STARTENUM;
    jsval_t val = jsval_undefined();
    unsigned prop_cnt = 0, i;
    size_t stepback;
    BSTR prop_name;
    HRESULT hres;

    if(is_on_stack(ctx, obj)) {
        FIXME("Found a cycle\n");
        return E_FAIL;
    }

    if(!stringify_push_obj(ctx, obj))
        return E_OUTOFMEMORY;

    if(!append_char(ctx, '{'))
        return E_OUTOFMEMORY;

    while((hres = IDispatchEx_GetNextDispID(&obj->IDispatchEx_iface, fdexEnumDefault, dispid, &dispid)) == S_OK) {
        jsval_release(val);
        hres = jsdisp_propget(obj, dispid, &val);
        if(FAILED(hres))
            return hres;

        if(is_undefined(val))
            continue;

        stepback = ctx->buf_len;

        if(prop_cnt && !append_char(ctx, ',')) {
            hres = E_OUTOFMEMORY;
            break;
        }

        if(*ctx->gap) {
            if(!append_char(ctx, '\n')) {
                hres = E_OUTOFMEMORY;
                break;
            }

            for(i=0; i < ctx->stack_top; i++) {
                if(!append_string(ctx, ctx->gap)) {
                    hres = E_OUTOFMEMORY;
                    break;
                }
            }
        }

        hres = IDispatchEx_GetMemberName(&obj->IDispatchEx_iface, dispid, &prop_name);
        if(FAILED(hres))
            break;

        hres = json_quote(ctx, prop_name, SysStringLen(prop_name));
        SysFreeString(prop_name);
        if(FAILED(hres))
            break;

        if(!append_char(ctx, ':') || (*ctx->gap && !append_char(ctx, ' '))) {
            hres = E_OUTOFMEMORY;
            break;
        }

        hres = stringify(ctx, val);
        if(FAILED(hres))
            break;

        if(hres == S_FALSE) {
            ctx->buf_len = stepback;
            continue;
        }

        prop_cnt++;
    }
    jsval_release(val);
    if(FAILED(hres))
        return hres;

    if(prop_cnt && *ctx->gap) {
        if(!append_char(ctx, '\n'))
            return E_OUTOFMEMORY;

        for(i=1; i < ctx->stack_top; i++) {
            if(!append_string(ctx, ctx->gap)) {
                hres = E_OUTOFMEMORY;
                break;
            }
        }
    }

    if(!append_char(ctx, '}'))
        return E_OUTOFMEMORY;

    stringify_pop_obj(ctx);
    return S_OK;
}