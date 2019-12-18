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
struct TYPE_3__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ SeafCloneManager ;

/* Variables and functions */
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*) ; 
 scalar_t__ sqlite_query_exec (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
remove_task_from_db (SeafCloneManager *mgr, const char *repo_id)
{
    char sql[256];

    snprintf (sql, sizeof(sql), 
              "DELETE FROM CloneTasks WHERE repo_id='%s'",
              repo_id);
    if (sqlite_query_exec (mgr->db, sql) < 0)
        return -1;

    snprintf (sql, sizeof(sql), 
              "DELETE FROM CloneEncInfo WHERE repo_id='%s'",
              repo_id);
    if (sqlite_query_exec (mgr->db, sql) < 0)
        return -1;

    snprintf (sql, sizeof(sql), 
              "DELETE FROM CloneVersionInfo WHERE repo_id='%s'",
              repo_id);
    if (sqlite_query_exec (mgr->db, sql) < 0)
        return -1;

    snprintf (sql, sizeof(sql), 
              "DELETE FROM CloneTasksMoreInfo WHERE repo_id='%s'",
              repo_id);
    if (sqlite_query_exec (mgr->db, sql) < 0)
        return -1;

    return 0;
}