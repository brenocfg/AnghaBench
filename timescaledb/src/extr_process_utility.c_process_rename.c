#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ parsetree; } ;
struct TYPE_14__ {int renameType; int /*<<< orphan*/ * relation; } ;
typedef  TYPE_1__ RenameStmt ;
typedef  TYPE_2__ ProcessUtilityArgs ;
typedef  int /*<<< orphan*/  Oid ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/  InvalidOid ; 
 int /*<<< orphan*/  NoLock ; 
#define  OBJECT_COLUMN 133 
#define  OBJECT_INDEX 132 
#define  OBJECT_SCHEMA 131 
#define  OBJECT_TABCONSTRAINT 130 
#define  OBJECT_TABLE 129 
#define  OBJECT_VIEW 128 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  process_rename_column (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  process_rename_constraint (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  process_rename_index (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  process_rename_schema (TYPE_1__*) ; 
 int /*<<< orphan*/  process_rename_table (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  process_rename_view (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 

__attribute__((used)) static void
process_rename(ProcessUtilityArgs *args)
{
	RenameStmt *stmt = (RenameStmt *) args->parsetree;
	Oid relid = InvalidOid;
	Cache *hcache;

	/* Only get the relid if it exists for this stmt */
	if (NULL != stmt->relation)
	{
		relid = RangeVarGetRelid(stmt->relation, NoLock, true);
		if (!OidIsValid(relid))
			return;
	}
	else
	{
		/*
		 * stmt->relation never be NULL unless we are renaming a schema
		 */
		if (stmt->renameType != OBJECT_SCHEMA)
			return;
	}

	hcache = ts_hypertable_cache_pin();

	switch (stmt->renameType)
	{
		case OBJECT_TABLE:
			process_rename_table(args, hcache, relid, stmt);
			break;
		case OBJECT_COLUMN:
			process_rename_column(args, hcache, relid, stmt);
			break;
		case OBJECT_INDEX:
			process_rename_index(args, hcache, relid, stmt);
			break;
		case OBJECT_TABCONSTRAINT:
			process_rename_constraint(args, hcache, relid, stmt);
			break;
		case OBJECT_VIEW:
			process_rename_view(relid, stmt);
			break;
		case OBJECT_SCHEMA:
			process_rename_schema(stmt);
			break;
		default:
			break;
	}

	ts_cache_release(hcache);
}