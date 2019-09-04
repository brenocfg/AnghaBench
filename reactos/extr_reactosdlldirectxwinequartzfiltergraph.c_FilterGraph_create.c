#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_45__   TYPE_9__ ;
typedef  struct TYPE_44__   TYPE_8__ ;
typedef  struct TYPE_43__   TYPE_7__ ;
typedef  struct TYPE_42__   TYPE_6__ ;
typedef  struct TYPE_41__   TYPE_5__ ;
typedef  struct TYPE_40__   TYPE_4__ ;
typedef  struct TYPE_39__   TYPE_3__ ;
typedef  struct TYPE_38__   TYPE_2__ ;
typedef  struct TYPE_37__   TYPE_21__ ;
typedef  struct TYPE_36__   TYPE_1__ ;
typedef  struct TYPE_35__   TYPE_18__ ;
typedef  struct TYPE_34__   TYPE_16__ ;
typedef  struct TYPE_33__   TYPE_15__ ;
typedef  struct TYPE_32__   TYPE_14__ ;
typedef  struct TYPE_31__   TYPE_13__ ;
typedef  struct TYPE_30__   TYPE_12__ ;
typedef  struct TYPE_29__   TYPE_11__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
struct TYPE_45__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_44__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_43__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_42__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_41__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_40__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_39__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_38__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_37__ {TYPE_15__* DebugInfo; } ;
struct TYPE_36__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_34__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_32__ {int /*<<< orphan*/  disabled; scalar_t__ hWnd; } ;
struct TYPE_31__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_30__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_29__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_28__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_35__ {int ref; int nameIndex; TYPE_16__ IUnknown_inner; TYPE_21__ cs; int /*<<< orphan*/  evqueue; int /*<<< orphan*/  hEventCompletion; int /*<<< orphan*/ * punkFilterMapper2; TYPE_16__* outer_unk; scalar_t__ version; scalar_t__ recursioncount; scalar_t__ pause_time; scalar_t__ start_time; int /*<<< orphan*/  timeformatseek; scalar_t__ nItfCacheEntries; int /*<<< orphan*/ * pSite; int /*<<< orphan*/  state; int /*<<< orphan*/ * refClockProvider; scalar_t__ EcCompleteCount; scalar_t__ nRenderers; TYPE_14__ notif; void* HandleEcClockChanged; void* HandleEcRepaint; void* HandleEcComplete; int /*<<< orphan*/ * refClock; scalar_t__ filterCapacity; scalar_t__ nFilters; int /*<<< orphan*/ * pFilterNames; int /*<<< orphan*/ * ppFiltersInGraph; TYPE_13__ IGraphVersion_iface; TYPE_12__ IObjectWithSite_iface; TYPE_11__ IMediaPosition_iface; TYPE_10__ IGraphConfig_iface; TYPE_9__ IMediaEventSink_iface; TYPE_8__ IMediaFilter_iface; TYPE_7__ IMediaEventEx_iface; TYPE_6__ IVideoWindow_iface; TYPE_5__ IBasicVideo2_iface; TYPE_4__ IBasicAudio_iface; TYPE_3__ IMediaSeeking_iface; TYPE_2__ IMediaControl_iface; TYPE_1__ IFilterGraph2_iface; void* defaultclock; } ;
struct TYPE_33__ {scalar_t__* Spare; } ;
typedef  TYPE_16__* LPVOID ;
typedef  TYPE_16__ IUnknown ;
typedef  TYPE_18__ IFilterGraphImpl ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  GUID ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  CLSCTX_INPROC_SERVER ; 
 int /*<<< orphan*/  CLSID_FilterMapper2 ; 
 int /*<<< orphan*/  CloseHandle (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CoCreateInstance (int /*<<< orphan*/ *,TYPE_16__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void**) ; 
 TYPE_18__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_18__*) ; 
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DeleteCriticalSection (TYPE_21__*) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EventsQueue_Destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  EventsQueue_Init (int /*<<< orphan*/ *) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IBasicAudio_VTable ; 
 int /*<<< orphan*/  IBasicVideo_VTable ; 
 int /*<<< orphan*/  IFilterGraph2_VTable ; 
 int /*<<< orphan*/  IGraphConfig_VTable ; 
 int /*<<< orphan*/  IGraphVersion_VTable ; 
 int /*<<< orphan*/  IID_IUnknown ; 
 int /*<<< orphan*/  IInner_VTable ; 
 int /*<<< orphan*/  IMediaControl_VTable ; 
 int /*<<< orphan*/  IMediaEventEx_VTable ; 
 int /*<<< orphan*/  IMediaEventSink_VTable ; 
 int /*<<< orphan*/  IMediaFilter_VTable ; 
 int /*<<< orphan*/  IMediaPosition_VTable ; 
 int /*<<< orphan*/  IMediaSeeking_VTable ; 
 int /*<<< orphan*/  IObjectWithSite_VTable ; 
 int /*<<< orphan*/  IUnknown_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IVideoWindow_VTable ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_21__*) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  State_Stopped ; 
 int /*<<< orphan*/  TIME_FORMAT_MEDIA_TIME ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_16__*,TYPE_16__**) ; 
 void* TRUE ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

