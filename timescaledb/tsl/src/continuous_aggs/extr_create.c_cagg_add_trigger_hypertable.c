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
struct TYPE_6__ {int row; int events; int /*<<< orphan*/  args; int /*<<< orphan*/  funcname; int /*<<< orphan*/  relation; int /*<<< orphan*/  trigname; int /*<<< orphan*/  timing; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {int /*<<< orphan*/  objectId; } ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_1__ ObjectAddress ;
typedef  int /*<<< orphan*/  Hypertable ;
typedef  TYPE_2__ CreateTrigStmt ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/  CAGGINVAL_TRIGGER_NAME ; 
 char* CAGG_INVALIDATION_TRIGGER ; 
 int /*<<< orphan*/  ERRCODE_INTERNAL_ERROR ; 
 int /*<<< orphan*/  ERROR ; 
 char* INTERNAL_SCHEMA_NAME ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRIGGER_TYPE_AFTER ; 
 int TRIGGER_TYPE_DELETE ; 
 int TRIGGER_TYPE_INSERT ; 
 int TRIGGER_TYPE_UPDATE ; 
 int /*<<< orphan*/  T_CreateTrigStmt ; 
 scalar_t__ check_trigger_exists_hypertable (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 char* get_namespace_name (int /*<<< orphan*/ ) ; 
 char* get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_namespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_make2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  makeRangeVar (char*,char*,int) ; 
 int /*<<< orphan*/  makeString (char*) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 TYPE_1__ ts_hypertable_create_trigger (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
cagg_add_trigger_hypertable(Oid relid, char *trigarg)
{
	ObjectAddress objaddr;
	char *relname = get_rel_name(relid);
	Oid schemaid = get_rel_namespace(relid);
	char *schema = get_namespace_name(schemaid);
	Cache *hcache;
	Hypertable *ht;

	CreateTrigStmt stmt = {
		.type = T_CreateTrigStmt,
		.row = true,
		.timing = TRIGGER_TYPE_AFTER,
		.trigname = CAGGINVAL_TRIGGER_NAME,
		.relation = makeRangeVar(schema, relname, -1),
		.funcname =
			list_make2(makeString(INTERNAL_SCHEMA_NAME), makeString(CAGG_INVALIDATION_TRIGGER)),
		.args = list_make1(makeString(trigarg)),
		.events = TRIGGER_TYPE_INSERT | TRIGGER_TYPE_UPDATE | TRIGGER_TYPE_DELETE,
	};
	if (check_trigger_exists_hypertable(relid, CAGGINVAL_TRIGGER_NAME))
		return;
	hcache = ts_hypertable_cache_pin();
	ht = ts_hypertable_cache_get_entry(hcache, relid);
	objaddr = ts_hypertable_create_trigger(ht, &stmt, NULL);
	if (!OidIsValid(objaddr.objectId))
		ereport(ERROR,
				(errcode(ERRCODE_INTERNAL_ERROR),
				 errmsg("could not create continuous aggregate trigger")));
	ts_cache_release(hcache);
}