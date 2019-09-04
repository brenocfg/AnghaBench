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
struct TYPE_5__ {int refCount; TYPE_1__ ITextStoreACP_iface; } ;
typedef  TYPE_2__ TextStoreACP ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TextStoreACP_TextStoreACPVtbl ; 

__attribute__((used)) static HRESULT TextStoreACP_Constructor(IUnknown **ppOut)
{
    TextStoreACP *This;

    This = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(TextStoreACP));
    if (This == NULL)
        return E_OUTOFMEMORY;

    This->ITextStoreACP_iface.lpVtbl = &TextStoreACP_TextStoreACPVtbl;
    This->refCount = 1;

    *ppOut = (IUnknown*)&This->ITextStoreACP_iface;
    return S_OK;
}