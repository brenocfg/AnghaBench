#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* gpointer ;
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_16__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_15__ {TYPE_2__* data; struct TYPE_15__* next; } ;
struct TYPE_14__ {int /*<<< orphan*/  tasks; } ;
struct TYPE_13__ {int /*<<< orphan*/  worktree; } ;
struct TYPE_12__ {scalar_t__ state; int /*<<< orphan*/  worktree; } ;
typedef  TYPE_2__ SeafRepo ;
typedef  TYPE_3__ SeafCloneManager ;
typedef  TYPE_4__ GList ;
typedef  int /*<<< orphan*/  GHashTableIter ;
typedef  TYPE_1__ CloneTask ;

/* Variables and functions */
 scalar_t__ CLONE_STATE_CANCELED ; 
 scalar_t__ CLONE_STATE_DONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,TYPE_1__**,TYPE_1__**) ; 
 int /*<<< orphan*/  g_list_free (TYPE_4__*) ; 
 scalar_t__ g_strcmp0 (char const*,int /*<<< orphan*/ ) ; 
 TYPE_7__* seaf ; 
 TYPE_4__* seaf_repo_manager_get_repo_list (int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static gboolean
is_worktree_of_repo (SeafCloneManager *mgr, const char *path)
{
    GList *repos, *ptr;
    SeafRepo *repo;
    GHashTableIter iter;
    gpointer key, value;
    CloneTask *task;

    repos = seaf_repo_manager_get_repo_list (seaf->repo_mgr, -1, -1);
    for (ptr = repos; ptr != NULL; ptr = ptr->next) {
        repo = ptr->data;
        if (g_strcmp0 (path, repo->worktree) == 0) {
            g_list_free (repos);
            return TRUE;
        }
    }
    g_list_free (repos);

    g_hash_table_iter_init (&iter, mgr->tasks);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        task = value;
        if (task->state == CLONE_STATE_DONE ||
            task->state == CLONE_STATE_CANCELED)
            continue;
        if (g_strcmp0 (path, task->worktree) == 0)
            return TRUE;
    }

    return FALSE;
}