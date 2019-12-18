#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  void* gpointer ;
struct TYPE_4__ {int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_3__ {int /*<<< orphan*/  repo_id; } ;
typedef  TYPE_1__ HttpTxTask ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_STATUS_SYNCING ; 
 TYPE_2__* seaf ; 
 int /*<<< orphan*/  seaf_sync_manager_update_active_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
set_path_status_syncing (gpointer key, gpointer value, gpointer user_data)
{
    HttpTxTask *task = user_data;
    char *path = key;
    int mode = (int)(long)value;
    seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                          task->repo_id,
                                          path,
                                          mode,
                                          SYNC_STATUS_SYNCING);
}