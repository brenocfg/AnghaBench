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
struct TYPE_5__ {int ref; TYPE_2__ IWshCollection_iface; int /*<<< orphan*/  classinfo; } ;
typedef  TYPE_1__ WshCollection ;
typedef  TYPE_2__ IWshCollection ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IID_IWshCollection ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  WshCollectionVtbl ; 
 TYPE_1__* heap_alloc (int) ; 
 int /*<<< orphan*/  init_classinfo (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static HRESULT WshCollection_Create(IWshCollection **collection)
{
    WshCollection *This;

    This = heap_alloc(sizeof(*This));
    if (!This) return E_OUTOFMEMORY;

    This->IWshCollection_iface.lpVtbl = &WshCollectionVtbl;
    This->ref = 1;

    init_classinfo(&IID_IWshCollection, (IUnknown *)&This->IWshCollection_iface, &This->classinfo);
    *collection = &This->IWshCollection_iface;

    return S_OK;
}