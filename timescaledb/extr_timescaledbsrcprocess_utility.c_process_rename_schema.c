#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  newname; int /*<<< orphan*/  subname; } ;
typedef  TYPE_1__ RenameStmt ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_TS_OPERATION_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  NAMEDATALEN ; 
 int NUM_TIMESCALEDB_SCHEMAS ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * timescaledb_schema_names ; 
 int /*<<< orphan*/  ts_chunks_rename_schema_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_continuous_agg_rename_schema_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_dimensions_rename_schema_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_hypertables_rename_schema_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_rename_schema(RenameStmt *stmt)
{
	int i = 0;

	/* Block any renames of our internal schemas */
	for (i = 0; i < NUM_TIMESCALEDB_SCHEMAS; i++)
	{
		if (strncmp(stmt->subname, timescaledb_schema_names[i], NAMEDATALEN) == 0)
		{
			ereport(ERROR,
					(errcode(ERRCODE_TS_OPERATION_NOT_SUPPORTED),
					 errmsg("cannot rename schemas used by the TimescaleDB extension")));
			return;
		}
	}

	ts_chunks_rename_schema_name(stmt->subname, stmt->newname);
	ts_dimensions_rename_schema_name(stmt->subname, stmt->newname);
	ts_hypertables_rename_schema_name(stmt->subname, stmt->newname);
	ts_continuous_agg_rename_schema_name(stmt->subname, stmt->newname);
}