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
struct object {int refs; TYPE_1__ ISWbemObject_iface; int /*<<< orphan*/  last_dispid_method; int /*<<< orphan*/  last_dispid; scalar_t__ nb_members; int /*<<< orphan*/ * members; int /*<<< orphan*/ * object; } ;
typedef  int /*<<< orphan*/  IWbemClassObject ;
typedef  TYPE_1__ ISWbemObject ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DISPID_BASE ; 
 int /*<<< orphan*/  DISPID_BASE_METHOD ; 
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IWbemClassObject_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,...) ; 
 struct object* heap_alloc (int) ; 
 int /*<<< orphan*/  object_vtbl ; 

__attribute__((used)) static HRESULT SWbemObject_create( IWbemClassObject *wbem_object, ISWbemObject **obj )
{
    struct object *object;

    TRACE( "%p, %p\n", obj, wbem_object );

    if (!(object = heap_alloc( sizeof(*object) ))) return E_OUTOFMEMORY;
    object->ISWbemObject_iface.lpVtbl = &object_vtbl;
    object->refs = 1;
    object->object = wbem_object;
    IWbemClassObject_AddRef( object->object );
    object->members = NULL;
    object->nb_members = 0;
    object->last_dispid = DISPID_BASE;
    object->last_dispid_method = DISPID_BASE_METHOD;

    *obj = &object->ISWbemObject_iface;
    TRACE( "returning iface %p\n", *obj );
    return S_OK;
}