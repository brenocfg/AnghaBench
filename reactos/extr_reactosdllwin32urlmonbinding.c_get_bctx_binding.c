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
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ IBinding ;
typedef  int /*<<< orphan*/  IBindCtx ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  Binding ;

/* Variables and functions */
 int /*<<< orphan*/  BindingVtbl ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IBindCtx_GetObjectParam (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  IID_IBinding ; 
 int /*<<< orphan*/  IUnknown_QueryInterface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cbinding_contextW ; 
 int /*<<< orphan*/ * impl_from_IBinding (TYPE_1__*) ; 

__attribute__((used)) static Binding *get_bctx_binding(IBindCtx *bctx)
{
    IBinding *binding;
    IUnknown *unk;
    HRESULT hres;

    hres = IBindCtx_GetObjectParam(bctx, cbinding_contextW, &unk);
    if(FAILED(hres))
        return NULL;

    hres = IUnknown_QueryInterface(unk, &IID_IBinding, (void**)&binding);
    IUnknown_Release(unk);
    if(FAILED(hres))
        return NULL;

    if (binding->lpVtbl != &BindingVtbl)
        return NULL;
    return impl_from_IBinding(binding);
}