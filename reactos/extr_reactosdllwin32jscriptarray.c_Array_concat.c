#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  disp; } ;
struct TYPE_5__ {TYPE_1__ u; } ;
typedef  TYPE_2__ vdisp_t ;
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsval_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
typedef  int /*<<< orphan*/  WORD ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  unsigned int DWORD ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  concat_obj (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  create_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  get_object (int /*<<< orphan*/ ) ; 
 scalar_t__ is_object_instance (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_propput_idx (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jsval_obj (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT Array_concat(script_ctx_t *ctx, vdisp_t *jsthis, WORD flags, unsigned argc, jsval_t *argv,
        jsval_t *r)
{
    jsdisp_t *ret;
    DWORD len = 0;
    HRESULT hres;

    TRACE("\n");

    hres = create_array(ctx, 0, &ret);
    if(FAILED(hres))
        return hres;

    hres = concat_obj(ret, jsthis->u.disp, &len);
    if(SUCCEEDED(hres)) {
        DWORD i;

        for(i=0; i < argc; i++) {
            if(is_object_instance(argv[i]))
                hres = concat_obj(ret, get_object(argv[i]), &len);
            else
                hres = jsdisp_propput_idx(ret, len++, argv[i]);
            if(FAILED(hres))
                break;
        }
    }

    if(FAILED(hres))
        return hres;

    if(r)
        *r = jsval_obj(ret);
    else
        jsdisp_release(ret);
    return S_OK;
}