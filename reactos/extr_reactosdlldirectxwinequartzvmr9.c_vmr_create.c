#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct TYPE_20__ {int /*<<< orphan*/  IBaseFilter_iface; int /*<<< orphan*/  csFilter; } ;
struct TYPE_19__ {TYPE_14__ filter; TYPE_12__* pInputPin; } ;
struct TYPE_17__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_16__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_29__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_28__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_27__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_26__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_25__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_24__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_23__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_22__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_21__ {int /*<<< orphan*/ * lpVtbl; } ;
struct quartz_vmr {int /*<<< orphan*/  hD3d9; TYPE_13__ renderer; int /*<<< orphan*/  target_rect; int /*<<< orphan*/  source_rect; int /*<<< orphan*/  baseControlVideo; int /*<<< orphan*/  baseControlWindow; TYPE_11__ IVMRWindowlessControl9_iface; TYPE_10__ IVMRWindowlessControl_iface; TYPE_9__ IVMRSurfaceAllocatorNotify9_iface; TYPE_8__ IVMRSurfaceAllocatorNotify_iface; TYPE_7__ IVMRMonitorConfig9_iface; TYPE_6__ IVMRMonitorConfig_iface; TYPE_5__ IVMRFilterConfig9_iface; TYPE_4__ IVMRFilterConfig_iface; int /*<<< orphan*/ * hWndClippingWindow; int /*<<< orphan*/ * presenter; int /*<<< orphan*/ * allocator; scalar_t__ cur_surface; scalar_t__ num_surfaces; int /*<<< orphan*/ * allocator_mon; int /*<<< orphan*/ * allocator_d3d9_dev; scalar_t__ mode; TYPE_3__ IAMFilterMiscFlags_iface; TYPE_2__ IAMCertifiedOutputProtection_iface; TYPE_1__ IUnknown_inner; void* bAggregatable; void* bUnkOuterValid; int /*<<< orphan*/ * outer_unk; } ;
struct TYPE_18__ {int /*<<< orphan*/  pin; } ;
typedef  int /*<<< orphan*/  RECT ;
typedef  int /*<<< orphan*/ * LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  int /*<<< orphan*/  CLSID ;

