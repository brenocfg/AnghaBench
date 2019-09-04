#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int refCount; TYPE_1__ ITfCategoryMgr_iface; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ CategoryMgr ;

/* Variables and functions */
 int /*<<< orphan*/  CLASS_E_NOAGGREGATION ; 
 int /*<<< orphan*/  CategoryMgrVtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ *) ; 

HRESULT CategoryMgr_Constructor(IUnknown *pUnkOuter, IUnknown **ppOut)
{
    CategoryMgr *This;
    if (pUnkOuter)
        return CLASS_E_NOAGGREGATION;

    This = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(CategoryMgr));
    if (This == NULL)
        return E_OUTOFMEMORY;

    This->ITfCategoryMgr_iface.lpVtbl = &CategoryMgrVtbl;
    This->refCount = 1;

    *ppOut = (IUnknown *)&This->ITfCategoryMgr_iface;
    TRACE("returning %p\n", *ppOut);
    return S_OK;
}