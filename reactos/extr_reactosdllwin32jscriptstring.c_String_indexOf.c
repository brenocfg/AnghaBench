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
typedef  int INT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  get_string_flat_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 
 scalar_t__ is_int32 (double) ; 
 unsigned int jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int) ; 
 int /*<<< orphan*/  memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,unsigned int) ; 
 unsigned int min (unsigned int,double) ; 
 int /*<<< orphan*/  to_flat_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 
 int /*<<< orphan*/  to_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static HRESULT String_indexOf(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    unsigned pos = 0, search_len, length;
    jsstr_t *search_jsstr, *jsstr;
    const WCHAR *search_str, *str;
    INT ret = -1;
    HRESULT hres;

    TRACE("\n");

    hres = get_string_flat_val(ctx, jsthis, &jsstr, &str);
    if(FAILED(hres))
        return hres;

    if(!argc) {
        if(r)
            *r = jsval_number(-1);
        jsstr_release(jsstr);
        return S_OK;
    }

    hres = to_flat_string(ctx, argv[0], &search_jsstr, &search_str);
    if(FAILED(hres)) {
        jsstr_release(jsstr);
        return hres;
    }

    search_len = jsstr_length(search_jsstr);
    length = jsstr_length(jsstr);

    if(argc >= 2) {
        double d;

        hres = to_integer(ctx, argv[1], &d);
        if(SUCCEEDED(hres) && d > 0.0)
            pos = is_int32(d) ? min(length, d) : length;
    }

    if(SUCCEEDED(hres) && length >= search_len) {
        const WCHAR *end = str+length-search_len;
        const WCHAR *ptr;

        for(ptr = str+pos; ptr <= end; ptr++) {
            if(!memcmp(ptr, search_str, search_len*sizeof(WCHAR))) {
                ret = ptr-str;
                break;
            }
        }
    }

    jsstr_release(search_jsstr);
    jsstr_release(jsstr);
    if(FAILED(hres))
        return hres;

    if(r)
        *r = jsval_number(ret);
    return S_OK;
}