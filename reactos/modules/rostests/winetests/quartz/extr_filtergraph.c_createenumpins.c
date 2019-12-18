#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  IBaseFilter_iface; } ;
typedef  TYPE_1__ TestFilterImpl ;
struct TYPE_11__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int refCount; int /*<<< orphan*/  synctime; TYPE_3__ IEnumPins_iface; TYPE_1__* base; int /*<<< orphan*/  (* receive_pin ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;scalar_t__ uIndex; } ;
typedef  TYPE_2__ IEnumPinsImpl ;
typedef  TYPE_3__ IEnumPins ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  (* FNOBTAINPIN ) (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;

/* Variables and functions */
 TYPE_2__* CoTaskMemAlloc (int) ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  E_POINTER ; 
 int /*<<< orphan*/  IBaseFilter_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  IEnumPinsImpl_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT createenumpins(IEnumPins ** ppEnum, FNOBTAINPIN receive_pin, TestFilterImpl *base)
{
    IEnumPinsImpl * pEnumPins;

    if (!ppEnum)
        return E_POINTER;

    pEnumPins = CoTaskMemAlloc(sizeof(IEnumPinsImpl));
    if (!pEnumPins)
    {
        *ppEnum = NULL;
        return E_OUTOFMEMORY;
    }
    pEnumPins->IEnumPins_iface.lpVtbl = &IEnumPinsImpl_Vtbl;
    pEnumPins->refCount = 1;
    pEnumPins->uIndex = 0;
    pEnumPins->receive_pin = receive_pin;
    pEnumPins->base = base;
    IBaseFilter_AddRef(&base->IBaseFilter_iface);
    *ppEnum = &pEnumPins->IEnumPins_iface;

    receive_pin(base, ~0, NULL, &pEnumPins->synctime);

    return S_OK;
}