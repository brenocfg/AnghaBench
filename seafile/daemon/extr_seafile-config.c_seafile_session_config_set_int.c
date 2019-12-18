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
typedef  int /*<<< orphan*/  sql ;
struct TYPE_3__ {int http_proxy_port; int /*<<< orphan*/  config_db; } ;
typedef  TYPE_1__ SeafileSession ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_PROXY_PORT ; 
 scalar_t__ g_strcmp0 (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_snprintf (int,char*,char*,char const*,int) ; 
 scalar_t__ sqlite_query_exec (int /*<<< orphan*/ ,char*) ; 

int
seafile_session_config_set_int (SeafileSession *session,
                                const char *key,
                                int value)
{
    char sql[256];

    sqlite3_snprintf (sizeof(sql), sql,
                      "REPLACE INTO Config VALUES ('%q', %d);",
                      key, value);
    if (sqlite_query_exec (session->config_db, sql) < 0)
        return -1;

    if (g_strcmp0(key, KEY_PROXY_PORT) == 0) {
        session->http_proxy_port = value;
    }

    return 0;
}