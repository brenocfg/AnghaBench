#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {TYPE_1__* DebugInfo; } ;
struct TYPE_8__ {int ref; TYPE_4__ IPropertyStoreCache_iface; int /*<<< orphan*/  formats; TYPE_3__ lock; } ;
struct TYPE_7__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  TYPE_2__ PropertyStore ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IPropertyStoreCache_QueryInterface (TYPE_4__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IPropertyStoreCache_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_3__*) ; 
 int /*<<< orphan*/  PropertyStore_Vtbl ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_init (int /*<<< orphan*/ *) ; 

HRESULT PropertyStore_CreateInstance(IUnknown *pUnkOuter, REFIID iid, void** ppv)
{
    PropertyStore *This;
    HRESULT ret;

    TRACE("(%p,%s,%p)\n", pUnkOuter, debugstr_guid(iid), ppv);

    *ppv = NULL;

    if (pUnkOuter) return CLASS_E_NOAGGREGATION;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(PropertyStore));
    if (!This) return E_OUTOFMEMORY;

    This->IPropertyStoreCache_iface.lpVtbl = &PropertyStore_Vtbl;
    This->ref = 1;
    InitializeCriticalSection(&This->lock);
    This->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": PropertyStore.lock");
    list_init(&This->formats);

    ret = IPropertyStoreCache_QueryInterface(&This->IPropertyStoreCache_iface, iid, ppv);
    IPropertyStoreCache_Release(&This->IPropertyStoreCache_iface);

    return ret;
}