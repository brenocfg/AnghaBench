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

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DISPATCH_METHOD ; 
 int /*<<< orphan*/  DISP_E_UNKNOWNNAME ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  disp_call_value (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_length (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,unsigned int*) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_get_idx (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_number (unsigned int) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 

__attribute__((used)) static HRESULT Array_forEach(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsval_t value, args[3], res;
    jsdisp_t *jsthis;
    unsigned length, i;
    HRESULT hres;

    TRACE("\n");

    /* FIXME: Check IsCallable */
    if(argc != 1 || !is_object_instance(argv[0])) {
        FIXME("Unsupported arguments\n");
        return E_NOTIMPL;
    }

    hres = get_length(ctx, vthis, &jsthis, &length);
    if(FAILED(hres))
        return hres;

    for(i = 0; i < length; i++) {
        hres = jsdisp_get_idx(jsthis, i, &value);
        if(hres == DISP_E_UNKNOWNNAME)
            continue;
        if(FAILED(hres))
            return hres;

        args[0] = value;
        args[1] = jsval_number(i);
        args[2] = jsval_obj(jsthis);
        hres = disp_call_value(ctx, get_object(argv[0]), NULL, DISPATCH_METHOD, ARRAY_SIZE(args), args, &res);
        jsval_release(value);
        if(FAILED(hres))
            return hres;
        jsval_release(res);
    }

    if(r) *r = jsval_undefined();
    return S_OK;
}