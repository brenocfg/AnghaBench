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
typedef  int /*<<< orphan*/  gboolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SQLITE_ERROR ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_warning (char*,int,char const*) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite_query_prepare (int /*<<< orphan*/ *,char const*) ; 

gboolean
sqlite_check_for_existence (sqlite3 *db, const char *sql)
{
    sqlite3_stmt *stmt;
    int result;

    stmt = sqlite_query_prepare (db, sql);
    if (!stmt)
        return FALSE;

    result = sqlite3_step (stmt);
    if (result == SQLITE_ERROR) {
        const gchar *str = sqlite3_errmsg (db);

        g_warning ("Couldn't execute query, error: %d->'%s'\n", 
                   result, str ? str : "no error given");
        sqlite3_finalize (stmt);
        return FALSE;
    }
    sqlite3_finalize (stmt);

    if (result == SQLITE_ROW)
        return TRUE;
    return FALSE;
}