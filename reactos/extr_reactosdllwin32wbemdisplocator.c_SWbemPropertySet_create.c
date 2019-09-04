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
struct propertyset {int refs; TYPE_1__ ISWbemPropertySet_iface; int /*<<< orphan*/ * object; } ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  TYPE_1__ ISWbemPropertySet ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IWbemClassObject_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 struct propertyset* heap_alloc (int) ; 
 int /*<<< orphan*/  propertyset_vtbl ; 

__attribute__((used)) static HRESULT SWbemPropertySet_create( IWbemClassObject *wbem_object, ISWbemPropertySet **obj )
{
    struct propertyset *propertyset;

    TRACE( "%p, %p\n", obj, wbem_object );

    if (!(propertyset = heap_alloc( sizeof(*propertyset) ))) return E_OUTOFMEMORY;
    propertyset->ISWbemPropertySet_iface.lpVtbl = &propertyset_vtbl;
    propertyset->refs = 1;
    propertyset->object = wbem_object;
    IWbemClassObject_AddRef( propertyset->object );
    *obj = &propertyset->ISWbemPropertySet_iface;

    TRACE( "returning iface %p\n", *obj );
    return S_OK;
}