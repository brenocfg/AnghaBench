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
struct TYPE_10__ {int ref; TYPE_5__ IWICBitmapDecoder_iface; TYPE_4__ lock; int /*<<< orphan*/ * imagebits; int /*<<< orphan*/ * stream; int /*<<< orphan*/  initialized; TYPE_1__ IWICBitmapFrameDecode_iface; } ;
typedef  TYPE_3__ TgaDecoder ;
struct TYPE_9__ {scalar_t__* Spare; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_QueryInterface (TYPE_5__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  IWICBitmapDecoder_Release (TYPE_5__*) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_4__*) ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  TgaDecoder_Frame_Vtbl ; 
 int /*<<< orphan*/  TgaDecoder_Vtbl ; 
 int /*<<< orphan*/  debugstr_guid (int /*<<< orphan*/ ) ; 

HRESULT TgaDecoder_CreateInstance(REFIID iid, void** ppv)
{
    TgaDecoder *This;
    HRESULT ret;

    TRACE("(%s,%p)\n", debugstr_guid(iid), ppv);

    *ppv = NULL;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(TgaDecoder));
    if (!This) return E_OUTOFMEMORY;

    This->IWICBitmapDecoder_iface.lpVtbl = &TgaDecoder_Vtbl;
    This->IWICBitmapFrameDecode_iface.lpVtbl = &TgaDecoder_Frame_Vtbl;
    This->ref = 1;
    This->initialized = FALSE;
    This->stream = NULL;
    This->imagebits = NULL;
    InitializeCriticalSection(&This->lock);
    This->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": TgaDecoder.lock");

    ret = IWICBitmapDecoder_QueryInterface(&This->IWICBitmapDecoder_iface, iid, ppv);
    IWICBitmapDecoder_Release(&This->IWICBitmapDecoder_iface);

    return ret;
}