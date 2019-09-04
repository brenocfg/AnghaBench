#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gpointer ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_16__ {int /*<<< orphan*/  repo_mgr; int /*<<< orphan*/ * ccnet_dir; int /*<<< orphan*/ * worktree_dir; int /*<<< orphan*/ * seaf_dir; } ;
struct TYPE_15__ {TYPE_2__* data; struct TYPE_15__* next; } ;
struct TYPE_14__ {int /*<<< orphan*/  tasks; } ;
struct TYPE_13__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * worktree; } ;
struct TYPE_12__ {scalar_t__ state; int /*<<< orphan*/  repo_id; int /*<<< orphan*/ * worktree; } ;
typedef  TYPE_2__ SeafRepo ;
typedef  TYPE_3__ SeafCloneManager ;
typedef  TYPE_4__ GList ;
typedef  int /*<<< orphan*/  GHashTableIter ;
typedef  int /*<<< orphan*/  GError ;
typedef  TYPE_1__ CloneTask ;

/* Variables and functions */
 scalar_t__ CLONE_STATE_CANCELED ; 
 scalar_t__ CLONE_STATE_DONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEAFILE_DOMAIN ; 
 int /*<<< orphan*/  SEAF_ERR_GENERAL ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ check_dir_inclusiveness (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,TYPE_1__**,TYPE_1__**) ; 
 int /*<<< orphan*/  g_list_free (TYPE_4__*) ; 
 int /*<<< orphan*/  g_set_error (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_8__* seaf ; 
 TYPE_4__* seaf_repo_manager_get_repo_list (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,...) ; 

gboolean
seaf_clone_manager_check_worktree_path (SeafCloneManager *mgr, const char *path, GError **error)
{
    GList *repos, *ptr;
    SeafRepo *repo;
    GHashTableIter iter;
    gpointer key, value;
    CloneTask *task;

    if (check_dir_inclusiveness (path, seaf->seaf_dir) != 0 ||
        /* It's OK if path is included by the default worktree parent. */
        check_dir_inclusiveness (path, seaf->worktree_dir) < 0 ||
        check_dir_inclusiveness (path, seaf->ccnet_dir) != 0) {
        seaf_warning ("Worktree path conflicts with seafile system path.\n");
        g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL,
                     "Worktree conflicts system path");
        return FALSE;
    }

    repos = seaf_repo_manager_get_repo_list (seaf->repo_mgr, -1, -1);
    for (ptr = repos; ptr != NULL; ptr = ptr->next) {
        repo = ptr->data;
        if (repo->worktree != NULL &&
            check_dir_inclusiveness (path, repo->worktree) != 0) {
            seaf_warning ("Worktree path conflict with repo %s.\n", repo->name);
            g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL,
                         "Worktree conflicts existing repo");
            g_list_free (repos);
            return FALSE;
        }
    }
    g_list_free (repos);

    g_hash_table_iter_init (&iter, mgr->tasks);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        task = value;
        if (task->state == CLONE_STATE_DONE ||
            task->state == CLONE_STATE_CANCELED)
            continue;
        if (check_dir_inclusiveness (path, task->worktree) != 0) {
            seaf_warning ("Worktree path conflict with clone %.8s.\n",
                          task->repo_id);
            g_set_error (error, SEAFILE_DOMAIN, SEAF_ERR_GENERAL,
                         "Worktree conflicts existing repo");
            return FALSE;
        }
    }

    return TRUE;
}