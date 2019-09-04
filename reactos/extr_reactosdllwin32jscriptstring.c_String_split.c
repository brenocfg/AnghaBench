#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
struct TYPE_10__ {scalar_t__ version; } ;
typedef  TYPE_1__ script_ctx_t ;
struct TYPE_11__ {int /*<<< orphan*/  const* cp; int /*<<< orphan*/  const* match_len; } ;
typedef  TYPE_2__ match_state_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  const WCHAR ;
typedef  scalar_t__ HRESULT ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 scalar_t__ E_OUTOFMEMORY ; 
 scalar_t__ FAILED (scalar_t__) ; 
 int /*<<< orphan*/  JSCLASS_REGEXP ; 
 int /*<<< orphan*/  REM_NO_PARENS ; 
 scalar_t__ SCRIPTLANGUAGEVERSION_ES5 ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ create_array (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 scalar_t__ get_string_flat_val (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 scalar_t__ is_undefined (int /*<<< orphan*/ ) ; 
 scalar_t__ jsdisp_propput_idx (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_alloc_len (int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 scalar_t__ regexp_match_next (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_2__**) ; 
 int /*<<< orphan*/  const* strstrW (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*) ; 
 scalar_t__ to_flat_string (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 
 scalar_t__ to_uint32 (TYPE_1__*,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static HRESULT String_split(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    match_state_t match_result, *match_ptr = &match_result;
    DWORD length, i, match_len = 0;
    const WCHAR *ptr, *ptr2, *str, *match_str = NULL;
    unsigned limit = ~0u;
    jsdisp_t *array, *regexp = NULL;
    jsstr_t *jsstr, *match_jsstr, *tmp_str;
    HRESULT hres;

    TRACE("\n");

    hres = get_string_flat_val(ctx, jsthis, &jsstr, &str);
    if(FAILED(hres))
        return hres;

    length = jsstr_length(jsstr);

    if(!argc || (is_undefined(argv[0]) && ctx->version >= SCRIPTLANGUAGEVERSION_ES5)) {
        if(!r)
            return S_OK;

        hres = create_array(ctx, 0, &array);
        if(FAILED(hres))
            return hres;

        /* NOTE: according to spec, we should respect limit argument here (if provided).
         * We have a test showing that it's broken in native IE. */
        hres = jsdisp_propput_idx(array, 0, jsval_string(jsstr));
        if(FAILED(hres)) {
            jsdisp_release(array);
            return hres;
        }

        *r = jsval_obj(array);
        return S_OK;
    }

    if(argc > 1 && !is_undefined(argv[1])) {
        hres = to_uint32(ctx, argv[1], &limit);
        if(FAILED(hres)) {
            jsstr_release(jsstr);
            return hres;
        }
    }

    if(is_object_instance(argv[0])) {
        regexp = iface_to_jsdisp(get_object(argv[0]));
        if(regexp) {
            if(!is_class(regexp, JSCLASS_REGEXP)) {
                jsdisp_release(regexp);
                regexp = NULL;
            }
        }
    }

    if(!regexp) {
        hres = to_flat_string(ctx, argv[0], &match_jsstr, &match_str);
        if(FAILED(hres)) {
            jsstr_release(jsstr);
            return hres;
        }

        match_len = jsstr_length(match_jsstr);
        if(!match_len) {
            jsstr_release(match_jsstr);
            match_str = NULL;
        }
    }

    hres = create_array(ctx, 0, &array);

    if(SUCCEEDED(hres)) {
        ptr = str;
        match_result.cp = str;
        for(i=0; i<limit; i++) {
            if(regexp) {
                hres = regexp_match_next(ctx, regexp, REM_NO_PARENS, jsstr, &match_ptr);
                if(hres != S_OK)
                    break;
                ptr2 = match_result.cp - match_result.match_len;
            }else if(match_str) {
                ptr2 = strstrW(ptr, match_str);
                if(!ptr2)
                    break;
            }else {
                if(!*ptr)
                    break;
                ptr2 = ptr+1;
            }

            tmp_str = jsstr_alloc_len(ptr, ptr2-ptr);
            if(!tmp_str) {
                hres = E_OUTOFMEMORY;
                break;
            }

            hres = jsdisp_propput_idx(array, i, jsval_string(tmp_str));
            jsstr_release(tmp_str);
            if(FAILED(hres))
                break;

            if(regexp)
                ptr = match_result.cp;
            else if(match_str)
                ptr = ptr2 + match_len;
            else
                ptr++;
        }
    }

    if(SUCCEEDED(hres) && (match_str || regexp) && i<limit) {
        DWORD len = (str+length) - ptr;

        if(len || match_str) {
            tmp_str = jsstr_alloc_len(ptr, len);

            if(tmp_str) {
                hres = jsdisp_propput_idx(array, i, jsval_string(tmp_str));
                jsstr_release(tmp_str);
            }else {
                hres = E_OUTOFMEMORY;
            }
        }
    }

    if(regexp)
        jsdisp_release(regexp);
    if(match_str)
        jsstr_release(match_jsstr);
    jsstr_release(jsstr);

    if(SUCCEEDED(hres) && r)
        *r = jsval_obj(array);
    else
        jsdisp_release(array);

    return hres;
}