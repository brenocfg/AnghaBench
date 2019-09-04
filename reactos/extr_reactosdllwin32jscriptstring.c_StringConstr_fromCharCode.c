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
typedef  unsigned int WCHAR ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/ * jsstr_alloc_buf (unsigned int,unsigned int**) ; 
 int /*<<< orphan*/  jsstr_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  to_uint32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*) ; 

__attribute__((used)) static HRESULT StringConstr_fromCharCode(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags,
        unsigned argc, jsval_t *argv, jsval_t *r)
{
    WCHAR *ret_str;
    DWORD i, code;
    jsstr_t *ret;
    HRESULT hres;

    TRACE("\n");

    ret = jsstr_alloc_buf(argc, &ret_str);
    if(!ret)
        return E_OUTOFMEMORY;

    for(i=0; i<argc; i++) {
        hres = to_uint32(ctx, argv[i], &code);
        if(FAILED(hres)) {
            jsstr_release(ret);
            return hres;
        }

        ret_str[i] = code;
    }

    if(r)
        *r = jsval_string(ret);
    else
        jsstr_release(ret);
    return S_OK;
}