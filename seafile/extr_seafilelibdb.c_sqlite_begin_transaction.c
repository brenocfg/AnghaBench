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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int sqlite_query_exec (int /*<<< orphan*/ *,char*) ; 

int
sqlite_begin_transaction (sqlite3 *db)
{
    char *sql = "BEGIN TRANSACTION;";
    return sqlite_query_exec (db, sql);
}