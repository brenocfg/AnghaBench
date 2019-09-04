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
struct TYPE_4__ {int /*<<< orphan*/  schema; } ;
typedef  TYPE_1__ EventTriggerDropSchema ;
typedef  TYPE_2__ EventTriggerDropObject ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ EVENT_TRIGGER_DROP_SCHEMA ; 
 int /*<<< orphan*/  EXTENSION_NAME ; 
 int /*<<< orphan*/  INTERNAL_SCHEMA_NAME ; 
 int /*<<< orphan*/  NOTICE ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ts_hypertable_reset_associated_schema_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_drop_schema(EventTriggerDropObject *obj)
{
	EventTriggerDropSchema *schema;
	int count;

	Assert(obj->type == EVENT_TRIGGER_DROP_SCHEMA);
	schema = (EventTriggerDropSchema *) obj;

	if (strcmp(schema->schema, INTERNAL_SCHEMA_NAME) == 0)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot drop the internal schema for extension \"%s\"", EXTENSION_NAME),
				 errhint("Use DROP EXTENSION to remove the extension and the schema.")));

	/*
	 * Check for any remaining hypertables that use the schema as its
	 * associated schema. For matches, we reset their associated schema to the
	 * INTERNAL schema
	 */
	count = ts_hypertable_reset_associated_schema_name(schema->schema);

	if (count > 0)
		ereport(NOTICE,
				(errmsg("the chunk storage schema changed to \"%s\" for %d hypertable%c",
						INTERNAL_SCHEMA_NAME,
						count,
						(count > 1) ? 's' : '\0')));
}