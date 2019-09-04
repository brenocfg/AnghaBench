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
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* gpointer ;
struct TYPE_11__ {TYPE_1__* sync_mgr; } ;
struct TYPE_10__ {int /*<<< orphan*/  error; int /*<<< orphan*/  state; int /*<<< orphan*/  is_manual_sync; } ;
struct TYPE_9__ {int /*<<< orphan*/  repo_id; TYPE_3__* current_task; int /*<<< orphan*/  in_sync; } ;
struct TYPE_8__ {int /*<<< orphan*/ * sync_infos; } ;
typedef  TYPE_3__ SyncTask ;
typedef  TYPE_2__ SyncInfo ;
typedef  int /*<<< orphan*/  SeafileSyncTask ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GHashTableIter ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_TYPE_SYNC_TASK ; 
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,TYPE_2__**,TYPE_2__**) ; 
 int /*<<< orphan*/ * g_list_prepend (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_object_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_5__* seaf ; 
 int /*<<< orphan*/  sync_error_to_str (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_state_to_str (int /*<<< orphan*/ ) ; 

GList *
seafile_get_sync_task_list (GError **error)
{
    GHashTable *sync_info_tbl = seaf->sync_mgr->sync_infos;
    GHashTableIter iter;
    SeafileSyncTask *s_task;
    GList *task_list = NULL;
    gpointer key, value;

    g_hash_table_iter_init (&iter, sync_info_tbl);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        SyncInfo *info = value;
        if (!info->in_sync)
            continue;
        SyncTask *task = info->current_task;
        if (!task)
            continue;
        s_task = g_object_new (SEAFILE_TYPE_SYNC_TASK,
                               "force_upload", task->is_manual_sync,
                               "state", sync_state_to_str(task->state),
                               "error", sync_error_to_str(task->error),
                               "repo_id", info->repo_id,
                               NULL);
        task_list = g_list_prepend (task_list, s_task);
    }

    return task_list;
}