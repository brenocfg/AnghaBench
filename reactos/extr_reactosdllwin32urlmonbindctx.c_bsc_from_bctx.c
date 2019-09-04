#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  IBindStatusCallbackEx_iface; int /*<<< orphan*/ * callback; } ;
typedef  int /*<<< orphan*/  IBindStatusCallback ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_1__ BindStatusCallback ;

/* Variables and functions */
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindStatusCallbackEx_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindStatusCallback_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBindStatusCallback_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IBindStatusCallback_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IID_IBindStatusCallbackHolder ; 
 int /*<<< orphan*/ * bsch_from_bctx (int /*<<< orphan*/ *) ; 

IBindStatusCallback *bsc_from_bctx(IBindCtx *bctx)
{
    BindStatusCallback *holder;
    IBindStatusCallback *bsc;
    HRESULT hres;

    bsc = bsch_from_bctx(bctx);
    if(!bsc)
        return NULL;

    hres = IBindStatusCallback_QueryInterface(bsc, &IID_IBindStatusCallbackHolder, (void**)&holder);
    if(FAILED(hres))
        return bsc;

    if(holder->callback) {
        IBindStatusCallback_Release(bsc);
        bsc = holder->callback;
        IBindStatusCallback_AddRef(bsc);
    }

    IBindStatusCallbackEx_Release(&holder->IBindStatusCallbackEx_iface);
    return bsc;
}