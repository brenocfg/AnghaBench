#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_8__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
struct TYPE_9__ {int /*<<< orphan*/  tmp_heap; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  match_state_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_11__ {int flags; } ;
struct TYPE_10__ {scalar_t__ last_index; int /*<<< orphan*/  dispex; TYPE_8__* jsregexp; } ;
typedef  TYPE_2__ RegExpInstance ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;
typedef  int BOOL ;

/* Variables and functions */
 scalar_t__ E_NOTIMPL ; 
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int FALSE ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  JSCLASS_REGEXP ; 
 int REG_GLOB ; 
 int /*<<< orphan*/  REM_RESET_INDEX ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/ * alloc_match_state (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  is_vclass (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsstr_empty () ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 TYPE_2__* regexp_from_vdisp (int /*<<< orphan*/ *) ; 
 scalar_t__ regexp_match_next (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_last_index (TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ to_flat_string (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static HRESULT run_exec(script_ctx_t *ctx, vdisp_t *jsthis, jsval_t arg,
        jsstr_t **input, match_state_t **result, BOOL *ret)
{
    RegExpInstance *regexp;
    match_state_t *match;
    DWORD last_index = 0;
    const WCHAR *string;
    jsstr_t *jsstr;
    HRESULT hres;

    if(!is_vclass(jsthis, JSCLASS_REGEXP)) {
        FIXME("Not a RegExp\n");
        return E_NOTIMPL;
    }

    regexp = regexp_from_vdisp(jsthis);

    hres = to_flat_string(ctx, arg, &jsstr, &string);
    if(FAILED(hres))
        return hres;

    if(regexp->jsregexp->flags & REG_GLOB) {
        if(regexp->last_index < 0) {
            jsstr_release(jsstr);
            set_last_index(regexp, 0);
            *ret = FALSE;
            if(input)
                *input = jsstr_empty();
            return S_OK;
        }

        last_index = regexp->last_index;
    }

    match = alloc_match_state(regexp->jsregexp, &ctx->tmp_heap, string+last_index);
    if(!match) {
        jsstr_release(jsstr);
        return E_OUTOFMEMORY;
    }

    hres = regexp_match_next(ctx, &regexp->dispex, REM_RESET_INDEX, jsstr, &match);
    if(FAILED(hres)) {
        jsstr_release(jsstr);
        return hres;
    }

    *result = match;
    *ret = hres == S_OK;
    if(input)
        *input = jsstr;
    else
        jsstr_release(jsstr);
    return S_OK;
}