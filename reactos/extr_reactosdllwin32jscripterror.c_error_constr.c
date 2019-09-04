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
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int WORD ;
typedef  double UINT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
#define  DISPATCH_CONSTRUCT 129 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  INVOKE_FUNC 128 
 double NAN ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  create_error (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ isnan (double) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * jsstr_empty () ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 
 int /*<<< orphan*/  to_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static HRESULT error_constr(script_ctx_t *ctx, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r, jsdisp_t *constr) {
    jsdisp_t *err;
    UINT num = 0;
    jsstr_t *msg = NULL;
    HRESULT hres;

    if(argc) {
        double n;

        hres = to_number(ctx, argv[0], &n);
        if(FAILED(hres)) /* FIXME: really? */
            n = NAN;
        if(isnan(n))
            hres = to_string(ctx, argv[0], &msg);
        if(FAILED(hres))
            return hres;
        num = n;
    }

    if(!msg) {
        if(argc > 1) {
            hres = to_string(ctx, argv[1], &msg);
            if(FAILED(hres))
                return hres;
        }else {
            msg = jsstr_empty();
        }
    }

    switch(flags) {
    case INVOKE_FUNC:
    case DISPATCH_CONSTRUCT:
        hres = create_error(ctx, constr, num, msg, &err);
        jsstr_release(msg);
        if(FAILED(hres))
            return hres;

        if(r)
            *r = jsval_obj(err);
        else
            jsdisp_release(err);
        return S_OK;

    default:
        if(msg)
            jsstr_release(msg);
        FIXME("unimplemented flags %x\n", flags);
        return E_NOTIMPL;
    }
}