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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_3__ {int /*<<< orphan*/  config_db; } ;
typedef  TYPE_1__ SeafileSession ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 int /*<<< orphan*/  sqlite_check_for_existence (int /*<<< orphan*/ ,char*) ; 

gboolean
seafile_session_config_exists (SeafileSession *session, const char *key)
{
    char sql[256];

    snprintf (sql, sizeof(sql),
              "SELECT 1 FROM Config WHERE key = '%s'",
              key);
    return sqlite_check_for_existence (session->config_db, sql);
}