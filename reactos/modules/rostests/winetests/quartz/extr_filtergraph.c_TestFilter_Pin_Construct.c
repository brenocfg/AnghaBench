#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  const* lpVtbl; } ;
struct TYPE_5__ {int refCount; TYPE_2__ IPin_iface; int /*<<< orphan*/  mtCurrent; int /*<<< orphan*/  pinInfo; int /*<<< orphan*/  pCritSec; int /*<<< orphan*/ * pConnectedTo; } ;
typedef  int /*<<< orphan*/  PIN_INFO ;
typedef  int /*<<< orphan*/  LPCRITICAL_SECTION ;
typedef  TYPE_1__ ITestPinImpl ;
typedef  int /*<<< orphan*/  IPinVtbl ;
typedef  TYPE_2__ IPin ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  AM_MEDIA_TYPE ;

/* Variables and functions */
 TYPE_1__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  Copy_PinInfo (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT TestFilter_Pin_Construct(const IPinVtbl *Pin_Vtbl, const PIN_INFO * pPinInfo, AM_MEDIA_TYPE *pinmt,
                                        LPCRITICAL_SECTION pCritSec, IPin ** ppPin)
{
    ITestPinImpl * pPinImpl;

    *ppPin = NULL;

    pPinImpl = CoTaskMemAlloc(sizeof(ITestPinImpl));

    if (!pPinImpl)
        return E_OUTOFMEMORY;

    pPinImpl->refCount = 1;
    pPinImpl->pConnectedTo = NULL;
    pPinImpl->pCritSec = pCritSec;
    Copy_PinInfo(&pPinImpl->pinInfo, pPinInfo);
    pPinImpl->mtCurrent = *pinmt;

    pPinImpl->IPin_iface.lpVtbl = Pin_Vtbl;

    *ppPin = &pPinImpl->IPin_iface;
    return S_OK;
}