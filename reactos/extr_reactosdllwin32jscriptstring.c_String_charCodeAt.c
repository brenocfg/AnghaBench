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
typedef  double DWORD ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NAN ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  get_string_val (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  is_int32 (double) ; 
 int /*<<< orphan*/  jsstr_extract (int /*<<< orphan*/ *,double,int,int /*<<< orphan*/ *) ; 
 double jsstr_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  to_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static HRESULT String_charCodeAt(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsstr_t *str;
    DWORD idx = 0;
    HRESULT hres;

    TRACE("\n");

    hres = get_string_val(ctx, jsthis, &str);
    if(FAILED(hres))
        return hres;

    if(argc > 0) {
        double d;

        hres = to_integer(ctx, argv[0], &d);
        if(FAILED(hres)) {
            jsstr_release(str);
            return hres;
        }

        if(!is_int32(d) || d < 0 || d >= jsstr_length(str)) {
            jsstr_release(str);
            if(r)
                *r = jsval_number(NAN);
            return S_OK;
        }

        idx = d;
    }

    if(r) {
        WCHAR c;
        jsstr_extract(str, idx, 1, &c);
        *r = jsval_number(c);
    }

    jsstr_release(str);
    return S_OK;
}