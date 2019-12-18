#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  synced_tree; int /*<<< orphan*/  syncing_tree; int /*<<< orphan*/  paths; } ;
typedef  TYPE_1__ ActivePathsInfo ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync_status_tree_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
active_paths_info_free (ActivePathsInfo *info)
{
    if (!info)
        return;
    g_hash_table_destroy (info->paths);
    sync_status_tree_free (info->syncing_tree);
    sync_status_tree_free (info->synced_tree);
    g_free (info);
}