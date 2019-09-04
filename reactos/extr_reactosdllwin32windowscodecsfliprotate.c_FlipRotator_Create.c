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
struct TYPE_10__ {TYPE_1__* DebugInfo; } ;
struct TYPE_8__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_9__ {int ref; TYPE_2__ IWICBitmapFlipRotator_iface; TYPE_4__ lock; scalar_t__ swap_xy; scalar_t__ flip_y; scalar_t__ flip_x; int /*<<< orphan*/ * source; } ;
struct TYPE_7__ {scalar_t__* Spare; } ;
typedef  TYPE_2__ IWICBitmapFlipRotator ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_3__ FlipRotator ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  FlipRotator_Vtbl ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_4__*) ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT FlipRotator_Create(IWICBitmapFlipRotator **fliprotator)
{
    FlipRotator *This;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(FlipRotator));
    if (!This) return E_OUTOFMEMORY;

    This->IWICBitmapFlipRotator_iface.lpVtbl = &FlipRotator_Vtbl;
    This->ref = 1;
    This->source = NULL;
    This->flip_x = 0;
    This->flip_y = 0;
    This->swap_xy = 0;
    InitializeCriticalSection(&This->lock);
    This->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": FlipRotator.lock");

    *fliprotator = &This->IWICBitmapFlipRotator_iface;

    return S_OK;
}