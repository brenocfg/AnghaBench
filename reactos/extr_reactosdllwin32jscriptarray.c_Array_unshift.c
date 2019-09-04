#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  dispex; } ;
struct TYPE_9__ {TYPE_1__ u; } ;
typedef  TYPE_2__ vdisp_t ;
struct TYPE_10__ {int version; } ;
typedef  TYPE_3__ script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ HRESULT ;
typedef  unsigned int DWORD ;
typedef  int /*<<< orphan*/  DISPID ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ DISP_E_UNKNOWNNAME ; 
 scalar_t__ FAILED (scalar_t__) ; 
 scalar_t__ IDispatchEx_DeleteMemberByDispID (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (scalar_t__) ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 scalar_t__ get_length (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ **,unsigned int*) ; 
 int /*<<< orphan*/ * idx_to_str (unsigned int,int /*<<< orphan*/ *) ; 
 scalar_t__ jsdisp_get_id (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jsdisp_propget (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ jsdisp_propput_idx (int /*<<< orphan*/ *,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_number (unsigned int) ; 
 int /*<<< orphan*/  jsval_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsval_undefined () ; 
 scalar_t__ set_length (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static HRESULT Array_unshift(script_ctx_t *ctx, vdisp_t *vthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsdisp_t *jsthis;
    WCHAR buf[14], *buf_end, *str;
    DWORD i, length;
    jsval_t val;
    DISPID id;
    HRESULT hres;

    TRACE("\n");

    hres = get_length(ctx, vthis, &jsthis, &length);
    if(FAILED(hres))
        return hres;

    if(argc) {
        buf_end = buf + ARRAY_SIZE(buf)-1;
        *buf_end-- = 0;
        i = length;

        while(i--) {
            str = idx_to_str(i, buf_end);

            hres = jsdisp_get_id(jsthis, str, 0, &id);
            if(SUCCEEDED(hres)) {
                hres = jsdisp_propget(jsthis, id, &val);
                if(FAILED(hres))
                    return hres;

                hres = jsdisp_propput_idx(jsthis, i+argc, val);
                jsval_release(val);
            }else if(hres == DISP_E_UNKNOWNNAME) {
                hres = IDispatchEx_DeleteMemberByDispID(vthis->u.dispex, id);
            }
        }

        if(FAILED(hres))
            return hres;
    }

    for(i=0; i<argc; i++) {
        hres = jsdisp_propput_idx(jsthis, i, argv[i]);
        if(FAILED(hres))
            return hres;
    }

    if(argc) {
        length += argc;
        hres = set_length(jsthis, length);
        if(FAILED(hres))
            return hres;
    }

    if(r)
        *r = ctx->version < 2 ? jsval_undefined() : jsval_number(length);
    return S_OK;
}