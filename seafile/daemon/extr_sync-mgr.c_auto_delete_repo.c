#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  mq_mgr; int /*<<< orphan*/  repo_mgr; int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_9__ {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
struct TYPE_8__ {scalar_t__ in_sync; } ;
typedef  TYPE_1__ SyncInfo ;
typedef  int /*<<< orphan*/  SeafSyncManager ;
typedef  TYPE_2__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (int /*<<< orphan*/ ) ; 
 TYPE_6__* seaf ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_mq_manager_publish_notification (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  seaf_repo_manager_del_repo (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_repo_manager_mark_repo_deleted (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_sync_manager_cancel_sync_task (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* seaf_sync_manager_get_sync_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
auto_delete_repo (SeafSyncManager *manager, SeafRepo *repo)
{
    SyncInfo *info = seaf_sync_manager_get_sync_info (manager, repo->id);
    char *name = g_strdup (repo->name);

    seaf_message ("Auto deleted repo '%s'.\n", repo->name);

    seaf_sync_manager_cancel_sync_task (seaf->sync_mgr, repo->id);

    if (info != NULL && info->in_sync) {
        seaf_repo_manager_mark_repo_deleted (seaf->repo_mgr, repo);
    } else {
        seaf_repo_manager_del_repo (seaf->repo_mgr, repo);
    }

    /* Publish a message, for applet to notify in the system tray */
    seaf_mq_manager_publish_notification (seaf->mq_mgr,
                                          "repo.removed",
                                          name);
    g_free (name);
}