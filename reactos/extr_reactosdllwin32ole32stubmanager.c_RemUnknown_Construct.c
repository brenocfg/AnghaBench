#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int refs; TYPE_2__ IRemUnknown_iface; } ;
typedef  TYPE_1__ RemUnknown ;
typedef  TYPE_2__ IRemUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RemUnknown_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT RemUnknown_Construct(IRemUnknown **ppRemUnknown)
{
    RemUnknown *This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));

    if (!This) return E_OUTOFMEMORY;

    This->IRemUnknown_iface.lpVtbl = &RemUnknown_Vtbl;
    This->refs = 1;

    *ppRemUnknown = &This->IRemUnknown_iface;
    return S_OK;
}