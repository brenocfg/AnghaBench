#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * lpVtbl; } ;
struct enumvar {int refs; TYPE_1__ IEnumVARIANT_iface; int /*<<< orphan*/ * objectenum; } ;
typedef  int /*<<< orphan*/  IEnumWbemClassObject ;
typedef  TYPE_1__ IEnumVARIANT ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  IEnumWbemClassObject_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  enumvar_vtbl ; 
 struct enumvar* heap_alloc (int) ; 

__attribute__((used)) static HRESULT EnumVARIANT_create( IEnumWbemClassObject *objectenum, IEnumVARIANT **obj )
{
    struct enumvar *enumvar;

    if (!(enumvar = heap_alloc( sizeof(*enumvar) ))) return E_OUTOFMEMORY;
    enumvar->IEnumVARIANT_iface.lpVtbl = &enumvar_vtbl;
    enumvar->refs = 1;
    enumvar->objectenum = objectenum;
    IEnumWbemClassObject_AddRef( enumvar->objectenum );

    *obj = &enumvar->IEnumVARIANT_iface;
    TRACE( "returning iface %p\n", *obj );
    return S_OK;
}