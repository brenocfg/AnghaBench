#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {TYPE_2__* DebugInfo; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_10__ {int ref; TYPE_5__ IWICBitmapDecoder_iface; TYPE_4__ lock; scalar_t__ current_frame; int /*<<< orphan*/ * gif; int /*<<< orphan*/  initialized; int /*<<< orphan*/ * stream; TYPE_1__ IWICMetadataBlockReader_iface; } ;
struct TYPE_9__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ GifDecoder ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  GifDecoder_BlockVtbl ; 
 int /*<<< orphan*/  GifDecoder_Vtbl ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_QueryInterface (TYPE_5__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_Release (TYPE_5__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_4__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

HRESULT GifDecoder_CreateInstance(REFIID iid, void** ppv)
{
    GifDecoder *This;
    HRESULT ret;

    TRACE("(%s,%p)\n", debugstr_guid(iid), ppv);

    *ppv = NULL;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(GifDecoder));
    if (!This) return E_OUTOFMEMORY;

    This->IWICBitmapDecoder_iface.lpVtbl = &GifDecoder_Vtbl;
    This->IWICMetadataBlockReader_iface.lpVtbl = &GifDecoder_BlockVtbl;
    This->stream = NULL;
    This->ref = 1;
    This->initialized = FALSE;
    This->gif = NULL;
    This->current_frame = 0;
    InitializeCriticalSection(&This->lock);
    This->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": GifDecoder.lock");

    ret = IWICBitmapDecoder_QueryInterface(&This->IWICBitmapDecoder_iface, iid, ppv);
    IWICBitmapDecoder_Release(&This->IWICBitmapDecoder_iface);

    return ret;
}