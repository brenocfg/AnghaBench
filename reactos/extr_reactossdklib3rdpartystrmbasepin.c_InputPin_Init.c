#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/  const* lpVtbl; } ;
struct TYPE_9__ {int refCount; double dRate; TYPE_1__ IPin_iface; int /*<<< orphan*/ * pFuncsTable; int /*<<< orphan*/  mtCurrent; int /*<<< orphan*/  pinInfo; scalar_t__ tStop; scalar_t__ tStart; int /*<<< orphan*/  pCritSec; int /*<<< orphan*/ * pConnectedTo; } ;
struct TYPE_12__ {int /*<<< orphan*/  end_of_stream; int /*<<< orphan*/  flushing; TYPE_3__ IMemInputPin_iface; TYPE_2__ pin; int /*<<< orphan*/ * preferred_allocator; int /*<<< orphan*/ * pAllocator; TYPE_4__ const* pFuncsTable; } ;
struct TYPE_11__ {int /*<<< orphan*/  base; } ;
typedef  int /*<<< orphan*/  PIN_INFO ;
typedef  int /*<<< orphan*/  LPCRITICAL_SECTION ;
typedef  int /*<<< orphan*/  IPinVtbl ;
typedef  int /*<<< orphan*/  IMemAllocator ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ BaseInputPinFuncTable ;
typedef  TYPE_5__ BaseInputPin ;
typedef  int /*<<< orphan*/  AM_MEDIA_TYPE ;

/* Variables and functions */
 int /*<<< orphan*/  Copy_PinInfo (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IMemAllocator_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  MemInputPin_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  ZeroMemory (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static HRESULT InputPin_Init(const IPinVtbl *InputPin_Vtbl, const PIN_INFO * pPinInfo,
                             const BaseInputPinFuncTable* vtbl,
                             LPCRITICAL_SECTION pCritSec, IMemAllocator *allocator, BaseInputPin * pPinImpl)
{
    TRACE("\n");

    /* Common attributes */
    pPinImpl->pin.refCount = 1;
    pPinImpl->pin.pConnectedTo = NULL;
    pPinImpl->pin.pCritSec = pCritSec;
    pPinImpl->pin.tStart = 0;
    pPinImpl->pin.tStop = 0;
    pPinImpl->pin.dRate = 1.0;
    Copy_PinInfo(&pPinImpl->pin.pinInfo, pPinInfo);
    ZeroMemory(&pPinImpl->pin.mtCurrent, sizeof(AM_MEDIA_TYPE));
    pPinImpl->pin.pFuncsTable = &vtbl->base;

    /* Input pin attributes */
    pPinImpl->pFuncsTable = vtbl;
    pPinImpl->pAllocator = pPinImpl->preferred_allocator = allocator;
    if (pPinImpl->preferred_allocator)
        IMemAllocator_AddRef(pPinImpl->preferred_allocator);
    pPinImpl->pin.IPin_iface.lpVtbl = InputPin_Vtbl;
    pPinImpl->IMemInputPin_iface.lpVtbl = &MemInputPin_Vtbl;
    pPinImpl->flushing = pPinImpl->end_of_stream = FALSE;

    return S_OK;
}