#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  repo_mgr; } ;
struct TYPE_6__ {int /*<<< orphan*/  id; int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  SyncTask ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_ERROR_ID_SERVER_REPO_DELETED ; 
 TYPE_2__* seaf ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_repo_manager_del_repo (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seafile_session_config_get_allow_repo_not_found_on_server (TYPE_2__*) ; 
 int /*<<< orphan*/  set_task_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
on_repo_deleted_on_server (SyncTask *task, SeafRepo *repo)
{
    set_task_error (task, SYNC_ERROR_ID_SERVER_REPO_DELETED);

    seaf_warning ("repo %s(%.8s) not found on server\n",
                  repo->name, repo->id);

    if (!seafile_session_config_get_allow_repo_not_found_on_server(seaf)) {
        seaf_message ("remove repo %s(%.8s) since it's deleted on relay\n",
                      repo->name, repo->id);
        /* seaf_mq_manager_publish_notification (seaf->mq_mgr, */
        /*                                       "repo.deleted_on_relay", */
        /*                                       repo->name); */
        seaf_repo_manager_del_repo (seaf->repo_mgr, repo);
    }
}