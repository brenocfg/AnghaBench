#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/  IBaseFilter_iface; int /*<<< orphan*/  csFilter; } ;
struct TYPE_14__ {TYPE_12__ filter; TYPE_2__* pInputPin; } ;
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {TYPE_10__ renderer; TYPE_4__ IUnknown_inner; int /*<<< orphan*/  baseControlVideo; int /*<<< orphan*/  baseControlWindow; TYPE_4__* outer_unk; int /*<<< orphan*/  FullScreenMode; int /*<<< orphan*/  WindowPos; int /*<<< orphan*/  DestRect; int /*<<< orphan*/  SourceRect; int /*<<< orphan*/  init; TYPE_1__ IAMFilterMiscFlags_iface; } ;
typedef  TYPE_3__ VideoRendererImpl ;
struct TYPE_17__ {int /*<<< orphan*/  pin; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  TYPE_4__ IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  BaseControlVideo_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BaseControlWindow_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_12__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BaseFuncTable ; 
 int /*<<< orphan*/  BaseRendererImpl_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BaseRenderer_Init (TYPE_10__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLSID_VideoRenderer ; 
 TYPE_3__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_3__*) ; 
 int /*<<< orphan*/  CreateRenderingSubsystem (TYPE_3__*) ; 
 int /*<<< orphan*/  E_FAIL ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IAMFilterMiscFlags_Vtbl ; 
 int /*<<< orphan*/  IBasicVideo_VTable ; 
 int /*<<< orphan*/  IInner_VTable ; 
 int /*<<< orphan*/  IVideoWindow_VTable ; 
 int /*<<< orphan*/  OAFALSE ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*,void**) ; 
 int /*<<< orphan*/  VideoRenderer_Vtbl ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  renderer_BaseControlVideoFuncTable ; 
 int /*<<< orphan*/  renderer_BaseWindowFuncTable ; 

HRESULT VideoRenderer_create(IUnknown *pUnkOuter, void **ppv)
{
    HRESULT hr;
    VideoRendererImpl * pVideoRenderer;

    TRACE("(%p, %p)\n", pUnkOuter, ppv);

    *ppv = NULL;

    pVideoRenderer = CoTaskMemAlloc(sizeof(VideoRendererImpl));
    pVideoRenderer->IUnknown_inner.lpVtbl = &IInner_VTable;
    pVideoRenderer->IAMFilterMiscFlags_iface.lpVtbl = &IAMFilterMiscFlags_Vtbl;

    pVideoRenderer->init = FALSE;
    ZeroMemory(&pVideoRenderer->SourceRect, sizeof(RECT));
    ZeroMemory(&pVideoRenderer->DestRect, sizeof(RECT));
    ZeroMemory(&pVideoRenderer->WindowPos, sizeof(RECT));
    pVideoRenderer->FullScreenMode = OAFALSE;

    if (pUnkOuter)
        pVideoRenderer->outer_unk = pUnkOuter;
    else
        pVideoRenderer->outer_unk = &pVideoRenderer->IUnknown_inner;

    hr = BaseRenderer_Init(&pVideoRenderer->renderer, &VideoRenderer_Vtbl, pUnkOuter,
            &CLSID_VideoRenderer, (DWORD_PTR)(__FILE__ ": VideoRendererImpl.csFilter"),
            &BaseFuncTable);

    if (FAILED(hr))
        goto fail;

    hr = BaseControlWindow_Init(&pVideoRenderer->baseControlWindow, &IVideoWindow_VTable,
            &pVideoRenderer->renderer.filter, &pVideoRenderer->renderer.filter.csFilter,
            &pVideoRenderer->renderer.pInputPin->pin, &renderer_BaseWindowFuncTable);
    if (FAILED(hr))
        goto fail;

    hr = BaseControlVideo_Init(&pVideoRenderer->baseControlVideo, &IBasicVideo_VTable,
            &pVideoRenderer->renderer.filter, &pVideoRenderer->renderer.filter.csFilter,
            &pVideoRenderer->renderer.pInputPin->pin, &renderer_BaseControlVideoFuncTable);
    if (FAILED(hr))
        goto fail;

    if (!CreateRenderingSubsystem(pVideoRenderer)) {
        hr = E_FAIL;
        goto fail;
    }

    *ppv = &pVideoRenderer->IUnknown_inner;
    return S_OK;

fail:
    BaseRendererImpl_Release(&pVideoRenderer->renderer.filter.IBaseFilter_iface);
    CoTaskMemFree(pVideoRenderer);
    return hr;
}