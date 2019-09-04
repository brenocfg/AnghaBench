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
struct cache_entry {int /*<<< orphan*/  ce_mode; int /*<<< orphan*/  name; } ;
struct TYPE_2__ {int /*<<< orphan*/  sync_mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_STATUS_SYNCED ; 
 TYPE_1__* seaf ; 
 int /*<<< orphan*/  seaf_sync_manager_update_active_path (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
update_sync_status (struct cache_entry *ce, void *user_data)
{
    char *repo_id = user_data;

    seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                          repo_id,
                                          ce->name,
                                          ce->ce_mode,
                                          SYNC_STATUS_SYNCED);
}