HRESULT FilterGraph_create(IUnknown *pUnkOuter, LPVOID *ppObj)
{
    IFilterGraphImpl *fimpl;
    HRESULT hr;

    TRACE("(%p,%p)\n", pUnkOuter, ppObj);

    *ppObj = NULL;

    fimpl = CoTaskMemAlloc(sizeof(*fimpl));
    fimpl->defaultclock = TRUE;
    fimpl->IUnknown_inner.lpVtbl = &IInner_VTable;
    fimpl->IFilterGraph2_iface.lpVtbl = &IFilterGraph2_VTable;
    fimpl->IMediaControl_iface.lpVtbl = &IMediaControl_VTable;
    fimpl->IMediaSeeking_iface.lpVtbl = &IMediaSeeking_VTable;
    fimpl->IBasicAudio_iface.lpVtbl = &IBasicAudio_VTable;
    fimpl->IBasicVideo2_iface.lpVtbl = &IBasicVideo_VTable;
    fimpl->IVideoWindow_iface.lpVtbl = &IVideoWindow_VTable;
    fimpl->IMediaEventEx_iface.lpVtbl = &IMediaEventEx_VTable;
    fimpl->IMediaFilter_iface.lpVtbl = &IMediaFilter_VTable;
    fimpl->IMediaEventSink_iface.lpVtbl = &IMediaEventSink_VTable;
    fimpl->IGraphConfig_iface.lpVtbl = &IGraphConfig_VTable;
    fimpl->IMediaPosition_iface.lpVtbl = &IMediaPosition_VTable;
    fimpl->IObjectWithSite_iface.lpVtbl = &IObjectWithSite_VTable;
    fimpl->IGraphVersion_iface.lpVtbl = &IGraphVersion_VTable;
    fimpl->ref = 1;
    fimpl->ppFiltersInGraph = NULL;
    fimpl->pFilterNames = NULL;
    fimpl->nFilters = 0;
    fimpl->filterCapacity = 0;
    fimpl->nameIndex = 1;
    fimpl->refClock = NULL;
    fimpl->hEventCompletion = CreateEventW(0, TRUE, FALSE, 0);
    fimpl->HandleEcComplete = TRUE;
    fimpl->HandleEcRepaint = TRUE;
    fimpl->HandleEcClockChanged = TRUE;
    fimpl->notif.hWnd = 0;
    fimpl->notif.disabled = FALSE;
    fimpl->nRenderers = 0;
    fimpl->EcCompleteCount = 0;
    fimpl->refClockProvider = NULL;
    fimpl->state = State_Stopped;
    fimpl->pSite = NULL;
    EventsQueue_Init(&fimpl->evqueue);
    InitializeCriticalSection(&fimpl->cs);
    fimpl->cs.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": IFilterGraphImpl.cs");
    fimpl->nItfCacheEntries = 0;
    memcpy(&fimpl->timeformatseek, &TIME_FORMAT_MEDIA_TIME, sizeof(GUID));
    fimpl->start_time = fimpl->pause_time = 0;
    fimpl->punkFilterMapper2 = NULL;
    fimpl->recursioncount = 0;
    fimpl->version = 0;

    if (pUnkOuter)
        fimpl->outer_unk = pUnkOuter;
    else
        fimpl->outer_unk = &fimpl->IUnknown_inner;

    /* create Filtermapper aggregated. */
    hr = CoCreateInstance(&CLSID_FilterMapper2, fimpl->outer_unk, CLSCTX_INPROC_SERVER,
            &IID_IUnknown, (void**)&fimpl->punkFilterMapper2);

    if (FAILED(hr)) {
        ERR("Unable to create filter mapper (%x)\n", hr);
        if (fimpl->punkFilterMapper2) IUnknown_Release(fimpl->punkFilterMapper2);
        CloseHandle(fimpl->hEventCompletion);
        EventsQueue_Destroy(&fimpl->evqueue);
        fimpl->cs.DebugInfo->Spare[0] = 0;
        DeleteCriticalSection(&fimpl->cs);
        CoTaskMemFree(fimpl);
        return hr;
    }

    *ppObj = &fimpl->IUnknown_inner;
    return S_OK;
}