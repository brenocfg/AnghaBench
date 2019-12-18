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
struct TYPE_5__ {int ref; TYPE_2__ IDataObject_iface; } ;
typedef  TYPE_1__ IDataObjectImpl ;
typedef  TYPE_2__ IDataObject ;

/* Variables and functions */
 int /*<<< orphan*/  IDataObjectImpl_Vtbl ; 
 TYPE_1__* heap_alloc (int) ; 

__attribute__((used)) static IDataObject* IDataObjectImpl_Construct(void)
{
    IDataObjectImpl *obj;

    obj = heap_alloc(sizeof(*obj));
    obj->IDataObject_iface.lpVtbl = &IDataObjectImpl_Vtbl;
    obj->ref = 1;

    return &obj->IDataObject_iface;
}