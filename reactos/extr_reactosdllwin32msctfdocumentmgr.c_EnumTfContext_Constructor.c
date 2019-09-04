#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int refCount; TYPE_1__ IEnumTfContexts_iface; int /*<<< orphan*/ * docmgr; } ;
typedef  TYPE_1__ IEnumTfContexts ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ EnumTfContext ;
typedef  int /*<<< orphan*/  DocumentMgr ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IEnumTfContexts_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 

__attribute__((used)) static HRESULT EnumTfContext_Constructor(DocumentMgr *mgr, IEnumTfContexts **ppOut)
{
    EnumTfContext *This;

    This = HeapAlloc(GetProcessHeap(),HEAP_ZERO_MEMORY,sizeof(EnumTfContext));
    if (This == NULL)
        return E_OUTOFMEMORY;

    This->IEnumTfContexts_iface.lpVtbl = &IEnumTfContexts_Vtbl;
    This->refCount = 1;
    This->docmgr = mgr;

    *ppOut = &This->IEnumTfContexts_iface;
    TRACE("returning %p\n", *ppOut);
    return S_OK;
}