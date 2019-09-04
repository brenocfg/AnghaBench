#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_16__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  tmp_heap; } ;
typedef  TYPE_1__ script_ctx_t ;
struct TYPE_19__ {int match_len; int /*<<< orphan*/  const* cp; } ;
typedef  TYPE_2__ match_state_t ;
struct TYPE_20__ {int index; int length; } ;
typedef  TYPE_3__ match_result_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  heap_pool_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_21__ {TYPE_16__* jsregexp; } ;
struct TYPE_17__ {int flags; } ;
typedef  TYPE_4__ RegExpInstance ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int REG_GLOB ; 
 scalar_t__ S_FALSE ; 
 scalar_t__ S_OK ; 
 TYPE_2__* alloc_match_state (TYPE_16__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 scalar_t__ do_regexp_match_next (TYPE_1__*,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/  const*,TYPE_2__*) ; 
 TYPE_3__* heap_alloc (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_3__*) ; 
 int /*<<< orphan*/  heap_pool_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * heap_pool_mark (int /*<<< orphan*/ *) ; 
 TYPE_3__* heap_realloc (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * jsstr_flatten (int /*<<< orphan*/ *) ; 
 TYPE_4__* regexp_from_jsdisp (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT regexp_match(script_ctx_t *ctx, jsdisp_t *dispex, jsstr_t *jsstr, BOOL gflag,
        match_result_t **match_result, DWORD *result_cnt)
{
    RegExpInstance *This = regexp_from_jsdisp(dispex);
    match_result_t *ret = NULL;
    match_state_t *result;
    DWORD i=0, ret_size = 0;
    heap_pool_t *mark;
    const WCHAR *str;
    HRESULT hres;

    mark = heap_pool_mark(&ctx->tmp_heap);

    str = jsstr_flatten(jsstr);
    if(!str)
        return E_OUTOFMEMORY;

    result = alloc_match_state(This->jsregexp, &ctx->tmp_heap, str);
    if(!result) {
        heap_pool_clear(mark);
        return E_OUTOFMEMORY;
    }

    while(1) {
        hres = do_regexp_match_next(ctx, This, 0, jsstr, str, result);
        if(hres == S_FALSE) {
            hres = S_OK;
            break;
        }

        if(FAILED(hres))
            break;

        if(ret_size == i) {
            if(ret) {
                match_result_t *old_ret = ret;

                ret = heap_realloc(old_ret, (ret_size <<= 1) * sizeof(match_result_t));
                if(!ret)
                    heap_free(old_ret);
            }else {
                ret = heap_alloc((ret_size=4) * sizeof(match_result_t));
            }
            if(!ret) {
                hres = E_OUTOFMEMORY;
                break;
            }
        }

        ret[i].index = result->cp - str - result->match_len;
        ret[i++].length = result->match_len;

        if(!gflag && !(This->jsregexp->flags & REG_GLOB)) {
            hres = S_OK;
            break;
        }
    }

    heap_pool_clear(mark);
    if(FAILED(hres)) {
        heap_free(ret);
        return hres;
    }

    *match_result = ret;
    *result_cnt = i;
    return S_OK;
}