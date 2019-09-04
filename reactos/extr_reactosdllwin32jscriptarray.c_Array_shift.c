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
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  scalar_t__ HRESULT ;
typedef  int DWORD ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ get_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int*) ; 
 scalar_t__ jsdisp_delete_idx (int /*<<< orphan*/ *,int) ; 
 scalar_t__ jsdisp_get_idx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ jsdisp_propput_idx (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 scalar_t__ set_length (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT Array_shift(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsdisp_t *jsthis;
    DWORD length = 0, i;
    jsval_t v, ret;
    HRESULT hres;

    TRACE("\n");

    hres = get_length(ctx, vthis, &jsthis, &length);
    if(FAILED(hres))
        return hres;

    if(!length) {
        hres = set_length(jsthis, 0);
        if(FAILED(hres))
            return hres;

        if(r)
            *r = jsval_undefined();
        return S_OK;
    }

    hres = jsdisp_get_idx(jsthis, 0, &ret);
    if(hres == DISP_E_UNKNOWNNAME) {
        ret = jsval_undefined();
        hres = S_OK;
    }

    for(i=1; SUCCEEDED(hres) && i<length; i++) {
        hres = jsdisp_get_idx(jsthis, i, &v);
        if(hres == DISP_E_UNKNOWNNAME)
            hres = jsdisp_delete_idx(jsthis, i-1);
        else if(SUCCEEDED(hres))
            hres = jsdisp_propput_idx(jsthis, i-1, v);
    }

    if(SUCCEEDED(hres)) {
        hres = jsdisp_delete_idx(jsthis, length-1);
        if(SUCCEEDED(hres))
            hres = set_length(jsthis, length-1);
    }

    if(FAILED(hres))
        return hres;

    if(r)
        *r = ret;
    else
        jsval_release(ret);
    return hres;
}