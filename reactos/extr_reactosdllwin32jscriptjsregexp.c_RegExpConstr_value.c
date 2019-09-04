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
#define  DISPATCH_METHOD 128 
 int /*<<< orphan*/  E_NOTIMPL ; 
 int /*<<< orphan*/  FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,...) ; 
 int /*<<< orphan*/  JSCLASS_REGEXP ; 
 int /*<<< orphan*/  JS_E_REGEXP_SYNTAX ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  create_regexp_var (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * iface_to_jsdisp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_class (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_undefined (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  throw_regexp_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT RegExpConstr_value(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    TRACE("\n");

    switch(flags) {
    case DISPATCH_METHOD:
        if(argc) {
            if(is_object_instance(argv[0])) {
                jsdisp_t *jsdisp = iface_to_jsdisp(get_object(argv[0]));
                if(jsdisp) {
                    if(is_class(jsdisp, JSCLASS_REGEXP)) {
                        if(argc > 1 && !is_undefined(argv[1])) {
                            jsdisp_release(jsdisp);
                            return throw_regexp_error(ctx, JS_E_REGEXP_SYNTAX, NULL);
                        }

                        if(r)
                            *r = jsval_obj(jsdisp);
                        else
                            jsdisp_release(jsdisp);
                        return S_OK;
                    }
                    jsdisp_release(jsdisp);
                }
            }
        }
        /* fall through */
    case DISPATCH_CONSTRUCT: {
        jsdisp_t *ret;
        HRESULT hres;

        if(!argc) {
            FIXME("no args\n");
            return E_NOTIMPL;
        }

        hres = create_regexp_var(ctx, argv[0], argc > 1 ? argv+1 : NULL, &ret);
        if(FAILED(hres))
            return hres;

        if(r)
            *r = jsval_obj(ret);
        else
            jsdisp_release(ret);
        return S_OK;
    }
    default:
        FIXME("unimplemented flags: %x\n", flags);
        return E_NOTIMPL;
    }

    return S_OK;
}