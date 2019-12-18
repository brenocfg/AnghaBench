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
struct TYPE_3__ {int /*<<< orphan*/  missing_ok; int /*<<< orphan*/  dbname; } ;
typedef  scalar_t__ Oid ;
typedef  TYPE_1__ DropdbStmt ;

/* Variables and functions */
 scalar_t__ InvalidOid ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  STOP ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errmsg (char*,scalar_t__) ; 
 scalar_t__ get_database_oid (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_message_send_and_wait (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
stop_workers_on_db_drop(DropdbStmt *drop_db_statement)
{
	/*
	 * Don't check if extension exists here because even though the current
	 * database might not have TimescaleDB installed the database we are
	 * dropping might.
	 */
	Oid dropped_db_oid = get_database_oid(drop_db_statement->dbname, drop_db_statement->missing_ok);

	if (dropped_db_oid != InvalidOid)
	{
		ereport(LOG,
				(errmsg("TimescaleDB background worker scheduler for database %u will be stopped",
						dropped_db_oid)));
		ts_bgw_message_send_and_wait(STOP, dropped_db_oid);
	}
	return;
}