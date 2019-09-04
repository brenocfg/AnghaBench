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
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  char gchar ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  g_warning (char*,int,char const*) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite_query_prepare (int /*<<< orphan*/ *,char const*) ; 

int sqlite_get_int (sqlite3 *db, const char *sql)
{
    int ret = -1;
    int result;
    sqlite3_stmt *stmt;

    if ( !(stmt = sqlite_query_prepare(db, sql)) )
        return 0;

    result = sqlite3_step (stmt);
    if (result == SQLITE_ROW) {
        ret = sqlite3_column_int (stmt, 0);
        sqlite3_finalize (stmt);
        return ret;
    }

    if (result == SQLITE_ERROR) {
        const gchar *str = sqlite3_errmsg (db);
        g_warning ("Couldn't execute query, error: %d->'%s'\n",
                   result, str ? str : "no error given");
        sqlite3_finalize (stmt);
        return -1;
    }

    sqlite3_finalize(stmt);
    return ret;
}