#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ULONG ;
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int ref; TYPE_1__ IEnumMoniker_iface; int /*<<< orphan*/ * moniker_list; int /*<<< orphan*/  pos; } ;
typedef  int /*<<< orphan*/  InterfaceList ;
typedef  TYPE_1__ IEnumMoniker ;
typedef  int /*<<< orphan*/  HRESULT ;
typedef  TYPE_2__ EnumMonikerImpl ;

/* Variables and functions */
 int /*<<< orphan*/  E_INVALIDARG ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  VT_EnumMonikerImpl ; 

__attribute__((used)) static HRESULT EnumMonikerImpl_CreateEnumROTMoniker(InterfaceList *moniker_list,
                                                 ULONG current_pos,
                                                 IEnumMoniker **ppenumMoniker)
{
    EnumMonikerImpl* This = NULL;

    if (!ppenumMoniker)
        return E_INVALIDARG;

    This = HeapAlloc(GetProcessHeap(), 0, sizeof(EnumMonikerImpl));
    if (!This) return E_OUTOFMEMORY;

    TRACE("(%p)\n", This);

    /* initialize the virtual table function */
    This->IEnumMoniker_iface.lpVtbl = &VT_EnumMonikerImpl;

    /* the initial reference is set to "1" */
    This->ref = 1;			/* set the ref count to one         */
    This->pos = current_pos;		/* Set the list start posn */
    This->moniker_list = moniker_list;

    *ppenumMoniker =  &This->IEnumMoniker_iface;

    return S_OK;
}