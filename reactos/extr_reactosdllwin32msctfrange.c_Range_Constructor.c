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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int refCount; TYPE_2__ ITfRange_iface; void* anchorEnd; void* anchorStart; void* lockType; int /*<<< orphan*/ * pITextStoreACP; int /*<<< orphan*/ * pITfContext; } ;
typedef  TYPE_1__ Range ;
typedef  TYPE_2__ ITfRange ;
typedef  int /*<<< orphan*/  ITfContext ;
typedef  int /*<<< orphan*/  ITextStoreACP ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  void* DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Range_RangeVtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 

HRESULT Range_Constructor(ITfContext *context, ITextStoreACP *textstore, DWORD lockType, DWORD anchorStart, DWORD anchorEnd, ITfRange **ppOut)
{
    Range *This;

    This = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(Range));
    if (This == NULL)
        return E_OUTOFMEMORY;

    TRACE("(%p) %p %p\n",This, context, textstore);

    This->ITfRange_iface.lpVtbl = &Range_RangeVtbl;
    This->refCount = 1;
    This->pITfContext = context;
    This->pITextStoreACP = textstore;
    This->lockType = lockType;
    This->anchorStart = anchorStart;
    This->anchorEnd = anchorEnd;

    *ppOut = &This->ITfRange_iface;
    TRACE("returning %p\n", *ppOut);

    return S_OK;
}