/* Variables and functions */
 int /*<<< orphan*/  BaseControlVideo_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_14__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BaseControlWindow_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_14__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BaseFuncTable ; 
 int /*<<< orphan*/  BaseRendererImpl_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BaseRenderer_Init (TYPE_13__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLSID_VideoMixingRenderer ; 
 int /*<<< orphan*/  CLSID_VideoMixingRenderer9 ; 
 struct quartz_vmr* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (struct quartz_vmr*) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 void* FALSE ; 
 int /*<<< orphan*/  FreeLibrary (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAMCertifiedOutputProtection_Vtbl ; 
 int /*<<< orphan*/  IAMFilterMiscFlags_Vtbl ; 
 int /*<<< orphan*/  IBasicVideo_VTable ; 
 int /*<<< orphan*/  IInner_VTable ; 
 int /*<<< orphan*/  IVideoWindow_VTable ; 
 scalar_t__ IsEqualGUID (int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LoadLibraryA (char*) ; 
 int /*<<< orphan*/  TRACE (char*,struct quartz_vmr*,...) ; 
 int /*<<< orphan*/  VFW_E_DDRAW_CAPS_NOT_SUITABLE ; 
 int /*<<< orphan*/  VMR7_FilterConfig_Vtbl ; 
 int /*<<< orphan*/  VMR7_MonitorConfig_Vtbl ; 
 int /*<<< orphan*/  VMR7_SurfaceAllocatorNotify_Vtbl ; 
 int /*<<< orphan*/  VMR7_WindowlessControl_Vtbl ; 
 int /*<<< orphan*/  VMR9_FilterConfig_Vtbl ; 
 int /*<<< orphan*/  VMR9_MonitorConfig_Vtbl ; 
 int /*<<< orphan*/  VMR9_SurfaceAllocatorNotify_Vtbl ; 
 int /*<<< orphan*/  VMR9_WindowlessControl_Vtbl ; 
 int /*<<< orphan*/  VMR_Vtbl ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  renderer_BaseControlVideoFuncTable ; 
 int /*<<< orphan*/  renderer_BaseWindowFuncTable ; 

__attribute__((used)) static HRESULT vmr_create(IUnknown *outer_unk, LPVOID *ppv, const CLSID *clsid)
{
    HRESULT hr;
    struct quartz_vmr* pVMR;

    TRACE("(%p, %p)\n", outer_unk, ppv);

    *ppv = NULL;

    pVMR = CoTaskMemAlloc(sizeof(struct quartz_vmr));

    pVMR->hD3d9 = LoadLibraryA("d3d9.dll");
    if (!pVMR->hD3d9 )
    {
        WARN("Could not load d3d9.dll\n");
        CoTaskMemFree(pVMR);
        return VFW_E_DDRAW_CAPS_NOT_SUITABLE;
    }

    pVMR->outer_unk = outer_unk;
    pVMR->bUnkOuterValid = FALSE;
    pVMR->bAggregatable = FALSE;
    pVMR->IUnknown_inner.lpVtbl = &IInner_VTable;
    pVMR->IAMCertifiedOutputProtection_iface.lpVtbl = &IAMCertifiedOutputProtection_Vtbl;
    pVMR->IAMFilterMiscFlags_iface.lpVtbl = &IAMFilterMiscFlags_Vtbl;

    pVMR->mode = 0;
    pVMR->allocator_d3d9_dev = NULL;
    pVMR->allocator_mon= NULL;
    pVMR->num_surfaces = pVMR->cur_surface = 0;
    pVMR->allocator = NULL;
    pVMR->presenter = NULL;
    pVMR->hWndClippingWindow = NULL;
    pVMR->IVMRFilterConfig_iface.lpVtbl = &VMR7_FilterConfig_Vtbl;
    pVMR->IVMRFilterConfig9_iface.lpVtbl = &VMR9_FilterConfig_Vtbl;
    pVMR->IVMRMonitorConfig_iface.lpVtbl = &VMR7_MonitorConfig_Vtbl;
    pVMR->IVMRMonitorConfig9_iface.lpVtbl = &VMR9_MonitorConfig_Vtbl;
    pVMR->IVMRSurfaceAllocatorNotify_iface.lpVtbl = &VMR7_SurfaceAllocatorNotify_Vtbl;
    pVMR->IVMRSurfaceAllocatorNotify9_iface.lpVtbl = &VMR9_SurfaceAllocatorNotify_Vtbl;
    pVMR->IVMRWindowlessControl_iface.lpVtbl = &VMR7_WindowlessControl_Vtbl;
    pVMR->IVMRWindowlessControl9_iface.lpVtbl = &VMR9_WindowlessControl_Vtbl;

    if (IsEqualGUID(clsid, &CLSID_VideoMixingRenderer))
        hr = BaseRenderer_Init(&pVMR->renderer, &VMR_Vtbl, outer_unk, &CLSID_VideoMixingRenderer,
                               (DWORD_PTR)(__FILE__ ": VMR7Impl.csFilter"), &BaseFuncTable);
    else
        hr = BaseRenderer_Init(&pVMR->renderer, &VMR_Vtbl, outer_unk, &CLSID_VideoMixingRenderer9,
                               (DWORD_PTR)(__FILE__ ": VMR9Impl.csFilter"), &BaseFuncTable);

    if (FAILED(hr))
        goto fail;

    hr = BaseControlWindow_Init(&pVMR->baseControlWindow, &IVideoWindow_VTable, &pVMR->renderer.filter,
                                &pVMR->renderer.filter.csFilter, &pVMR->renderer.pInputPin->pin,
                                &renderer_BaseWindowFuncTable);
    if (FAILED(hr))
        goto fail;

    hr = BaseControlVideo_Init(&pVMR->baseControlVideo, &IBasicVideo_VTable, &pVMR->renderer.filter,
                               &pVMR->renderer.filter.csFilter, &pVMR->renderer.pInputPin->pin,
                               &renderer_BaseControlVideoFuncTable);
    if (FAILED(hr))
        goto fail;

    *ppv = (LPVOID)pVMR;
    ZeroMemory(&pVMR->source_rect, sizeof(RECT));
    ZeroMemory(&pVMR->target_rect, sizeof(RECT));
    TRACE("Created at %p\n", pVMR);
    return hr;

fail:
    BaseRendererImpl_Release(&pVMR->renderer.filter.IBaseFilter_iface);
    FreeLibrary(pVMR->hD3d9);
    CoTaskMemFree(pVMR);
    return hr;
}