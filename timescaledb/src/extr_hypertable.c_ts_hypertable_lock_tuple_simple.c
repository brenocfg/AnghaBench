#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Oid ;
typedef  int HTSU_Result ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_LOCK_NOT_AVAILABLE ; 
 int /*<<< orphan*/  ERROR ; 
#define  HeapTupleBeingUpdated 133 
#define  HeapTupleInvisible 132 
#define  HeapTupleMayBeUpdated 131 
#define  HeapTupleSelfUpdated 130 
#define  HeapTupleUpdated 129 
#define  HeapTupleWouldBlock 128 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_rel_name (int /*<<< orphan*/ ) ; 
 int ts_hypertable_lock_tuple (int /*<<< orphan*/ ) ; 

bool
ts_hypertable_lock_tuple_simple(Oid table_relid)
{
	HTSU_Result result = ts_hypertable_lock_tuple(table_relid);

	switch (result)
	{
		case HeapTupleSelfUpdated:

			/*
			 * Updated by the current transaction already. We equate this with
			 * a successful lock since the tuple should be locked if updated
			 * by us.
			 */
			return true;
		case HeapTupleMayBeUpdated:
			/* successfully locked */
			return true;
		case HeapTupleUpdated:
			ereport(ERROR,
					(errcode(ERRCODE_LOCK_NOT_AVAILABLE),
					 errmsg("hypertable \"%s\" has already been updated by another transaction",
							get_rel_name(table_relid)),
					 errhint("Retry the operation again")));
		case HeapTupleBeingUpdated:
			ereport(ERROR,
					(errcode(ERRCODE_LOCK_NOT_AVAILABLE),
					 errmsg("hypertable \"%s\" is being updated by another transaction",
							get_rel_name(table_relid)),
					 errhint("Retry the operation again")));
		case HeapTupleWouldBlock:
			/* Locking would block. Let caller decide what to do */
			return false;
		case HeapTupleInvisible:
			elog(ERROR, "attempted to lock invisible tuple");
			return false;
		default:
			elog(ERROR, "unexpected tuple lock status");
			return false;
	}
}