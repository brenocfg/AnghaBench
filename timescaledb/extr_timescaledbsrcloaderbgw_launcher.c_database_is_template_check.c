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
struct TYPE_2__ {scalar_t__ datistemplate; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_database ;

/* Variables and functions */
 int /*<<< orphan*/  DATABASEOID ; 
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ GETSTRUCT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HeapTupleIsValid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MyDatabaseId ; 
 int /*<<< orphan*/  ObjectIdGetDatum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ReleaseSysCache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SearchSysCache1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*) ; 

__attribute__((used)) static void
database_is_template_check(void)
{
	Form_pg_database pgdb;
	HeapTuple tuple;

	tuple = SearchSysCache1(DATABASEOID, ObjectIdGetDatum(MyDatabaseId));
	if (!HeapTupleIsValid(tuple))
		ereport(ERROR,
				(errmsg("TimescaleDB background worker failed to find entry for database in "
						"syscache")));

	pgdb = (Form_pg_database) GETSTRUCT(tuple);
	if (pgdb->datistemplate)
		ereport(ERROR,
				(errmsg("TimescaleDB background worker connected to template database, exiting")));

	ReleaseSysCache(tuple);
}