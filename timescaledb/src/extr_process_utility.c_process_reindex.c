#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  id; } ;
struct TYPE_14__ {TYPE_1__ fd; } ;
struct TYPE_13__ {scalar_t__ parsetree; } ;
struct TYPE_12__ {int kind; int /*<<< orphan*/ * relation; } ;
typedef  TYPE_2__ ReindexStmt ;
typedef  TYPE_3__ ProcessUtilityArgs ;
typedef  int /*<<< orphan*/  Oid ;
typedef  TYPE_4__ Hypertable ;
typedef  int /*<<< orphan*/  Cache ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_FEATURE_NOT_SUPPORTED ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IndexGetRelation (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  NoLock ; 
 int /*<<< orphan*/  OidIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PreventCommandDuringRecovery (char*) ; 
#define  REINDEX_OBJECT_INDEX 129 
#define  REINDEX_OBJECT_TABLE 128 
 int /*<<< orphan*/  RangeVarGetRelid (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*) ; 
 int /*<<< orphan*/  foreach_chunk (TYPE_4__*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  process_add_hypertable (TYPE_3__*,TYPE_4__*) ; 
 int /*<<< orphan*/  reindex_chunk ; 
 int /*<<< orphan*/  ts_cache_release (int /*<<< orphan*/ *) ; 
 TYPE_4__* ts_hypertable_cache_get_entry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ts_hypertable_cache_pin () ; 
 int /*<<< orphan*/  ts_hypertable_permissions_check_by_id (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
process_reindex(ProcessUtilityArgs *args)
{
	ReindexStmt *stmt = (ReindexStmt *) args->parsetree;
	Oid relid;
	Cache *hcache;
	Hypertable *ht;
	bool ret = false;

	if (NULL == stmt->relation)
		/* Not a case we are interested in */
		return false;

	relid = RangeVarGetRelid(stmt->relation, NoLock, true);

	if (!OidIsValid(relid))
		return false;

	hcache = ts_hypertable_cache_pin();

	switch (stmt->kind)
	{
		case REINDEX_OBJECT_TABLE:
			ht = ts_hypertable_cache_get_entry(hcache, relid);

			if (NULL != ht)
			{
				PreventCommandDuringRecovery("REINDEX");
				ts_hypertable_permissions_check_by_id(ht->fd.id);

				if (foreach_chunk(ht, reindex_chunk, stmt) >= 0)
					ret = true;

				process_add_hypertable(args, ht);
			}
			break;
		case REINDEX_OBJECT_INDEX:
			ht = ts_hypertable_cache_get_entry(hcache, IndexGetRelation(relid, true));

			if (NULL != ht)
			{
				process_add_hypertable(args, ht);
				ts_hypertable_permissions_check_by_id(ht->fd.id);

				/*
				 * Recursing to chunks is currently not supported. Need to
				 * look up all chunk indexes that corresponds to the
				 * hypertable's index.
				 */
				ereport(ERROR,
						(errcode(ERRCODE_FEATURE_NOT_SUPPORTED),
						 errmsg("reindexing of a specific index on a hypertable is unsupported"),
						 errhint(
							 "As a workaround, it is possible to run REINDEX TABLE to reindex all "
							 "indexes on a hypertable, including all indexes on chunks.")));
			}
			break;
		default:
			break;
	}

	ts_cache_release(hcache);

	return ret;
}