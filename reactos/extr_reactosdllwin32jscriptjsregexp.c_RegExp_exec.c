#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
struct TYPE_5__ {int /*<<< orphan*/  tmp_heap; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  match_state_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  heap_pool_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ BOOL ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  create_match_array (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  heap_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_pool_mark (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_empty () ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_disp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_null () ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  run_exec (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **,scalar_t__*) ; 

__attribute__((used)) static HRESULT RegExp_exec(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    match_state_t *match;
    heap_pool_t *mark;
    BOOL b;
    jsstr_t *string;
    HRESULT hres;

    TRACE("\n");

    mark = heap_pool_mark(&ctx->tmp_heap);

    hres = run_exec(ctx, jsthis, argc ? argv[0] : jsval_string(jsstr_empty()), &string, &match, &b);
    if(FAILED(hres)) {
        heap_pool_clear(mark);
        return hres;
    }

    if(r) {
        if(b) {
            IDispatch *ret;

            hres = create_match_array(ctx, string, match, &ret);
            if(SUCCEEDED(hres))
                *r = jsval_disp(ret);
        }else {
            *r = jsval_null();
        }
    }

    heap_pool_clear(mark);
    jsstr_release(string);
    return hres;
}