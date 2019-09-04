#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  IBaseFilter_iface; } ;
struct TYPE_15__ {TYPE_2__ filter; } ;
struct TYPE_14__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {TYPE_4__ IUnknown_inner; TYPE_9__ renderer; TYPE_4__* outer_unk; TYPE_1__ IAMFilterMiscFlags_iface; } ;
typedef  TYPE_3__ NullRendererImpl ;
typedef  TYPE_4__ IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  BaseRendererImpl_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BaseRenderer_Init (TYPE_9__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLSID_NullRenderer ; 
 TYPE_3__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_3__*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAMFilterMiscFlags_Vtbl ; 
 int /*<<< orphan*/  IInner_VTable ; 
 int /*<<< orphan*/  NullRenderer_Vtbl ; 
 int /*<<< orphan*/  RendererFuncTable ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*,void**) ; 

HRESULT NullRenderer_create(IUnknown *pUnkOuter, void **ppv)
{
    HRESULT hr;
    NullRendererImpl *pNullRenderer;

    TRACE("(%p, %p)\n", pUnkOuter, ppv);

    *ppv = NULL;

    pNullRenderer = CoTaskMemAlloc(sizeof(NullRendererImpl));
    pNullRenderer->IUnknown_inner.lpVtbl = &IInner_VTable;
    pNullRenderer->IAMFilterMiscFlags_iface.lpVtbl = &IAMFilterMiscFlags_Vtbl;

    if (pUnkOuter)
        pNullRenderer->outer_unk = pUnkOuter;
    else
        pNullRenderer->outer_unk = &pNullRenderer->IUnknown_inner;

    hr = BaseRenderer_Init(&pNullRenderer->renderer, &NullRenderer_Vtbl, pUnkOuter,
            &CLSID_NullRenderer, (DWORD_PTR)(__FILE__ ": NullRendererImpl.csFilter"),
            &RendererFuncTable);

    if (FAILED(hr))
    {
        BaseRendererImpl_Release(&pNullRenderer->renderer.filter.IBaseFilter_iface);
        CoTaskMemFree(pNullRenderer);
    }
    else
        *ppv = &pNullRenderer->IUnknown_inner;

    return S_OK;
}