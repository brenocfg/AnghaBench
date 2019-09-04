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
 int SQLITE_OK ; 
 int /*<<< orphan*/  g_warning (char*,int,char const*,char const*) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ *) ; 

sqlite3_stmt *
sqlite_query_prepare (sqlite3 *db, const char *sql)
{
    sqlite3_stmt *stmt;
    int result;

    result = sqlite3_prepare_v2 (db, sql, -1, &stmt, NULL);

    if (result != SQLITE_OK) {
        const gchar *str = sqlite3_errmsg (db);

        g_warning ("Couldn't prepare query, error:%d->'%s'\n\t%s\n", 
                   result, str ? str : "no error given", sql);

        return NULL;
    }

    return stmt;
}