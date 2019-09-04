#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  IPin_iface; } ;
struct TYPE_17__ {TYPE_1__ pin; } ;
struct TYPE_14__ {int pfnCheckMediaType; } ;
struct TYPE_16__ {TYPE_2__ base; } ;
struct TYPE_15__ {scalar_t__ dir; } ;
typedef  TYPE_3__ PIN_INFO ;
typedef  int /*<<< orphan*/  LPCRITICAL_SECTION ;
typedef  int LONG ;
typedef  int /*<<< orphan*/  IPinVtbl ;
typedef  int /*<<< orphan*/  IPin ;
typedef  int /*<<< orphan*/  IMemAllocator ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_4__ BaseInputPinFuncTable ;
typedef  TYPE_5__ BaseInputPin ;

/* Variables and functions */
 TYPE_5__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  CoTaskMemFree (TYPE_5__*) ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 int /*<<< orphan*/  E_FAIL ; 
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  InputPin_Init (int /*<<< orphan*/  const*,TYPE_3__ const*,TYPE_4__ const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_5__*) ; 
 scalar_t__ PINDIR_INPUT ; 
 scalar_t__ SUCCEEDED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  assert (int) ; 

HRESULT BaseInputPin_Construct(const IPinVtbl *InputPin_Vtbl, LONG inputpin_size, const PIN_INFO * pPinInfo,
                               const BaseInputPinFuncTable* vtbl,
                               LPCRITICAL_SECTION pCritSec, IMemAllocator *allocator, IPin ** ppPin)
{
    BaseInputPin * pPinImpl;

    *ppPin = NULL;

    assert(inputpin_size >= sizeof(BaseInputPin));
    assert(vtbl->base.pfnCheckMediaType);

    if (pPinInfo->dir != PINDIR_INPUT)
    {
        ERR("Pin direction(%x) != PINDIR_INPUT\n", pPinInfo->dir);
        return E_INVALIDARG;
    }

    pPinImpl = CoTaskMemAlloc(inputpin_size);

    if (!pPinImpl)
        return E_OUTOFMEMORY;

    if (SUCCEEDED(InputPin_Init(InputPin_Vtbl, pPinInfo, vtbl, pCritSec, allocator, pPinImpl)))
    {
        *ppPin = &pPinImpl->pin.IPin_iface;
        return S_OK;
    }

    CoTaskMemFree(pPinImpl);
    return E_FAIL;
}