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
typedef  int /*<<< orphan*/  stop_cache_binding_proc_t ;
struct TYPE_3__ {int /*<<< orphan*/  IBindStatusCallback_iface; int /*<<< orphan*/  bindf; void* ctx; int /*<<< orphan*/  onstop_proc; } ;
typedef  int /*<<< orphan*/  IUri ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IMoniker ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ DownloadBSC ;

/* Variables and functions */
 int /*<<< orphan*/  BINDF_ASYNCHRONOUS ; 
 int /*<<< orphan*/  CreateAsyncBindCtx (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  CreateURLMonikerEx2 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DownloadBSC_Create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IMoniker_BindToStorage (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IMoniker_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 

HRESULT download_to_cache(IUri *uri, stop_cache_binding_proc_t proc, void *ctx, IBindStatusCallback *callback)
{
    DownloadBSC *dwl_bsc;
    IBindCtx *bindctx;
    IMoniker *mon;
    IUnknown *unk;
    HRESULT hres;

    hres = DownloadBSC_Create(callback, NULL, &dwl_bsc);
    if(FAILED(hres))
        return hres;

    dwl_bsc->onstop_proc = proc;
    dwl_bsc->ctx = ctx;
    dwl_bsc->bindf = BINDF_ASYNCHRONOUS;

    hres = CreateAsyncBindCtx(0, &dwl_bsc->IBindStatusCallback_iface, NULL, &bindctx);
    IBindStatusCallback_Release(&dwl_bsc->IBindStatusCallback_iface);
    if(FAILED(hres))
        return hres;

    hres = CreateURLMonikerEx2(NULL, uri, &mon, 0);
    if(FAILED(hres)) {
        IBindCtx_Release(bindctx);
        return hres;
    }

    hres = IMoniker_BindToStorage(mon, bindctx, NULL, &IID_IUnknown, (void**)&unk);
    IMoniker_Release(mon);
    IBindCtx_Release(bindctx);
    if(SUCCEEDED(hres) && unk)
        IUnknown_Release(unk);
    return hres;

}