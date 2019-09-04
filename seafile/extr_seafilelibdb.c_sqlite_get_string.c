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
 char* g_strdup (char const*) ; 
 int /*<<< orphan*/  g_warning (char*,int,char const*) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite_query_prepare (int /*<<< orphan*/ *,char const*) ; 

char *sqlite_get_string (sqlite3 *db, const char *sql)
{
    const char *res = NULL;
    int result;
    sqlite3_stmt *stmt;
    char *ret;

    if ( !(stmt = sqlite_query_prepare(db, sql)) )
        return NULL;

    result = sqlite3_step (stmt);
    if (result == SQLITE_ROW) {
        res = (const char *)sqlite3_column_text (stmt, 0);
        ret = g_strdup(res);
        sqlite3_finalize (stmt);
        return ret;
    }

    if (result == SQLITE_ERROR) {
        const gchar *str = sqlite3_errmsg (db);
        g_warning ("Couldn't execute query, error: %d->'%s'\n",
                   result, str ? str : "no error given");
        sqlite3_finalize (stmt);
        return NULL;
    }

    sqlite3_finalize(stmt);
    return NULL;
}