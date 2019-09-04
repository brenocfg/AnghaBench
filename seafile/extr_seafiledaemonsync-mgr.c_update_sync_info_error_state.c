#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ err_cnt; scalar_t__ sync_perm_err_cnt; int /*<<< orphan*/  in_error; } ;
struct TYPE_4__ {scalar_t__ error; TYPE_2__* info; } ;
typedef  TYPE_1__ SyncTask ;
typedef  TYPE_2__ SyncInfo ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ IN_ERROR_THRESHOLD ; 
 scalar_t__ SYNC_ERROR_ACCESS_DENIED ; 
 int SYNC_STATE_ERROR ; 
 int /*<<< orphan*/  TRUE ; 

__attribute__((used)) static void
update_sync_info_error_state (SyncTask *task, int new_state)
{
    SyncInfo *info = task->info;

    if (new_state == SYNC_STATE_ERROR) {
        info->err_cnt++;
        if (info->err_cnt == IN_ERROR_THRESHOLD)
            info->in_error = TRUE;
        if (task->error == SYNC_ERROR_ACCESS_DENIED)
            info->sync_perm_err_cnt++;
    } else if (info->err_cnt > 0) {
        info->err_cnt = 0;
        info->in_error = FALSE;
        info->sync_perm_err_cnt = 0;
    }
}