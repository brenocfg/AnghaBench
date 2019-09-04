#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_14__ {TYPE_2__* DebugInfo; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_13__ {int ref; TYPE_7__ IWICMetadataWriter_iface; TYPE_6__ lock; scalar_t__ item_count; int /*<<< orphan*/ * items; TYPE_3__ const* vtable; TYPE_1__ IWICPersistStream_iface; } ;
struct TYPE_12__ {int /*<<< orphan*/  clsid; } ;
struct TYPE_11__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  TYPE_3__ MetadataHandlerVtbl ;
typedef  TYPE_4__ MetadataHandler ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWICMetadataWriter_QueryInterface (TYPE_7__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IWICMetadataWriter_Release (TYPE_7__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_6__*) ; 
 int /*<<< orphan*/  MetadataHandler_PersistStream_Vtbl ; 
 int /*<<< orphan*/  MetadataHandler_Vtbl ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

HRESULT MetadataReader_Create(const MetadataHandlerVtbl *vtable, REFIID iid, void** ppv)
{
    MetadataHandler *This;
    HRESULT hr;

    TRACE("%s\n", debugstr_guid(vtable->clsid));

    *ppv = NULL;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(MetadataHandler));
    if (!This) return E_OUTOFMEMORY;

    This->IWICMetadataWriter_iface.lpVtbl = &MetadataHandler_Vtbl;
    This->IWICPersistStream_iface.lpVtbl = &MetadataHandler_PersistStream_Vtbl;
    This->ref = 1;
    This->vtable = vtable;
    This->items = NULL;
    This->item_count = 0;

    InitializeCriticalSection(&This->lock);
    This->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": MetadataHandler.lock");

    hr = IWICMetadataWriter_QueryInterface(&This->IWICMetadataWriter_iface, iid, ppv);

    IWICMetadataWriter_Release(&This->IWICMetadataWriter_iface);

    return hr;
}