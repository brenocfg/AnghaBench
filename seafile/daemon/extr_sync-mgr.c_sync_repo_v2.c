#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gboolean ;
struct TYPE_13__ {int /*<<< orphan*/  repo_mgr; int /*<<< orphan*/  branch_mgr; } ;
struct TYPE_12__ {char* commit_id; } ;
struct TYPE_11__ {int /*<<< orphan*/  last_sync_time; int /*<<< orphan*/  server_url; int /*<<< orphan*/  name; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  SyncTask ;
typedef  int /*<<< orphan*/  SeafSyncManager ;
typedef  TYPE_1__ SeafRepo ;
typedef  TYPE_2__ SeafBranch ;

/* Variables and functions */
 char* EMPTY_SHA1 ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  REPO_PROP_DOWNLOAD_HEAD ; 
 scalar_t__ can_schedule_repo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  check_head_commit_http (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  commit_repo (int /*<<< orphan*/ *) ; 
 scalar_t__ create_commit_from_event_queue (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/ * create_sync_task_v2 (int /*<<< orphan*/ *,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  need_check_on_server (int /*<<< orphan*/ *,TYPE_1__*,char*) ; 
 TYPE_6__* seaf ; 
 TYPE_2__* seaf_branch_manager_get_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seaf_branch_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* seaf_repo_manager_get_repo_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  start_fetch_if_necessary (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  start_upload_if_necessary (int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
sync_repo_v2 (SeafSyncManager *manager, SeafRepo *repo, gboolean is_manual_sync)
{
    SeafBranch *master, *local;
    SyncTask *task;
    int ret = 0;
    char *last_download = NULL;

    master = seaf_branch_manager_get_branch (seaf->branch_mgr, repo->id, "master");
    if (!master) {
        seaf_warning ("No master branch found for repo %s(%.8s).\n",
                      repo->name, repo->id);
        return -1;
    }
    local = seaf_branch_manager_get_branch (seaf->branch_mgr, repo->id, "local");
    if (!local) {
        seaf_warning ("No local branch found for repo %s(%.8s).\n",
                      repo->name, repo->id);
        return -1;
    }

    /* If last download was interrupted in the fetch and download stage,
     * need to resume it at exactly the same remote commit.
     */
    last_download = seaf_repo_manager_get_repo_property (seaf->repo_mgr,
                                                         repo->id,
                                                         REPO_PROP_DOWNLOAD_HEAD);
    if (last_download && strcmp (last_download, EMPTY_SHA1) != 0) {
        if (is_manual_sync || can_schedule_repo (manager, repo)) {
            task = create_sync_task_v2 (manager, repo, is_manual_sync, FALSE);
            start_fetch_if_necessary (task, last_download);
        }
        goto out;
    }

    if (strcmp (master->commit_id, local->commit_id) != 0) {
        if (is_manual_sync || can_schedule_repo (manager, repo)) {
            task = create_sync_task_v2 (manager, repo, is_manual_sync, FALSE);
            start_upload_if_necessary (task);
        }
        /* Do nothing if the client still has something to upload
         * but it's before 30-second schedule.
         */
        goto out;
    } else if (is_manual_sync) {
        task = create_sync_task_v2 (manager, repo, is_manual_sync, FALSE);
        commit_repo (task);
        goto out;
    } else if (create_commit_from_event_queue (manager, repo, is_manual_sync))
        goto out;

    if (is_manual_sync || can_schedule_repo (manager, repo)) {
        /* If file syncing protocol version is higher than 2, we check for all head commit ids
         * for synced repos regularly.
         */
        if (!is_manual_sync && !need_check_on_server (manager, repo, master->commit_id)) {
            seaf_debug ("Repo %s is not changed on server %s.\n", repo->name, repo->server_url);
            repo->last_sync_time = time(NULL);
            goto out;
        }

        task = create_sync_task_v2 (manager, repo, is_manual_sync, FALSE);
        check_head_commit_http (task);
    }

out:
    g_free (last_download);
    seaf_branch_unref (master);
    seaf_branch_unref (local);
    return ret;
}