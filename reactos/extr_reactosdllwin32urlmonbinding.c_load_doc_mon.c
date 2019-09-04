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
struct TYPE_3__ {scalar_t__ download_state; int /*<<< orphan*/  mon; int /*<<< orphan*/  IBinding_iface; int /*<<< orphan*/  bctx; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IPersistMoniker ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ Binding ;

/* Variables and functions */
 int /*<<< orphan*/  CreateAsyncBindCtxEx (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ END_DOWNLOAD ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FIXME (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindCtx_RegisterObjectParam (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindCtx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindCtx_RevokeObjectParam (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IPersistMoniker_Load (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  WARN (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bscb_holderW ; 
 int /*<<< orphan*/  cbinding_contextW ; 

__attribute__((used)) static void load_doc_mon(Binding *binding, IPersistMoniker *persist)
{
    IBindCtx *bctx;
    HRESULT hres;

    hres = CreateAsyncBindCtxEx(binding->bctx, 0, NULL, NULL, &bctx, 0);
    if(FAILED(hres)) {
        WARN("CreateAsyncBindCtxEx failed: %08x\n", hres);
        return;
    }

    IBindCtx_RevokeObjectParam(bctx, bscb_holderW);
    IBindCtx_RegisterObjectParam(bctx, cbinding_contextW, (IUnknown*)&binding->IBinding_iface);

    hres = IPersistMoniker_Load(persist, binding->download_state == END_DOWNLOAD, binding->mon, bctx, 0x12);
    IBindCtx_RevokeObjectParam(bctx, cbinding_contextW);
    IBindCtx_Release(bctx);
    if(FAILED(hres))
        FIXME("Load failed: %08x\n", hres);
}