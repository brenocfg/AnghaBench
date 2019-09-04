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
struct TYPE_9__ {int ref; TYPE_2__ IWICBitmapClipper_iface; TYPE_4__ lock; int /*<<< orphan*/ * source; } ;
struct TYPE_7__ {scalar_t__* Spare; } ;
typedef  TYPE_2__ IWICBitmapClipper ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  scalar_t__ DWORD_PTR ;
typedef  TYPE_3__ BitmapClipper ;

/* Variables and functions */
 int /*<<< orphan*/  BitmapClipper_Vtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_3__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  InitializeCriticalSection (TYPE_4__*) ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT BitmapClipper_Create(IWICBitmapClipper **clipper)
{
    BitmapClipper *This;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(BitmapClipper));
    if (!This) return E_OUTOFMEMORY;

    This->IWICBitmapClipper_iface.lpVtbl = &BitmapClipper_Vtbl;
    This->ref = 1;
    This->source = NULL;
    InitializeCriticalSection(&This->lock);
    This->lock.DebugInfo->Spare[0] = (DWORD_PTR)(__FILE__ ": BitmapClipper.lock");

    *clipper = &This->IWICBitmapClipper_iface;

    return S_OK;
}