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
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_15__ {int /*<<< orphan*/  is_readonly; int /*<<< orphan*/  auto_sync; } ;
struct TYPE_14__ {TYPE_1__* priv; } ;
struct TYPE_13__ {TYPE_2__* current_task; scalar_t__ in_sync; int /*<<< orphan*/  head_commit; scalar_t__ in_error; } ;
struct TYPE_12__ {scalar_t__ state; } ;
struct TYPE_11__ {int /*<<< orphan*/  auto_sync_enabled; } ;
typedef  TYPE_3__ SyncInfo ;
typedef  TYPE_4__ SeafSyncManager ;
typedef  TYPE_5__ SeafRepo ;

/* Variables and functions */
 scalar_t__ SYNC_STATE_COMMIT ; 
 scalar_t__ SYNC_STATE_FETCH ; 
 scalar_t__ SYNC_STATE_MERGE ; 
 scalar_t__ SYNC_STATE_UPLOAD ; 
 size_t SYNC_STATUS_ERROR ; 
 size_t SYNC_STATUS_NONE ; 
 size_t SYNC_STATUS_PAUSED ; 
 size_t SYNC_STATUS_READONLY ; 
 size_t SYNC_STATUS_SYNCED ; 
 size_t SYNC_STATUS_SYNCING ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 TYPE_3__* get_sync_info (TYPE_4__*,char const*) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * path_status_tbl ; 
 TYPE_7__* seaf ; 
 TYPE_5__* seaf_repo_manager_get_repo (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static char *
get_repo_sync_status (SeafSyncManager *mgr, const char *repo_id)
{
    SyncInfo *info = get_sync_info (mgr, repo_id);
    SeafRepo *repo;

    if (info->in_error)
        return g_strdup(path_status_tbl[SYNC_STATUS_ERROR]);

    repo = seaf_repo_manager_get_repo (seaf->repo_mgr, repo_id);
    if (!repo)
        return g_strdup(path_status_tbl[SYNC_STATUS_NONE]);

    if (!repo->auto_sync || !mgr->priv->auto_sync_enabled)
        return g_strdup(path_status_tbl[SYNC_STATUS_PAUSED]);

    char allzeros[41] = {0};
    if (!info->in_sync && memcmp(allzeros, info->head_commit, 41) == 0)
        return g_strdup(path_status_tbl[SYNC_STATUS_NONE]);

    if (info->in_sync &&
        (info->current_task->state == SYNC_STATE_COMMIT ||
         info->current_task->state == SYNC_STATE_FETCH ||
         info->current_task->state == SYNC_STATE_UPLOAD ||
         info->current_task->state == SYNC_STATE_MERGE))
        return g_strdup(path_status_tbl[SYNC_STATUS_SYNCING]);
    else if (!repo->is_readonly)
        return g_strdup(path_status_tbl[SYNC_STATUS_SYNCED]);
    else
        return g_strdup(path_status_tbl[SYNC_STATUS_READONLY]);
}