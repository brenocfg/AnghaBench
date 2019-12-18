#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  column_name; } ;
struct TYPE_12__ {TYPE_2__ fd; } ;
struct TYPE_11__ {TYPE_1__* space; } ;
struct TYPE_9__ {int num_dimensions; TYPE_4__* dimensions; } ;
typedef  TYPE_3__ Hypertable ;
typedef  TYPE_4__ Dimension ;
typedef  TYPE_5__ AlterTableCmd ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_TS_OPERATION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ IS_OPEN_DIMENSION (TYPE_4__*) ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int /*<<< orphan*/  NameStr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_altertable_drop_not_null(Hypertable *ht, AlterTableCmd *cmd)
{
	int i;

	for (i = 0; i < ht->space->num_dimensions; i++)
	{
		Dimension *dim = &ht->space->dimensions[i];

		if (IS_OPEN_DIMENSION(dim) &&
			strncmp(NameStr(dim->fd.column_name), cmd->name, NAMEDATALEN) == 0)
			ereport(ERROR,
					(errcode(ERRCODE_TS_OPERATION_NOT_SUPPORTED),
					 errmsg("cannot drop not-null constraint from a time-partitioned column")));
	}
}