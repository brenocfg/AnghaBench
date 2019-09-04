#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
struct TYPE_5__ {int paren_count; int match_len; int /*<<< orphan*/  const* cp; TYPE_1__* parens; } ;
typedef  TYPE_2__ match_state_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WCHAR ;
struct TYPE_4__ {int index; int /*<<< orphan*/  length; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  size_t DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  DISPATCH_METHOD ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  get_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsdisp_call_value (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_alloc_len (int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * jsstr_empty () ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * jsstr_substr (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_number (int) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT rep_call(script_ctx_t *ctx, jsdisp_t *func,
        jsstr_t *jsstr, const WCHAR *str, match_state_t *match, jsstr_t **ret)
{
    jsval_t *argv;
    unsigned argc;
    jsval_t val;
    jsstr_t *tmp_str;
    DWORD i;
    HRESULT hres = S_OK;

    argc = match->paren_count+3;
    argv = heap_alloc_zero(sizeof(*argv)*argc);
    if(!argv)
        return E_OUTOFMEMORY;

    tmp_str = jsstr_alloc_len(match->cp-match->match_len, match->match_len);
    if(!tmp_str)
        hres = E_OUTOFMEMORY;
    argv[0] = jsval_string(tmp_str);

    if(SUCCEEDED(hres)) {
        for(i=0; i < match->paren_count; i++) {
            if(match->parens[i].index != -1)
                tmp_str = jsstr_substr(jsstr, match->parens[i].index, match->parens[i].length);
            else
                tmp_str = jsstr_empty();
            if(!tmp_str) {
               hres = E_OUTOFMEMORY;
               break;
            }
            argv[i+1] = jsval_string(tmp_str);
        }
    }

    if(SUCCEEDED(hres)) {
        argv[match->paren_count+1] = jsval_number(match->cp-str - match->match_len);
        argv[match->paren_count+2] = jsval_string(jsstr);
    }

    if(SUCCEEDED(hres))
        hres = jsdisp_call_value(func, NULL, DISPATCH_METHOD, argc, argv, &val);

    for(i=0; i <= match->paren_count; i++)
        jsstr_release(get_string(argv[i]));
    heap_free(argv);

    if(FAILED(hres))
        return hres;

    hres = to_string(ctx, val, ret);
    jsval_release(val);
    return hres;
}