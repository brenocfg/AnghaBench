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
struct TYPE_6__ {int ref; TYPE_1__ IHTMLStorage_iface; int /*<<< orphan*/  dispex; } ;
typedef  int /*<<< orphan*/  IUnknown ;
typedef  TYPE_1__ IHTMLStorage ;
typedef  TYPE_2__ HTMLStorage ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  HTMLStorageVtbl ; 
 int /*<<< orphan*/  HTMLStorage_dispex ; 
 int /*<<< orphan*/  S_OK ; 
 TYPE_2__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  init_dispex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

HRESULT create_storage(IHTMLStorage **p)
{
    HTMLStorage *storage;

    storage = heap_alloc_zero(sizeof(*storage));
    if(!storage)
        return E_OUTOFMEMORY;

    storage->IHTMLStorage_iface.lpVtbl = &HTMLStorageVtbl;
    storage->ref = 1;
    init_dispex(&storage->dispex, (IUnknown*)&storage->IHTMLStorage_iface, &HTMLStorage_dispex);

    *p = &storage->IHTMLStorage_iface;
    return S_OK;
}