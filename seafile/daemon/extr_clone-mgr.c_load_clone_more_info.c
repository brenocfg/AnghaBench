#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sql ;
struct TYPE_6__ {char* repo_id; TYPE_1__* manager; } ;
struct TYPE_5__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ CloneTask ;

/* Variables and functions */
 int /*<<< orphan*/  load_more_info_cb ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 
 int /*<<< orphan*/  sqlite_foreach_selected_row (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void
load_clone_more_info (CloneTask *task)
{
    char sql[256];

    snprintf (sql, sizeof(sql),
              "SELECT more_info FROM CloneTasksMoreInfo WHERE repo_id='%s'",
              task->repo_id);

    sqlite_foreach_selected_row (task->manager->db, sql,
                                 load_more_info_cb, task);
}