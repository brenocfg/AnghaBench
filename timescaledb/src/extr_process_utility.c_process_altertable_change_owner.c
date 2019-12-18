#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  newowner; } ;
struct TYPE_11__ {int /*<<< orphan*/  compressed_hypertable_id; } ;
struct TYPE_12__ {int /*<<< orphan*/  main_table_relid; TYPE_1__ fd; } ;
typedef  TYPE_2__ Hypertable ;
typedef  TYPE_3__ AlterTableCmd ;

/* Variables and functions */
 int /*<<< orphan*/  AlterTableInternal (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IsA (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RoleSpec ; 
 scalar_t__ TS_HYPERTABLE_HAS_COMPRESSION (TYPE_2__*) ; 
 int /*<<< orphan*/  foreach_chunk (TYPE_2__*,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  list_make1 (TYPE_3__*) ; 
 int /*<<< orphan*/  process_altertable_change_owner_chunk ; 
 TYPE_2__* ts_hypertable_get_by_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_altertable_change_owner(Hypertable *ht, AlterTableCmd *cmd)
{
	Assert(IsA(cmd->newowner, RoleSpec));

	foreach_chunk(ht, process_altertable_change_owner_chunk, cmd);

	if (TS_HYPERTABLE_HAS_COMPRESSION(ht))
	{
		Hypertable *compressed_hypertable =
			ts_hypertable_get_by_id(ht->fd.compressed_hypertable_id);
		AlterTableInternal(compressed_hypertable->main_table_relid, list_make1(cmd), false);
		process_altertable_change_owner(compressed_hypertable, cmd);
	}
}