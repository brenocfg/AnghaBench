#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_5__ {int ref; TYPE_3__ IMMDeviceEnumerator_iface; } ;
typedef  int /*<<< orphan*/  REFIID ;
typedef  TYPE_1__ MMDevEnumImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IMMDeviceEnumerator_QueryInterface (TYPE_3__*,int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  MMDevEnumVtbl ; 
 TYPE_1__* MMDevEnumerator ; 
 int /*<<< orphan*/  eCapture ; 
 int /*<<< orphan*/  eRender ; 
 int /*<<< orphan*/  load_devices_from_reg () ; 
 int /*<<< orphan*/  load_driver_devices (int /*<<< orphan*/ ) ; 

HRESULT MMDevEnum_Create(REFIID riid, void **ppv)
{
    MMDevEnumImpl *This = MMDevEnumerator;

    if (!This)
    {
        This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
        *ppv = NULL;
        if (!This)
            return E_OUTOFMEMORY;
        This->ref = 1;
        This->IMMDeviceEnumerator_iface.lpVtbl = &MMDevEnumVtbl;
        MMDevEnumerator = This;

        load_devices_from_reg();
        load_driver_devices(eRender);
        load_driver_devices(eCapture);
    }
    return IMMDeviceEnumerator_QueryInterface(&This->IMMDeviceEnumerator_iface, riid, ppv);
}