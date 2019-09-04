#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_8__* call_ctx; } ;
typedef  TYPE_6__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
struct TYPE_16__ {void* id; int /*<<< orphan*/  disp; } ;
struct TYPE_17__ {unsigned int off; void* hres; TYPE_4__ idref; } ;
struct TYPE_19__ {TYPE_5__ u; void* type; } ;
typedef  TYPE_7__ exprval_t ;
struct TYPE_20__ {unsigned int arguments_off; unsigned int variables_off; TYPE_3__* base_scope; TYPE_2__* function; } ;
typedef  TYPE_8__ call_frame_t ;
struct TYPE_15__ {int /*<<< orphan*/  obj; int /*<<< orphan*/  jsobj; int /*<<< orphan*/  frame; } ;
struct TYPE_14__ {unsigned int var_cnt; int /*<<< orphan*/ * params; TYPE_1__* variables; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
typedef  void* HRESULT ;
typedef  void* DISPID ;
typedef  int /*<<< orphan*/  BSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 void* EXPRVAL_IDREF ; 
 void* EXPRVAL_INVALID ; 
 void* EXPRVAL_STACK_REF ; 
 int /*<<< orphan*/  FAILED (void*) ; 
 int /*<<< orphan*/  FALSE ; 
#define  JSV_NUMBER 130 
#define  JSV_OBJECT 129 
#define  JSV_UNDEFINED 128 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 void* get_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int is_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_addref (int /*<<< orphan*/ ) ; 
 void* jsdisp_get_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  jsval_number (void*) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ ) ; 
 int jsval_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * stack_top_ref (TYPE_6__*,unsigned int) ; 
 int /*<<< orphan*/  stack_topn (TYPE_6__*,unsigned int) ; 

__attribute__((used)) static BOOL stack_topn_exprval(script_ctx_t *ctx, unsigned n, exprval_t *r)
{
    jsval_t v = stack_topn(ctx, n+1);

    switch(jsval_type(v)) {
    case JSV_NUMBER: {
        call_frame_t *frame = ctx->call_ctx;
        unsigned off = get_number(v);

        if(!frame->base_scope->frame && off >= frame->arguments_off) {
            DISPID id;
            BSTR name;
            HRESULT hres;

            /* Got stack reference in deoptimized code. Need to convert it back to variable object reference. */

            assert(off < frame->variables_off + frame->function->var_cnt);
            name = off >= frame->variables_off
                ? frame->function->variables[off - frame->variables_off].name
                : frame->function->params[off - frame->arguments_off];
            hres = jsdisp_get_id(ctx->call_ctx->base_scope->jsobj, name, 0, &id);
            if(FAILED(hres)) {
                r->type = EXPRVAL_INVALID;
                r->u.hres = hres;
                return FALSE;
            }

            *stack_top_ref(ctx, n+1) = jsval_obj(jsdisp_addref(frame->base_scope->jsobj));
            *stack_top_ref(ctx, n) = jsval_number(id);
            r->type = EXPRVAL_IDREF;
            r->u.idref.disp = frame->base_scope->obj;
            r->u.idref.id = id;
            return TRUE;
        }

        r->type = EXPRVAL_STACK_REF;
        r->u.off = off;
        return TRUE;
    }
    case JSV_OBJECT:
        r->type = EXPRVAL_IDREF;
        r->u.idref.disp = get_object(v);
        assert(is_number(stack_topn(ctx, n)));
        r->u.idref.id = get_number(stack_topn(ctx, n));
        return TRUE;
    case JSV_UNDEFINED:
        r->type = EXPRVAL_INVALID;
        assert(is_number(stack_topn(ctx, n)));
        r->u.hres = get_number(stack_topn(ctx, n));
        return FALSE;
    default:
        assert(0);
        return FALSE;
    }
}