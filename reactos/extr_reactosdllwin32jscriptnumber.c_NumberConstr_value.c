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
typedef  int WORD ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
#define  DISPATCH_CONSTRUCT 129 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int) ; 
#define  INVOKE_FUNC 128 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  create_number (int /*<<< orphan*/ *,double,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  jsval_number (double) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_number (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double*) ; 

__attribute__((used)) static HRESULT NumberConstr_value(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    double n;
    HRESULT hres;

    TRACE("\n");

    switch(flags) {
    case INVOKE_FUNC:
        if(!argc) {
            if(r)
                *r = jsval_number(0);
            return S_OK;
        }

        hres = to_number(ctx, argv[0], &n);
        if(FAILED(hres))
            return hres;

        if(r)
            *r = jsval_number(n);
        break;

    case DISPATCH_CONSTRUCT: {
        jsdisp_t *obj;

        if(argc) {
            hres = to_number(ctx, argv[0], &n);
            if(FAILED(hres))
                return hres;
        }else {
            n = 0;
        }

        hres = create_number(ctx, n, &obj);
        if(FAILED(hres))
            return hres;

        *r = jsval_obj(obj);
        break;
    }
    default:
        FIXME("unimplemented flags %x\n", flags);
        return E_NOTIMPL;
    }

    return S_OK;
}