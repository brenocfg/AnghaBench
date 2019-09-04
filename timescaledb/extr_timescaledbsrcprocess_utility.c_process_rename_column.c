#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  id; } ;
struct TYPE_9__ {int /*<<< orphan*/  space; TYPE_1__ fd; } ;
struct TYPE_8__ {int /*<<< orphan*/  newname; int /*<<< orphan*/  subname; } ;
typedef  TYPE_2__ RenameStmt ;
typedef  int /*<<< orphan*/  ProcessUtilityArgs ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_3__ Hypertable ;
typedef  int /*<<< orphan*/  Dimension ;
typedef  int /*<<< orphan*/  Chunk ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/  DIMENSION_TYPE_ANY ; 
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int HypertableIsMaterialization ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_add_hypertable (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/ * ts_chunk_get_by_relid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int ts_continuous_agg_hypertable_status (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_dimension_set_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hyperspace_get_dimension_by_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
process_rename_column(ProcessUtilityArgs *args, Cache *hcache, Oid relid, RenameStmt *stmt)
{
	Hypertable *ht = ts_hypertable_cache_get_entry(hcache, relid);
	Dimension *dim;

	if (NULL == ht)
	{
		Chunk *chunk = ts_chunk_get_by_relid(relid, 0, false);

		if (NULL != chunk)
			ereport(ERROR,
					(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
					 errmsg("cannot rename column \"%s\" of hypertable chunk \"%s\"",
							stmt->subname,
							get_rel_name(relid)),
					 errhint("Rename the hypertable column instead.")));
		return;
	}

	/* block renaming columns on the materialization table of a continuous agg*/
	if ((ts_continuous_agg_hypertable_status(ht->fd.id) & HypertableIsMaterialization) != 0)
		ereport(ERROR,
				(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
				 errmsg("cannot rename column \"%s\" of materialization table \"%s\"",
						stmt->subname,
						get_rel_name(relid))));

	process_add_hypertable(args, ht);

	dim = ts_hyperspace_get_dimension_by_name(ht->space, DIMENSION_TYPE_ANY, stmt->subname);

	if (NULL == dim)
		return;

	ts_dimension_set_name(dim, stmt->newname);
}