#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  column_name; } ;
struct TYPE_7__ {TYPE_1__ fd; } ;
struct TYPE_6__ {int num_dimensions; TYPE_3__* dimensions; } ;
typedef  int /*<<< orphan*/  List ;
typedef  TYPE_2__ Hyperspace ;
typedef  TYPE_3__ Dimension ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_TS_BAD_HYPERTABLE_INDEX_DEFINITION ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_has_attribute (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
ts_indexing_verify_columns(Hyperspace *hs, List *indexelems)
{
	int i;

	for (i = 0; i < hs->num_dimensions; i++)
	{
		Dimension *dim = &hs->dimensions[i];

		if (!index_has_attribute(indexelems, NameStr(dim->fd.column_name)))
			ereport(ERROR,
					(errcode(ERRCODE_TS_BAD_HYPERTABLE_INDEX_DEFINITION),
					 errmsg("cannot create a unique index without the column \"%s\" (used in "
							"partitioning)",
							NameStr(dim->fd.column_name))));
	}
}