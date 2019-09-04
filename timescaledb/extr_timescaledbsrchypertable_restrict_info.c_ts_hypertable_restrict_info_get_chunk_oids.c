#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ num_dimensions; } ;
struct TYPE_11__ {scalar_t__ num_slices; } ;
struct TYPE_10__ {TYPE_6__* space; } ;
struct TYPE_9__ {int num_dimensions; int /*<<< orphan*/ ** dimension_restriction; } ;
typedef  int /*<<< orphan*/  List ;
typedef  int /*<<< orphan*/  LOCKMODE ;
typedef  TYPE_1__ HypertableRestrictInfo ;
typedef  TYPE_2__ Hypertable ;
typedef  TYPE_3__ DimensionVec ;
typedef  int /*<<< orphan*/  DimensionRestrictInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * NIL ; 
 TYPE_3__* dimension_restrict_info_slices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_3__*) ; 
 scalar_t__ list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_chunk_find_all_oids (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

List *
ts_hypertable_restrict_info_get_chunk_oids(HypertableRestrictInfo *hri, Hypertable *ht,
										   LOCKMODE lockmode)
{
	int i;
	List *dimension_vecs = NIL;

	for (i = 0; i < hri->num_dimensions; i++)
	{
		DimensionRestrictInfo *dri = hri->dimension_restriction[i];
		DimensionVec *dv;

		Assert(NULL != dri);

		dv = dimension_restrict_info_slices(dri);

		Assert(dv->num_slices >= 0);

		/*
		 * If there are no matching slices in any single dimension, the result
		 * will be empty
		 */
		if (dv->num_slices == 0)
			return NIL;

		dimension_vecs = lappend(dimension_vecs, dv);
	}

	Assert(list_length(dimension_vecs) == ht->space->num_dimensions);

	return ts_chunk_find_all_oids(ht->space, dimension_vecs, lockmode);
}