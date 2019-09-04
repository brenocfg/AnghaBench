#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  wt_monitor; int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_7__ {TYPE_1__* data; struct TYPE_7__* next; } ;
struct TYPE_6__ {scalar_t__ sync_interval; int /*<<< orphan*/  id; } ;
typedef  int /*<<< orphan*/  SeafSyncManager ;
typedef  TYPE_1__ SeafRepo ;
typedef  TYPE_2__ GList ;

/* Variables and functions */
 int /*<<< orphan*/  g_list_free (TYPE_2__*) ; 
 TYPE_4__* seaf ; 
 TYPE_2__* seaf_repo_manager_get_repo_list (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  seaf_sync_manager_cancel_sync_task (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_sync_manager_remove_active_path_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_wt_monitor_unwatch_repo (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
disable_auto_sync_for_repos (SeafSyncManager *mgr)
{
    GList *repos;
    GList *ptr;
    SeafRepo *repo;

    repos = seaf_repo_manager_get_repo_list (seaf->repo_mgr, -1, -1);
    for (ptr = repos; ptr; ptr = ptr->next) {
        repo = ptr->data;
        if (repo->sync_interval == 0)
            seaf_wt_monitor_unwatch_repo (seaf->wt_monitor, repo->id);
        seaf_sync_manager_cancel_sync_task (mgr, repo->id);
        seaf_sync_manager_remove_active_path_info (mgr, repo->id);
    }

    g_list_free (repos);
}