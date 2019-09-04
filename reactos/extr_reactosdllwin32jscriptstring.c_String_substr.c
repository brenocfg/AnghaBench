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
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  get_string_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ is_int32 (double) ; 
 int jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_substr (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int min (int,double) ; 
 int /*<<< orphan*/  to_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static HRESULT String_substr(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    int start=0, len, length;
    jsstr_t *str;
    double d;
    HRESULT hres;

    TRACE("\n");

    hres = get_string_val(ctx, jsthis, &str);
    if(FAILED(hres))
        return hres;

    length = jsstr_length(str);
    if(argc >= 1) {
        hres = to_integer(ctx, argv[0], &d);
        if(FAILED(hres)) {
            jsstr_release(str);
            return hres;
        }

        if(d >= 0)
            start = is_int32(d) ? min(length, d) : length;
    }

    if(argc >= 2) {
        hres = to_integer(ctx, argv[1], &d);
        if(FAILED(hres)) {
            jsstr_release(str);
            return hres;
        }

        if(d >= 0.0)
            len = is_int32(d) ? min(length-start, d) : length-start;
        else
            len = 0;
    }else {
        len = length-start;
    }

    hres = S_OK;
    if(r) {
        jsstr_t *ret = jsstr_substr(str, start, len);
        if(ret)
            *r = jsval_string(ret);
        else
            hres = E_OUTOFMEMORY;
    }

    jsstr_release(str);
    return hres;
}