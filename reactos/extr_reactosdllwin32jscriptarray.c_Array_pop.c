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
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ get_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 scalar_t__ jsdisp_delete_idx (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ jsdisp_get_idx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 scalar_t__ set_length (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static HRESULT Array_pop(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsdisp_t *jsthis;
    jsval_t val;
    DWORD length;
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

    length--;
    hres = jsdisp_get_idx(jsthis, length, &val);
    if(SUCCEEDED(hres))
        hres = jsdisp_delete_idx(jsthis, length);
    else if(hres == DISP_E_UNKNOWNNAME) {
        val = jsval_undefined();
        hres = S_OK;
    }else
        return hres;

    if(SUCCEEDED(hres))
        hres = set_length(jsthis, length);

    if(FAILED(hres)) {
        jsval_release(val);
        return hres;
    }

    if(r)
        *r = val;
    else
        jsval_release(val);
    return hres;
}