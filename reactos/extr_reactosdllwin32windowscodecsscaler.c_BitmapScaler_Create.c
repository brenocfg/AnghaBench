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
struct TYPE_12__ {TYPE_2__* DebugInfo; } ;
struct TYPE_10__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_11__ {int ref; TYPE_3__ IWICBitmapScaler_iface; TYPE_5__ lock; scalar_t__ bpp; scalar_t__ mode; scalar_t__ src_height; scalar_t__ src_width; scalar_t__ height; scalar_t__ width; int /*<<< orphan*/ * source; TYPE_1__ IMILBitmapScaler_iface; } ;
struct TYPE_9__ {scalar_t__* Spare; } ;
typedef  TYPE_3__ IWICBitmapScaler ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;
typedef  TYPE_4__ BitmapScaler ;

/* Variables and functions */
 int /*<<< orphan*/  BitmapScaler_Vtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_4__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IMILBitmapScaler_Vtbl ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_5__*) ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT BitmapScaler_Create(IWICBitmapScaler **scaler)
{
    BitmapScaler *This;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(BitmapScaler));
    if (!This) return E_OUTOFMEMORY;

    This->IWICBitmapScaler_iface.lpVtbl = &BitmapScaler_Vtbl;
    This->IMILBitmapScaler_iface.lpVtbl = &IMILBitmapScaler_Vtbl;
    This->ref = 1;
    This->source = NULL;
    This->width = 0;
    This->height = 0;
    This->src_width = 0;
    This->src_height = 0;
    This->mode = 0;
    This->bpp = 0;
    InitializeCriticalSection(&This->lock);
    This->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": BitmapScaler.lock");

    *scaler = &This->IWICBitmapScaler_iface;

    return S_OK;
}