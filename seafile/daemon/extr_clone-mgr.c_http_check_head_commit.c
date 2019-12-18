#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  http_tx_mgr; } ;
struct TYPE_6__ {int /*<<< orphan*/  use_fileserver_port; int /*<<< orphan*/  token; int /*<<< orphan*/  effective_url; int /*<<< orphan*/  repo_version; int /*<<< orphan*/  repo_id; } ;
typedef  TYPE_1__ CloneTask ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_ERROR_ID_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/  check_head_commit_done ; 
 int http_tx_manager_check_head_commit (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  transition_to_error (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
http_check_head_commit (CloneTask *task)
{
    int ret = http_tx_manager_check_head_commit (seaf->http_tx_mgr,
                                                 task->repo_id,
                                                 task->repo_version,
                                                 task->effective_url,
                                                 task->token,
                                                 task->use_fileserver_port,
                                                 check_head_commit_done,
                                                 task);
    if (ret < 0)
        transition_to_error (task, SYNC_ERROR_ID_NOT_ENOUGH_MEMORY);
}