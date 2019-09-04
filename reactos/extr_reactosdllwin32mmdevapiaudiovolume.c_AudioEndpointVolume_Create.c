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
struct TYPE_5__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_6__ {int ref; TYPE_1__ IAudioEndpointVolumeEx_iface; } ;
typedef  int /*<<< orphan*/  MMDevice ;
typedef  TYPE_1__ IAudioEndpointVolumeEx ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ AEVImpl ;

/* Variables and functions */
 int /*<<< orphan*/  AEVImpl_Vtbl ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 

HRESULT AudioEndpointVolume_Create(MMDevice *parent, IAudioEndpointVolumeEx **ppv)
{
    AEVImpl *This;

    *ppv = NULL;
    This = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(*This));
    if (!This)
        return E_OUTOFMEMORY;
    This->IAudioEndpointVolumeEx_iface.lpVtbl = &AEVImpl_Vtbl;
    This->ref = 1;

    *ppv = &This->IAudioEndpointVolumeEx_iface;
    return S_OK;
}