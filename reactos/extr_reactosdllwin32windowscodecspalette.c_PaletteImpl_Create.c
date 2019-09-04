#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* DebugInfo; } ;
struct TYPE_9__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_8__ {int ref; TYPE_3__ IWICPalette_iface; TYPE_5__ lock; int /*<<< orphan*/  type; int /*<<< orphan*/ * colors; scalar_t__ count; } ;
struct TYPE_7__ {scalar_t__* Spare; } ;
typedef  TYPE_2__ PaletteImpl ;
typedef  TYPE_3__ IWICPalette ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_5__*) ; 
 int /*<<< orphan*/  PaletteImpl_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WICBitmapPaletteTypeCustom ; 

HRESULT PaletteImpl_Create(IWICPalette **palette)
{
    PaletteImpl *This;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(PaletteImpl));
    if (!This) return E_OUTOFMEMORY;

    This->IWICPalette_iface.lpVtbl = &PaletteImpl_Vtbl;
    This->ref = 1;
    This->count = 0;
    This->colors = NULL;
    This->type = WICBitmapPaletteTypeCustom;
    InitializeCriticalSection(&This->lock);
    This->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": PaletteImpl.lock");

    *palette = &This->IWICPalette_iface;

    return S_OK;
}