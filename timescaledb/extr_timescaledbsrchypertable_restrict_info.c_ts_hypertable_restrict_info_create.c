#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_1__* space; } ;
struct TYPE_8__ {int num_dimensions; int /*<<< orphan*/ ** dimension_restriction; } ;
struct TYPE_7__ {int num_dimensions; int /*<<< orphan*/ * dimensions; } ;
typedef  int /*<<< orphan*/  RelOptInfo ;
typedef  TYPE_2__ HypertableRestrictInfo ;
typedef  TYPE_3__ Hypertable ;
typedef  int /*<<< orphan*/  DimensionRestrictInfo ;

/* Variables and functions */
 int /*<<< orphan*/ * dimension_restrict_info_create (int /*<<< orphan*/ *) ; 
 TYPE_2__* palloc0 (int) ; 

HypertableRestrictInfo *
ts_hypertable_restrict_info_create(RelOptInfo *rel, Hypertable *ht)
{
	int num_dimensions = ht->space->num_dimensions;
	HypertableRestrictInfo *res =
		palloc0(sizeof(HypertableRestrictInfo) + sizeof(DimensionRestrictInfo *) * num_dimensions);
	int i;

	res->num_dimensions = num_dimensions;

	for (i = 0; i < num_dimensions; i++)
	{
		DimensionRestrictInfo *dri = dimension_restrict_info_create(&ht->space->dimensions[i]);

		res->dimension_restriction[i] = dri;
	}

	return res;
}