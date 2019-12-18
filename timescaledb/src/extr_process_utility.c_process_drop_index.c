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
struct TYPE_5__ {int /*<<< orphan*/  index_name; int /*<<< orphan*/  schema; } ;
struct TYPE_4__ {scalar_t__ type; } ;
typedef  TYPE_1__ EventTriggerDropObject ;
typedef  TYPE_2__ EventTriggerDropIndex ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ EVENT_TRIGGER_DROP_INDEX ; 
 int /*<<< orphan*/  ts_chunk_index_delete_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
process_drop_index(EventTriggerDropObject *obj)
{
	EventTriggerDropIndex *index;

	Assert(obj->type == EVENT_TRIGGER_DROP_INDEX);
	index = (EventTriggerDropIndex *) obj;

	ts_chunk_index_delete_by_name(index->schema, index->index_name, true);
}