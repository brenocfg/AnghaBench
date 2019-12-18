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
typedef  int /*<<< orphan*/  sql ;

/* Variables and functions */
 int /*<<< orphan*/  get_value ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ sqlite_foreach_selected_row (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char**) ; 

__attribute__((used)) static char *
config_get_string (sqlite3 *config_db, const char *key)
{
    char sql[256];
    char *value = NULL;

    snprintf (sql, sizeof(sql),
              "SELECT value FROM Config WHERE key='%s';",
              key);
    if (sqlite_foreach_selected_row (config_db, sql,
                                     get_value, &value) < 0)
        return NULL;

    return value;
}