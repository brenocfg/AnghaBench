#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 unsigned int JSSTR_MAX_LENGTH ; 
 int /*<<< orphan*/  SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  get_string_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ ** heap_alloc_zero (unsigned int const) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * jsstr_alloc_buf (unsigned int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * jsstr_concat (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_flush (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 unsigned int jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT String_concat(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsstr_t *ret = NULL, *str;
    HRESULT hres;

    TRACE("\n");

    hres = get_string_val(ctx, jsthis, &str);
    if(FAILED(hres))
        return hres;

    switch(argc) {
    case 0:
        ret = str;
        break;
    case 1: {
        jsstr_t *arg_str;

        hres = to_string(ctx, argv[0], &arg_str);
        if(FAILED(hres)) {
            jsstr_release(str);
            return hres;
        }

        ret = jsstr_concat(str, arg_str);
        jsstr_release(str);
        if(!ret)
            return E_OUTOFMEMORY;
        break;
    }
    default: {
        const unsigned str_cnt = argc+1;
        unsigned len = 0, i;
        jsstr_t **strs;
        WCHAR *ptr;

        strs = heap_alloc_zero(str_cnt * sizeof(*strs));
        if(!strs) {
            jsstr_release(str);
            return E_OUTOFMEMORY;
        }

        strs[0] = str;
        for(i=0; i < argc; i++) {
            hres = to_string(ctx, argv[i], strs+i+1);
            if(FAILED(hres))
                break;
        }

        if(SUCCEEDED(hres)) {
            for(i=0; i < str_cnt; i++) {
                len += jsstr_length(strs[i]);
                if(len > JSSTR_MAX_LENGTH) {
                    hres = E_OUTOFMEMORY;
                    break;
                }
            }

            if(SUCCEEDED(hres)) {
                ret = jsstr_alloc_buf(len, &ptr);
                if(ret) {
                    for(i=0; i < str_cnt; i++)
                        ptr += jsstr_flush(strs[i], ptr);
                }else {
                    hres = E_OUTOFMEMORY;
                }
            }
        }

        while(i--)
            jsstr_release(strs[i]);
        heap_free(strs);
        if(FAILED(hres))
            return hres;
    }
    }

    if(r)
        *r = jsval_string(ret);
    else
        jsstr_release(ret);
    return S_OK;
}