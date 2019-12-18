#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  clone_mgr; } ;
struct TYPE_10__ {int /*<<< orphan*/  worktree; int /*<<< orphan*/  repo_name; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  error; int /*<<< orphan*/  state; } ;
struct TYPE_9__ {TYPE_2__* data; struct TYPE_9__* next; } ;
typedef  int /*<<< orphan*/  SeafileCloneTask ;
typedef  TYPE_1__ GList ;
typedef  int /*<<< orphan*/  GError ;
typedef  TYPE_2__ CloneTask ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_TYPE_CLONE_TASK ; 
 int /*<<< orphan*/  clone_task_state_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_list_free (TYPE_1__*) ; 
 TYPE_1__* g_list_prepend (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_object_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* seaf ; 
 TYPE_1__* seaf_clone_manager_get_tasks (int /*<<< orphan*/ ) ; 

GList *
seafile_get_clone_tasks (GError **error)
{
    GList *tasks, *ptr;
    GList *ret = NULL;
    CloneTask *task;
    SeafileCloneTask *t;

    tasks = seaf_clone_manager_get_tasks (seaf->clone_mgr);
    for (ptr = tasks; ptr != NULL; ptr = ptr->next) {
        task = ptr->data;
        t = g_object_new (SEAFILE_TYPE_CLONE_TASK,
                          "state", clone_task_state_to_str(task->state),
                          "error", task->error,
                          "repo_id", task->repo_id,
                          "repo_name", task->repo_name,
                          "worktree", task->worktree,
                          NULL);
        ret = g_list_prepend (ret, t);
    }

    g_list_free (tasks);
    return ret;
}