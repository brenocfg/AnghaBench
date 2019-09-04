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
struct list {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/ * lpVtbl; } ;
struct ciffenum_groups {int ref; TYPE_1__ IEnumCifGroups_iface; struct list* position; struct list* start; int /*<<< orphan*/ * file; } ;
typedef  TYPE_1__ IEnumCifGroups ;
typedef  int /*<<< orphan*/  ICifFile ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  E_OUTOFMEMORY ; 
 int /*<<< orphan*/  ICifFile_AddRef (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  S_OK ; 
 int /*<<< orphan*/  enum_groupsVtbl ; 
 struct ciffenum_groups* heap_alloc_zero (int) ; 

__attribute__((used)) static HRESULT enum_groups_create(ICifFile *file, struct list *start, IEnumCifGroups **iface)
{
    struct ciffenum_groups *enumerator;

    enumerator = heap_alloc_zero(sizeof(*enumerator));
    if (!enumerator) return E_OUTOFMEMORY;

    enumerator->IEnumCifGroups_iface.lpVtbl = &enum_groupsVtbl;
    enumerator->ref      = 1;
    enumerator->file     = file;
    enumerator->start    = start;
    enumerator->position = start;

    ICifFile_AddRef(file);

    *iface = &enumerator->IEnumCifGroups_iface;
    return S_OK;
}