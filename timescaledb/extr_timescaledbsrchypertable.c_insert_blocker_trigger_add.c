#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int row; int /*<<< orphan*/  events; int /*<<< orphan*/  args; int /*<<< orphan*/  funcname; int /*<<< orphan*/  relation; int /*<<< orphan*/  trigname; int /*<<< orphan*/  timing; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  objectId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  TYPE_2__ CreateTrigStmt ;

/* Variables and functions */
 TYPE_1__ CreateTriggerCompat (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  INSERT_BLOCKER_NAME ; 
 int /*<<< orphan*/  INTERNAL_SCHEMA_NAME ; 
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NIL ; 
 int /*<<< orphan*/  OLD_INSERT_BLOCKER_NAME ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_TYPE_BEFORE ; 
 int /*<<< orphan*/  TRIGGER_TYPE_INSERT ; 
 int /*<<< orphan*/  T_CreateTrigStmt ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeRangeVar (char*,char*,int) ; 
 int /*<<< orphan*/  makeString (int /*<<< orphan*/ ) ; 

__attribute__((used)) static Oid
insert_blocker_trigger_add(Oid relid)
{
	ObjectAddress objaddr;
	char *relname = get_rel_name(relid);
	Oid schemaid = get_rel_namespace(relid);
	char *schema = get_namespace_name(schemaid);
	CreateTrigStmt stmt = {
		.type = T_CreateTrigStmt,
		.row = true,
		.timing = TRIGGER_TYPE_BEFORE,
		.trigname = INSERT_BLOCKER_NAME,
		.relation = makeRangeVar(schema, relname, -1),
		.funcname =
			list_make2(makeString(INTERNAL_SCHEMA_NAME), makeString(OLD_INSERT_BLOCKER_NAME)),
		.args = NIL,
		.events = TRIGGER_TYPE_INSERT,
	};

	/*
	 * We create a user-visible trigger, so that it will get pg_dump'd with
	 * the hypertable. This call will error out if a trigger with the same
	 * name already exists. (This is the desired behavior.)
	 */
	objaddr = CreateTriggerCompat(&stmt, NULL, relid, InvalidOid, InvalidOid, InvalidOid, false);

	if (!OidIsValid(objaddr.objectId))
		elog(ERROR, "could not create insert blocker trigger");

	return objaddr.objectId;
}