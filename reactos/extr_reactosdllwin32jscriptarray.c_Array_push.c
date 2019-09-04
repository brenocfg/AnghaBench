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
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  get_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,scalar_t__*) ; 
 int /*<<< orphan*/  jsdisp_propput_idx (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_number (scalar_t__) ; 
 int /*<<< orphan*/  set_length (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static HRESULT Array_push(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsdisp_t *jsthis;
    DWORD length = 0;
    unsigned i;
    HRESULT hres;

    TRACE("\n");

    hres = get_length(ctx, vthis, &jsthis, &length);
    if(FAILED(hres))
        return hres;

    for(i=0; i < argc; i++) {
        hres = jsdisp_propput_idx(jsthis, length+i, argv[i]);
        if(FAILED(hres))
            return hres;
    }

    hres = set_length(jsthis, length+argc);
    if(FAILED(hres))
        return hres;

    if(r)
        *r = jsval_number(length+argc);
    return S_OK;
}