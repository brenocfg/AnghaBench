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
struct TYPE_9__ {unsigned int stack_top; scalar_t__* gap; } ;
typedef  TYPE_1__ stringify_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  scalar_t__ HRESULT ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ E_FAIL ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  append_char (TYPE_1__*,char) ; 
 int /*<<< orphan*/  append_string (TYPE_1__*,scalar_t__*) ; 
 unsigned int array_get_length (int /*<<< orphan*/ *) ; 
 scalar_t__ is_on_stack (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ jsdisp_get_idx (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__* nullW ; 
 scalar_t__ stringify (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stringify_pop_obj (TYPE_1__*) ; 
 int /*<<< orphan*/  stringify_push_obj (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT stringify_array(stringify_ctx_t *ctx, jsdisp_t *obj)
{
    unsigned length, i, j;
    jsval_t val;
    HRESULT hres;

    if(is_on_stack(ctx, obj)) {
        FIXME("Found a cycle\n");
        return E_FAIL;
    }

    if(!stringify_push_obj(ctx, obj))
        return E_OUTOFMEMORY;

    if(!append_char(ctx, '['))
        return E_OUTOFMEMORY;

    length = array_get_length(obj);

    for(i=0; i < length; i++) {
        if(i && !append_char(ctx, ','))
            return E_OUTOFMEMORY;

        if(*ctx->gap) {
            if(!append_char(ctx, '\n'))
                return E_OUTOFMEMORY;

            for(j=0; j < ctx->stack_top; j++) {
                if(!append_string(ctx, ctx->gap))
                    return E_OUTOFMEMORY;
            }
        }

        hres = jsdisp_get_idx(obj, i, &val);
        if(SUCCEEDED(hres)) {
            hres = stringify(ctx, val);
            if(FAILED(hres))
                return hres;
            if(hres == S_FALSE && !append_string(ctx, nullW))
                return E_OUTOFMEMORY;
        }else if(hres == DISP_E_UNKNOWNNAME) {
            if(!append_string(ctx, nullW))
                return E_OUTOFMEMORY;
        }else {
            return hres;
        }
    }

    if((length && *ctx->gap && !append_char(ctx, '\n')) || !append_char(ctx, ']'))
        return E_OUTOFMEMORY;

    stringify_pop_obj(ctx);
    return S_OK;
}