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
struct TYPE_5__ {int ref; TYPE_2__ IMMDeviceCollection_iface; int /*<<< orphan*/  state; int /*<<< orphan*/  flow; } ;
typedef  TYPE_1__ MMDevColImpl ;
typedef  TYPE_2__ IMMDeviceCollection ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  int /*<<< orphan*/  EDataFlow ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_1__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  MMDevColVtbl ; 
 int /*<<< orphan*/  S_OK ; 

__attribute__((used)) static HRESULT MMDevCol_Create(IMMDeviceCollection **ppv, EDataFlow flow, DWORD state)
{
    MMDevColImpl *This;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(*This));
    *ppv = NULL;
    if (!This)
        return E_OUTOFMEMORY;
    This->IMMDeviceCollection_iface.lpVtbl = &MMDevColVtbl;
    This->ref = 1;
    This->flow = flow;
    This->state = state;
    *ppv = &This->IMMDeviceCollection_iface;
    return S_OK;
}