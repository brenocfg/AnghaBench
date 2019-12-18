#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_10__ {TYPE_1__ fd; } ;
struct TYPE_9__ {scalar_t__ type; } ;
struct TYPE_8__ {int /*<<< orphan*/  constraint_name; int /*<<< orphan*/  table; int /*<<< orphan*/  schema; } ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  TYPE_2__ EventTriggerDropTableConstraint ;
typedef  TYPE_3__ EventTriggerDropObject ;
typedef  TYPE_4__ Chunk ;
typedef  int /*<<< orphan*/  CatalogSecurityContext ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ EVENT_TRIGGER_DROP_TABLE_CONSTRAINT ; 
 TYPE_4__* chunk_get_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  foreach_chunk (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_drop_constraint_on_chunk ; 
 int /*<<< orphan*/  ts_catalog_database_info_become_owner (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_catalog_database_info_get () ; 
 int /*<<< orphan*/  ts_catalog_restore_user (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ts_chunk_constraint_delete_by_constraint_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/ * ts_hypertable_get_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_drop_table_constraint(EventTriggerDropObject *obj)
{
	EventTriggerDropTableConstraint *constraint;
	Hypertable *ht;

	Assert(obj->type == EVENT_TRIGGER_DROP_TABLE_CONSTRAINT);
	constraint = (EventTriggerDropTableConstraint *) obj;

	/* do not use relids because underlying table could be gone */
	ht = ts_hypertable_get_by_name(constraint->schema, constraint->table);

	if (ht != NULL)
	{
		CatalogSecurityContext sec_ctx;

		ts_catalog_database_info_become_owner(ts_catalog_database_info_get(), &sec_ctx);

		/* Recurse to each chunk and drop the corresponding constraint */
		foreach_chunk(ht, process_drop_constraint_on_chunk, constraint->constraint_name);

		ts_catalog_restore_user(&sec_ctx);
	}
	else
	{
		Chunk *chunk = chunk_get_by_name(constraint->schema, constraint->table, 0, false);

		if (NULL != chunk)
		{
			ts_chunk_constraint_delete_by_constraint_name(chunk->fd.id,
														  constraint->constraint_name,
														  true,
														  false);
		}
	}
}