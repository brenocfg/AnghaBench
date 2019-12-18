#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ type; } ;
struct TYPE_4__ {int /*<<< orphan*/  table_name; int /*<<< orphan*/  schema; } ;
typedef  TYPE_1__ EventTriggerDropTable ;
typedef  TYPE_2__ EventTriggerDropObject ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  DROP_RESTRICT ; 
 scalar_t__ EVENT_TRIGGER_DROP_TABLE ; 
 int /*<<< orphan*/  ts_chunk_delete_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_hypertable_delete_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_drop_table(EventTriggerDropObject *obj)
{
	EventTriggerDropTable *table;

	Assert(obj->type == EVENT_TRIGGER_DROP_TABLE);
	table = (EventTriggerDropTable *) obj;

	ts_hypertable_delete_by_name(table->schema, table->table_name);
	ts_chunk_delete_by_name(table->schema, table->table_name, DROP_RESTRICT);
}