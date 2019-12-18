#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sync_infos; } ;
typedef  int /*<<< orphan*/  SyncInfo ;
typedef  TYPE_1__ SeafSyncManager ;

/* Variables and functions */
 int /*<<< orphan*/ * g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 

SyncInfo *
seaf_sync_manager_get_sync_info (SeafSyncManager *mgr,
                                 const char *repo_id)
{
    return g_hash_table_lookup (mgr->sync_infos, repo_id);
}