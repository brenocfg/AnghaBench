#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_7__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
struct TYPE_22__ {int dwSize; int /*<<< orphan*/  dwFlags; } ;
struct TYPE_20__ {int /*<<< orphan*/  IBaseFilter_iface; } ;
struct TYPE_16__ {TYPE_4__ filter; } ;
struct TYPE_19__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_18__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_17__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_21__ {TYPE_15__ renderer; int /*<<< orphan*/  blocked; int /*<<< orphan*/  dsound; TYPE_3__ IAMFilterMiscFlags_iface; TYPE_2__ IAMDirectSound_iface; TYPE_1__ IReferenceClock_iface; int /*<<< orphan*/  basicAudio; } ;
typedef  TYPE_5__* LPVOID ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  IDirectSoundBuffer ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  DWORD_PTR ;
typedef  TYPE_5__ DSoundRenderImpl ;
typedef  TYPE_7__ DSBUFFERDESC ;

/* Variables and functions */
 int /*<<< orphan*/  BaseFuncTable ; 
 int /*<<< orphan*/  BaseRendererImpl_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BaseRenderer_Init (TYPE_15__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BasicAudio_Init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CLSID_DSoundRender ; 
 TYPE_5__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_5__*) ; 
 int /*<<< orphan*/  CreateEventW (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DSBCAPS_PRIMARYBUFFER ; 
 int /*<<< orphan*/  DSBPLAY_LOOPING ; 
 int /*<<< orphan*/  DSSCL_PRIORITY ; 
 int /*<<< orphan*/  DSoundRender_Vtbl ; 
 int /*<<< orphan*/  DirectSoundCreate8 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetDesktopWindow () ; 
 int /*<<< orphan*/  GetLastError () ; 
 int /*<<< orphan*/  HRESULT_FROM_WIN32 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IAMDirectSound_Vtbl ; 
 int /*<<< orphan*/  IAMFilterMiscFlags_Vtbl ; 
 int /*<<< orphan*/  IBaseFilter_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IBasicAudio_Vtbl ; 
 int /*<<< orphan*/  IDirectSound8_CreateSoundBuffer (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IDirectSound8_SetCooperativeLevel (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Play (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IDirectSoundBuffer_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IReferenceClock_Vtbl ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,TYPE_5__**) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  ZeroMemory (TYPE_5__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_7__*,int /*<<< orphan*/ ,int) ; 

HRESULT DSoundRender_create(IUnknown * pUnkOuter, LPVOID * ppv)
{
    HRESULT hr;
    DSoundRenderImpl * pDSoundRender;

    TRACE("(%p, %p)\n", pUnkOuter, ppv);

    *ppv = NULL;

    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    pDSoundRender = CoTaskMemAlloc(sizeof(DSoundRenderImpl));
    if (!pDSoundRender)
        return E_OUTOFMEMORY;
    ZeroMemory(pDSoundRender, sizeof(DSoundRenderImpl));

    hr = BaseRenderer_Init(&pDSoundRender->renderer, &DSoundRender_Vtbl, (IUnknown*)pDSoundRender, &CLSID_DSoundRender, (DWORD_PTR)(__FILE__ ": DSoundRenderImpl.csFilter"), &BaseFuncTable);

    BasicAudio_Init(&pDSoundRender->basicAudio,&IBasicAudio_Vtbl);
    pDSoundRender->IReferenceClock_iface.lpVtbl = &IReferenceClock_Vtbl;
    pDSoundRender->IAMDirectSound_iface.lpVtbl = &IAMDirectSound_Vtbl;
    pDSoundRender->IAMFilterMiscFlags_iface.lpVtbl = &IAMFilterMiscFlags_Vtbl;

    if (SUCCEEDED(hr))
    {
        hr = DirectSoundCreate8(NULL, &pDSoundRender->dsound, NULL);
        if (FAILED(hr))
            ERR("Cannot create Direct Sound object (%x)\n", hr);
        else
            hr = IDirectSound8_SetCooperativeLevel(pDSoundRender->dsound, GetDesktopWindow(), DSSCL_PRIORITY);
        if (SUCCEEDED(hr)) {
            IDirectSoundBuffer *buf;
            DSBUFFERDESC buf_desc;
            memset(&buf_desc,0,sizeof(DSBUFFERDESC));
            buf_desc.dwSize = sizeof(DSBUFFERDESC);
            buf_desc.dwFlags = DSBCAPS_PRIMARYBUFFER;
            hr = IDirectSound8_CreateSoundBuffer(pDSoundRender->dsound, &buf_desc, &buf, NULL);
            if (SUCCEEDED(hr)) {
                IDirectSoundBuffer_Play(buf, 0, 0, DSBPLAY_LOOPING);
                IDirectSoundBuffer_Release(buf);
            }
            hr = S_OK;
        }
    }

    if (SUCCEEDED(hr))
    {
        pDSoundRender->blocked = CreateEventW(NULL, TRUE, TRUE, NULL);

        if (!pDSoundRender->blocked || FAILED(hr))
        {
            IBaseFilter_Release(&pDSoundRender->renderer.filter.IBaseFilter_iface);
            return HRESULT_FROM_WIN32(GetLastError());
        }

        *ppv = pDSoundRender;
    }
    else
    {
        BaseRendererImpl_Release(&pDSoundRender->renderer.filter.IBaseFilter_iface);
        CoTaskMemFree(pDSoundRender);
    }

    return hr;
}