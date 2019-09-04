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
struct TYPE_8__ {int ref; TYPE_4__ IWICBitmapEncoder_iface; scalar_t__ colors; scalar_t__ n_frames; void* committed; void* info_written; void* initialized; TYPE_3__ lock; int /*<<< orphan*/ * stream; } ;
struct TYPE_7__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ GifEncoder ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 void* FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GifEncoder_Vtbl ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWICBitmapEncoder_QueryInterface (TYPE_4__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IWICBitmapEncoder_Release (TYPE_4__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_3__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

HRESULT GifEncoder_CreateInstance(REFIID iid, void **ppv)
{
    GifEncoder *This;
    HRESULT ret;

    TRACE("%s,%p\n", debugstr_guid(iid), ppv);

    *ppv = NULL;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    if (!This) return E_OUTOFMEMORY;

    This->IWICBitmapEncoder_iface.lpVtbl = &GifEncoder_Vtbl;
    This->ref = 1;
    This->stream = NULL;
    InitializeCriticalSection(&This->lock);
    This->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": GifEncoder.lock");
    This->initialized = FALSE;
    This->info_written = FALSE;
    This->committed = FALSE;
    This->n_frames = 0;
    This->colors = 0;

    ret = IWICBitmapEncoder_QueryInterface(&This->IWICBitmapEncoder_iface, iid, ppv);
    IWICBitmapEncoder_Release(&This->IWICBitmapEncoder_iface);

    return ret;
}