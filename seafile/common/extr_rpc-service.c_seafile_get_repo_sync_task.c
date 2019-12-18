#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  sync_mgr; int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_6__ {int /*<<< orphan*/  repo_id; int /*<<< orphan*/  head_commit; int /*<<< orphan*/  in_sync; TYPE_1__* current_task; } ;
struct TYPE_5__ {int /*<<< orphan*/  error; int /*<<< orphan*/  is_manual_sync; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ SyncTask ;
typedef  TYPE_2__ SyncInfo ;
typedef  int /*<<< orphan*/  SeafileSyncTask ;
typedef  int /*<<< orphan*/  SeafRepo ;
typedef  int /*<<< orphan*/  GObject ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_TYPE_SYNC_TASK ; 
 int /*<<< orphan*/ * g_object_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,char const*,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* seaf ; 
 int /*<<< orphan*/ * seaf_repo_manager_get_repo (int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* seaf_sync_manager_get_sync_info (int /*<<< orphan*/ ,char const*) ; 
 char* sync_state_to_str (int /*<<< orphan*/ ) ; 

GObject *
seafile_get_repo_sync_task (const char *repo_id, GError **error)
{
    SeafRepo *repo;
    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, repo_id);

    if (!repo) {
        return NULL;
    }

    SyncInfo *info = seaf_sync_manager_get_sync_info (seaf->sync_mgr, repo_id);
    if (!info || !info->current_task)
        return NULL;

    SyncTask *task = info->current_task;
    const char *sync_state;
    char allzeros[41] = {0};

    if (!info->in_sync && memcmp(allzeros, info->head_commit, 41) == 0) {
        sync_state = "waiting for sync";
    } else {
        sync_state = sync_state_to_str(task->state);
    }

    SeafileSyncTask *s_task;
    s_task = g_object_new (SEAFILE_TYPE_SYNC_TASK,
                           "force_upload", task->is_manual_sync,
                           "state", sync_state,
                           "error", task->error,
                           "repo_id", info->repo_id,
                           NULL);

    return (GObject *)s_task;
}