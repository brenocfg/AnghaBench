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
 scalar_t__ sqlite_open_db (char const*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sqlite_query_exec (int /*<<< orphan*/ *,char*) ; 

sqlite3 *
seafile_session_config_open_db (const char *db_path)
{
    sqlite3 *db;

    if (sqlite_open_db (db_path, &db) < 0)
        return NULL;

    /*
     * Values are stored in text. You should convert it
     * back to integer if needed when you read it from
     * db.
     */
    char *sql = "CREATE TABLE IF NOT EXISTS Config ("
        "key TEXT PRIMARY KEY, "
        "value TEXT);";
    sqlite_query_exec (db, sql);

    return db;
}