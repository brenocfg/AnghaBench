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
struct TYPE_7__ {scalar_t__ num_slices; } ;
struct TYPE_6__ {int num_dimensions; int /*<<< orphan*/ ** dimension_restriction; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_1__ HypertableRestrictInfo ;
typedef  TYPE_2__ DimensionVec ;
typedef  int /*<<< orphan*/  DimensionRestrictInfo ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/ * NIL ; 
 TYPE_2__* dimension_restrict_info_slices (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lappend (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int list_length (int /*<<< orphan*/ *) ; 

__attribute__((used)) static List *
gather_restriction_dimension_vectors(HypertableRestrictInfo *hri)
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

	Assert(list_length(dimension_vecs) == hri->num_dimensions);

	return dimension_vecs;
}