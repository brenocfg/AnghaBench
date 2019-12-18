#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ datistemplate; int /*<<< orphan*/  datallowconn; } ;
typedef  int /*<<< orphan*/  Relation ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  int /*<<< orphan*/  HeapScanDesc ;
typedef  int /*<<< orphan*/  HTAB ;
typedef  TYPE_1__* Form_pg_database ;

/* Variables and functions */
 int /*<<< orphan*/  AccessShareLock ; 
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  DatabaseRelationId ; 
 int /*<<< orphan*/  ForwardScanDirection ; 
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetTransactionSnapshot () ; 
 int /*<<< orphan*/  HeapTupleGetOid (int /*<<< orphan*/ ) ; 
 scalar_t__ HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  db_hash_entry_create_if_not_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_beginscan_catalog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_close (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_endscan (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_getnext (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_open (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
populate_database_htab(HTAB *db_htab)
{
	Relation rel;
	HeapScanDesc scan;
	HeapTuple tup;

	/*
	 * by this time we should already be connected to the db, and only have
	 * access to shared catalogs
	 */
	StartTransactionCommand();
	(void) GetTransactionSnapshot();

	rel = heap_open(DatabaseRelationId, AccessShareLock);
	scan = heap_beginscan_catalog(rel, 0, NULL);

	while (HeapTupleIsValid(tup = heap_getnext(scan, ForwardScanDirection)))
	{
		Form_pg_database pgdb = (Form_pg_database) GETSTRUCT(tup);

		if (!pgdb->datallowconn || pgdb->datistemplate)
			continue; /* don't bother with dbs that don't allow
					   * connections or are templates */

		db_hash_entry_create_if_not_exists(db_htab, HeapTupleGetOid(tup));
	}
	heap_endscan(scan);
	heap_close(rel, AccessShareLock);

	CommitTransactionCommand();
}