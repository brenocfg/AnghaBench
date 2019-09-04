#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  started; int /*<<< orphan*/  filelock_mgr; int /*<<< orphan*/  clone_mgr; int /*<<< orphan*/  repo_mgr; int /*<<< orphan*/  wt_monitor; int /*<<< orphan*/  sync_mgr; int /*<<< orphan*/  http_tx_mgr; int /*<<< orphan*/  ev_mgr; } ;
typedef  TYPE_1__ SeafileSession ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ cevent_manager_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_error (char*) ; 
 scalar_t__ http_tx_manager_start (int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_clone_manager_start (int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_filelock_manager_start (int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_repo_manager_start (int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_sync_manager_start (int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_wt_monitor_start (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
cleanup_job_done (void *vdata)
{
    SeafileSession *session = vdata;

    if (cevent_manager_start (session->ev_mgr) < 0) {
        g_error ("Failed to start event manager.\n");
        return;
    }

    if (http_tx_manager_start (session->http_tx_mgr) < 0) {
        g_error ("Failed to start http transfer manager.\n");
        return;
    }

    if (seaf_sync_manager_start (session->sync_mgr) < 0) {
        g_error ("Failed to start sync manager.\n");
        return;
    }

    if (seaf_wt_monitor_start (session->wt_monitor) < 0) {
        g_error ("Failed to start worktree monitor.\n");
        return;
    }

    /* Must be after wt monitor, since we may add watch to repo worktree. */
    if (seaf_repo_manager_start (session->repo_mgr) < 0) {
        g_error ("Failed to start repo manager.\n");
        return;
    }

    if (seaf_clone_manager_start (session->clone_mgr) < 0) {
        g_error ("Failed to start clone manager.\n");
        return;
    }

    if (seaf_filelock_manager_start (session->filelock_mgr) < 0) {
        g_error ("Failed to start filelock manager.\n");
        return;
    }

    /* The system is up and running. */
    session->started = TRUE;
}