#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct objectset {int refs; TYPE_1__ ISWbemObjectSet_iface; int /*<<< orphan*/ * objectenum; int /*<<< orphan*/  count; } ;
typedef  TYPE_1__ ISWbemObjectSet ;
typedef  int /*<<< orphan*/  IEnumWbemClassObject ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IEnumWbemClassObject_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  get_object_count (int /*<<< orphan*/ *) ; 
 struct objectset* heap_alloc (int) ; 
 int /*<<< orphan*/  objectset_vtbl ; 

__attribute__((used)) static HRESULT SWbemObjectSet_create( IEnumWbemClassObject *wbem_objectenum, ISWbemObjectSet **obj )
{
    struct objectset *objectset;

    TRACE( "%p, %p\n", obj, wbem_objectenum );

    if (!(objectset = heap_alloc( sizeof(*objectset) ))) return E_OUTOFMEMORY;
    objectset->ISWbemObjectSet_iface.lpVtbl = &objectset_vtbl;
    objectset->refs = 1;
    objectset->objectenum = wbem_objectenum;
    IEnumWbemClassObject_AddRef( objectset->objectenum );
    objectset->count = get_object_count( objectset->objectenum );

    *obj = &objectset->ISWbemObjectSet_iface;
    TRACE( "returning iface %p\n", *obj );
    return S_OK;
}