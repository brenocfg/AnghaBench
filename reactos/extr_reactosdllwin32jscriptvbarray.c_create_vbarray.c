#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  script_ctx_t ;
typedef  int /*<<< orphan*/  jsdisp_t ;
struct TYPE_3__ {int /*<<< orphan*/  dispex; int /*<<< orphan*/  safearray; } ;
typedef  TYPE_1__ VBArrayInstance ;
typedef  int /*<<< orphan*/  SAFEARRAY ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  SafeArrayCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  alloc_vbarray (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 int /*<<< orphan*/  jsdisp_release (int /*<<< orphan*/ *) ; 

HRESULT create_vbarray(script_ctx_t *ctx, SAFEARRAY *sa, jsdisp_t **ret)
{
    VBArrayInstance *vbarray;
    HRESULT hres;

    hres = alloc_vbarray(ctx, NULL, &vbarray);
    if(FAILED(hres))
        return hres;

    hres = SafeArrayCopy(sa, &vbarray->safearray);
    if(FAILED(hres)) {
        jsdisp_release(&vbarray->dispex);
        return hres;
    }

    *ret = &vbarray->dispex;
    return S_OK;
}