#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vdisp_t ;
struct TYPE_6__ {int safeopt; } ;
typedef  TYPE_1__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsstr_t ;
typedef  scalar_t__ WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDispatch ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ DISPATCH_CONSTRUCT ; 
 int /*<<< orphan*/  E_NOTIMPL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  IID_IDispatch ; 
 int INTERFACESAFE_FOR_UNTRUSTED_DATA ; 
 int INTERFACE_USES_DISPEX ; 
 int INTERFACE_USES_SECURITY_MANAGER ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JS_E_CANNOT_CREATE_OBJ ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/ * create_activex_object (TYPE_1__*,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_disp (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_generic_error (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_flat_string (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/  const**) ; 

__attribute__((used)) static HRESULT ActiveXObject_value(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsstr_t * progid_str;
    const WCHAR *progid;
    IDispatch *disp;
    IUnknown *obj;
    HRESULT hres;

    TRACE("\n");

    if(flags != DISPATCH_CONSTRUCT) {
        FIXME("unsupported flags %x\n", flags);
        return E_NOTIMPL;
    }

    if(ctx->safeopt != (INTERFACESAFE_FOR_UNTRUSTED_DATA|INTERFACE_USES_DISPEX|INTERFACE_USES_SECURITY_MANAGER)
        && ctx->safeopt != INTERFACE_USES_DISPEX) {
        FIXME("Unsupported safeopt %x\n", ctx->safeopt);
        return E_NOTIMPL;
    }

    if(argc != 1) {
        FIXME("unsupported argc %d\n", argc);
        return E_NOTIMPL;
    }

    hres = to_flat_string(ctx, argv[0], &progid_str, &progid);
    if(FAILED(hres))
        return hres;

    obj = create_activex_object(ctx, progid);
    jsstr_release(progid_str);
    if(!obj)
        return throw_generic_error(ctx, JS_E_CANNOT_CREATE_OBJ, NULL);

    hres = IUnknown_QueryInterface(obj, &IID_IDispatch, (void**)&disp);
    IUnknown_Release(obj);
    if(FAILED(hres)) {
        FIXME("Object does not support IDispatch\n");
        return E_NOTIMPL;
    }

    *r = jsval_disp(disp);
    return S_OK;
}