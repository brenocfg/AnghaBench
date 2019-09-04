#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pthread_t ;
struct TYPE_8__ {TYPE_1__* priv; } ;
struct TYPE_7__ {void* update_tx_state_timer; void* check_sync_timer; } ;
typedef  TYPE_2__ SeafSyncManager ;
typedef  int /*<<< orphan*/  GCallback ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_SYNC_INTERVAL ; 
 int /*<<< orphan*/  UPDATE_TX_STATE_INTERVAL ; 
 int /*<<< orphan*/  auto_sync_pulse ; 
 int /*<<< orphan*/  g_signal_connect (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__*) ; 
 scalar_t__ on_repo_http_fetched ; 
 scalar_t__ on_repo_http_uploaded ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  seaf ; 
 void* seaf_timer_new (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 
 int /*<<< orphan*/  update_cached_head_commit_ids ; 
 int /*<<< orphan*/  update_tx_state ; 

int
seaf_sync_manager_start (SeafSyncManager *mgr)
{
    mgr->priv->check_sync_timer = seaf_timer_new (
        auto_sync_pulse, mgr, CHECK_SYNC_INTERVAL);

    mgr->priv->update_tx_state_timer = seaf_timer_new (
        update_tx_state, mgr, UPDATE_TX_STATE_INTERVAL);

    g_signal_connect (seaf, "repo-http-fetched",
                      (GCallback)on_repo_http_fetched, mgr);
    g_signal_connect (seaf, "repo-http-uploaded",
                      (GCallback)on_repo_http_uploaded, mgr);

#ifdef WIN32
    seaf_job_manager_schedule_job (seaf->job_mgr,
                                   refresh_windows_explorer_thread,
                                   NULL,
                                   mgr->priv->refresh_paths);

    mgr->priv->refresh_windows_timer = seaf_timer_new (
        refresh_all_windows_on_startup, mgr, STARTUP_REFRESH_WINDOWS_DELAY);
#endif

    pthread_t tid;
    if (pthread_create (&tid, NULL, update_cached_head_commit_ids, mgr) < 0) {
        seaf_warning ("Failed to create update cached head commit id thread.\n");
        return -1;
    }

    return 0;
}