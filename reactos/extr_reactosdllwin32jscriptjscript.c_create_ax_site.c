#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  site; } ;
typedef  TYPE_2__ script_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; TYPE_1__ IServiceProvider_iface; int /*<<< orphan*/ * sp; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IServiceProvider ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ AXSite ;

/* Variables and functions */
 int /*<<< orphan*/  AXSiteVtbl ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IActiveScriptSite_QueryInterface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IID_IServiceProvider ; 
 int /*<<< orphan*/  IServiceProvider_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 TYPE_3__* heap_alloc (int) ; 

IUnknown *create_ax_site(script_ctx_t *ctx)
{
    IServiceProvider *sp = NULL;
    AXSite *ret;
    HRESULT hres;

    hres = IActiveScriptSite_QueryInterface(ctx->site, &IID_IServiceProvider, (void**)&sp);
    if(FAILED(hres)) {
        TRACE("Could not get IServiceProvider iface: %08x\n", hres);
    }

    ret = heap_alloc(sizeof(AXSite));
    if(!ret) {
        IServiceProvider_Release(sp);
        return NULL;
    }

    ret->IServiceProvider_iface.lpVtbl = &AXSiteVtbl;
    ret->ref = 1;
    ret->sp = sp;

    return (IUnknown*)&ret->IServiceProvider_iface;
}