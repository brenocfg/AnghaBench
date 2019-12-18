#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  head_commit; int /*<<< orphan*/  is_corrupt; int /*<<< orphan*/  is_deleted; int /*<<< orphan*/  error_code; int /*<<< orphan*/  check_success; } ;
struct TYPE_8__ {int /*<<< orphan*/  head_commit; int /*<<< orphan*/  repo_corrupted; int /*<<< orphan*/  deleted_on_relay; } ;
struct TYPE_7__ {TYPE_2__* info; } ;
typedef  TYPE_1__ SyncTask ;
typedef  TYPE_2__ SyncInfo ;
typedef  TYPE_3__ HttpHeadCommit ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_task_error (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_sync_status_v2 (TYPE_1__*) ; 

__attribute__((used)) static void
check_head_commit_done (HttpHeadCommit *result, void *user_data)
{
    SyncTask *task = user_data;
    SyncInfo *info = task->info;

    if (!result->check_success) {
        set_task_error (task, result->error_code);
        return;
    }

    info->deleted_on_relay = result->is_deleted;
    info->repo_corrupted = result->is_corrupt;
    memcpy (info->head_commit, result->head_commit, 40);

    update_sync_status_v2 (task);
}