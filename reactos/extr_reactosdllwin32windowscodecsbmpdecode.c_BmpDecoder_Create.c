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
struct TYPE_12__ {TYPE_3__* DebugInfo; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int ref; int packed; int icoframe; TYPE_5__ lock; int /*<<< orphan*/ * imagedata; int /*<<< orphan*/ * stream; int /*<<< orphan*/  initialized; TYPE_2__ IWICBitmapFrameDecode_iface; TYPE_1__ IWICBitmapDecoder_iface; } ;
struct TYPE_10__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;
typedef  TYPE_4__ BmpDecoder ;

/* Variables and functions */
 int /*<<< orphan*/  BmpDecoder_FrameVtbl ; 
 int /*<<< orphan*/  BmpDecoder_Vtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_5__*) ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT BmpDecoder_Create(int packed, int icoframe, BmpDecoder **ppDecoder)
{
    BmpDecoder *This;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(BmpDecoder));
    if (!This) return E_OUTOFMEMORY;

    This->IWICBitmapDecoder_iface.lpVtbl = &BmpDecoder_Vtbl;
    This->IWICBitmapFrameDecode_iface.lpVtbl = &BmpDecoder_FrameVtbl;
    This->ref = 1;
    This->initialized = FALSE;
    This->stream = NULL;
    This->imagedata = NULL;
    InitializeCriticalSection(&This->lock);
    This->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": BmpDecoder.lock");
    This->packed = packed;
    This->icoframe = icoframe;

    *ppDecoder = This;

    return S_OK;
}