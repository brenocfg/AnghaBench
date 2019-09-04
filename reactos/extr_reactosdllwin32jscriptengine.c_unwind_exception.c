#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  val; } ;
struct TYPE_17__ {scalar_t__ stack_top; TYPE_3__ ei; TYPE_6__* call_ctx; } ;
typedef  TYPE_4__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_18__ {unsigned int catch_off; scalar_t__ stack_top; scalar_t__ scope; unsigned int finally_off; struct TYPE_18__* next; } ;
typedef  TYPE_5__ except_frame_t ;
struct TYPE_19__ {scalar_t__ scope; scalar_t__ base_scope; scalar_t__ stack_base; int flags; unsigned int ip; TYPE_5__* except_frame; TYPE_2__* bytecode; } ;
typedef  TYPE_6__ call_frame_t ;
typedef  char WCHAR ;
struct TYPE_15__ {TYPE_1__* instrs; } ;
struct TYPE_14__ {scalar_t__ op; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 int EXEC_RETURN_TO_INTERP ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ JSV_OBJECT ; 
 scalar_t__ OP_enter_catch ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN (char*,...) ; 
 scalar_t__ WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  clear_ei (TYPE_4__*) ; 
 int /*<<< orphan*/  debugstr_jsval (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (TYPE_5__*) ; 
 int /*<<< orphan*/  jscript ; 
 int /*<<< orphan*/  jsdisp_propget_name (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_bool (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 scalar_t__ jsval_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 int /*<<< orphan*/  pop_call_frame (TYPE_4__*) ; 
 int /*<<< orphan*/  print_backtrace (TYPE_4__*) ; 
 int /*<<< orphan*/  scope_pop (scalar_t__*) ; 
 int /*<<< orphan*/  stack_popn (TYPE_4__*,scalar_t__) ; 
 int /*<<< orphan*/  stack_push (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * to_jsdisp (int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT unwind_exception(script_ctx_t *ctx, HRESULT exception_hres)
{
    except_frame_t *except_frame;
    call_frame_t *frame;
    jsval_t except_val;
    unsigned catch_off;
    HRESULT hres;

    if(WARN_ON(jscript)) {
        jsdisp_t *error_obj;
        jsval_t msg;

        static const WCHAR messageW[] = {'m','e','s','s','a','g','e',0};

        WARN("Exception %08x %s", exception_hres, debugstr_jsval(ctx->ei.val));
        if(jsval_type(ctx->ei.val) == JSV_OBJECT) {
            error_obj = to_jsdisp(get_object(ctx->ei.val));
            if(error_obj) {
                hres = jsdisp_propget_name(error_obj, messageW, &msg);
                if(SUCCEEDED(hres)) {
                    WARN(" (message %s)", debugstr_jsval(msg));
                    jsval_release(msg);
                }
            }
        }
        WARN(" in:\n");

        print_backtrace(ctx);
    }

    for(frame = ctx->call_ctx; !frame->except_frame; frame = ctx->call_ctx) {
        DWORD flags;

        while(frame->scope != frame->base_scope)
            scope_pop(&frame->scope);

        stack_popn(ctx, ctx->stack_top-frame->stack_base);

        flags = frame->flags;
        pop_call_frame(ctx);
        if(!(flags & EXEC_RETURN_TO_INTERP))
            return exception_hres;
    }

    except_frame = frame->except_frame;
    catch_off = except_frame->catch_off;

    assert(except_frame->stack_top <= ctx->stack_top);
    stack_popn(ctx, ctx->stack_top - except_frame->stack_top);

    while(except_frame->scope != frame->scope)
        scope_pop(&frame->scope);

    frame->ip = catch_off ? catch_off : except_frame->finally_off;
    if(catch_off) assert(frame->bytecode->instrs[frame->ip].op == OP_enter_catch);

    except_val = ctx->ei.val;
    ctx->ei.val = jsval_undefined();
    clear_ei(ctx);

    /* keep current except_frame if we're entering catch block with finally block associated */
    if(catch_off && except_frame->finally_off) {
        except_frame->catch_off = 0;
    }else {
        frame->except_frame = except_frame->next;
        heap_free(except_frame);
    }

    hres = stack_push(ctx, except_val);
    if(FAILED(hres))
        return hres;

    if(!catch_off)
        hres = stack_push(ctx, jsval_bool(FALSE));
    return hres;
}