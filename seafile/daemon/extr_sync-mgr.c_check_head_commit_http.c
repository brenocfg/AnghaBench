#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  http_tx_mgr; } ;
struct TYPE_9__ {int /*<<< orphan*/  use_fileserver_port; int /*<<< orphan*/  token; int /*<<< orphan*/  effective_host; int /*<<< orphan*/  version; int /*<<< orphan*/  id; } ;
struct TYPE_8__ {TYPE_2__* repo; } ;
typedef  TYPE_1__ SyncTask ;
typedef  TYPE_2__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_ERROR_ID_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  SYNC_STATE_INIT ; 
 int /*<<< orphan*/  check_head_commit_done ; 
 int http_tx_manager_check_head_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_5__* seaf ; 
 int /*<<< orphan*/  set_task_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transition_sync_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
check_head_commit_http (SyncTask *task)
{
    SeafRepo *repo = task->repo;

    int ret = http_tx_manager_check_head_commit (seaf->http_tx_mgr,
                                                 repo->id, repo->version,
                                                 repo->effective_host,
                                                 repo->token,
                                                 repo->use_fileserver_port,
                                                 check_head_commit_done,
                                                 task);
    if (ret == 0)
        transition_sync_state (task, SYNC_STATE_INIT);
    else if (ret < 0)
        set_task_error (task, SYNC_ERROR_ID_NOT_ENOUGH_MEMORY);

    return ret;
}