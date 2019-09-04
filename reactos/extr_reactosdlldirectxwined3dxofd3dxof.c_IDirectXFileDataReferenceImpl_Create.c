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
struct TYPE_6__ {int /*<<< orphan*/ * lpVtbl; } ;
struct TYPE_7__ {int ref; TYPE_1__ IDirectXFileDataReference_iface; } ;
typedef  TYPE_2__ IDirectXFileDataReferenceImpl ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DXFILEERR_BADALLOC ; 
 int /*<<< orphan*/  GetProcessHeap () ; 
 int /*<<< orphan*/  HEAP_ZERO_MEMORY ; 
 TYPE_2__* HeapAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  IDirectXFileDataReference_Vtbl ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__**) ; 

__attribute__((used)) static HRESULT IDirectXFileDataReferenceImpl_Create(IDirectXFileDataReferenceImpl** ppObj)
{
    IDirectXFileDataReferenceImpl* object;

    TRACE("(%p)\n", ppObj);

    object = HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(IDirectXFileDataReferenceImpl));
    if (!object)
        return DXFILEERR_BADALLOC;

    object->IDirectXFileDataReference_iface.lpVtbl = &IDirectXFileDataReference_Vtbl;
    object->ref = 1;

    *ppObj = object;

    return S_OK;
}