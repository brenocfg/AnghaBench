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
struct TYPE_4__ {int /*<<< orphan*/  trigger_name; int /*<<< orphan*/  table; int /*<<< orphan*/  schema; } ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  TYPE_1__ EventTriggerDropTrigger ;
typedef  TYPE_2__ EventTriggerDropObject ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ EVENT_TRIGGER_DROP_TRIGGER ; 
 int /*<<< orphan*/  ts_hypertable_drop_trigger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_get_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_drop_trigger(EventTriggerDropObject *obj)
{
	EventTriggerDropTrigger *trigger_event;
	Hypertable *ht;

	Assert(obj->type == EVENT_TRIGGER_DROP_TRIGGER);
	trigger_event = (EventTriggerDropTrigger *) obj;

	/* do not use relids because underlying table could be gone */
	ht = ts_hypertable_get_by_name(trigger_event->schema, trigger_event->table);

	if (ht != NULL)
	{
		/* Recurse to each chunk and drop the corresponding trigger */
		ts_hypertable_drop_trigger(ht, trigger_event->trigger_name);
	}
}