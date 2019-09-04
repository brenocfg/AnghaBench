#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int type; } ;
typedef  int /*<<< orphan*/  EventTriggerDropView ;
typedef  TYPE_1__ EventTriggerDropObject ;

/* Variables and functions */
#define  EVENT_TRIGGER_DROP_INDEX 133 
#define  EVENT_TRIGGER_DROP_SCHEMA 132 
#define  EVENT_TRIGGER_DROP_TABLE 131 
#define  EVENT_TRIGGER_DROP_TABLE_CONSTRAINT 130 
#define  EVENT_TRIGGER_DROP_TRIGGER 129 
#define  EVENT_TRIGGER_DROP_VIEW 128 
 int /*<<< orphan*/  process_drop_index (TYPE_1__*) ; 
 int /*<<< orphan*/  process_drop_schema (TYPE_1__*) ; 
 int /*<<< orphan*/  process_drop_table (TYPE_1__*) ; 
 int /*<<< orphan*/  process_drop_table_constraint (TYPE_1__*) ; 
 int /*<<< orphan*/  process_drop_trigger (TYPE_1__*) ; 
 int /*<<< orphan*/  process_drop_view (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
process_ddl_sql_drop(EventTriggerDropObject *obj)
{
	switch (obj->type)
	{
		case EVENT_TRIGGER_DROP_TABLE_CONSTRAINT:
			process_drop_table_constraint(obj);
			break;
		case EVENT_TRIGGER_DROP_INDEX:
			process_drop_index(obj);
			break;
		case EVENT_TRIGGER_DROP_TABLE:
			process_drop_table(obj);
			break;
		case EVENT_TRIGGER_DROP_SCHEMA:
			process_drop_schema(obj);
			break;
		case EVENT_TRIGGER_DROP_TRIGGER:
			process_drop_trigger(obj);
			break;
		case EVENT_TRIGGER_DROP_VIEW:
			process_drop_view((EventTriggerDropView *) obj);
			break;
	}
}