#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* gpointer ;
struct TYPE_10__ {TYPE_1__* priv; } ;
struct TYPE_9__ {int /*<<< orphan*/  paths; } ;
struct TYPE_8__ {int /*<<< orphan*/  active_paths; } ;
typedef  TYPE_3__ SeafSyncManager ;
typedef  int /*<<< orphan*/  GHashTableIter ;
typedef  TYPE_2__ ActivePathsInfo ;

/* Variables and functions */
 int /*<<< orphan*/  g_hash_table_iter_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_iter_next (int /*<<< orphan*/ *,TYPE_2__**,TYPE_2__**) ; 
 scalar_t__ g_hash_table_size (int /*<<< orphan*/ ) ; 

int
seaf_sync_manager_active_paths_number (SeafSyncManager *mgr)
{
    GHashTableIter iter;
    gpointer key, value;
    ActivePathsInfo *info;
    int ret = 0;

    g_hash_table_iter_init (&iter, mgr->priv->active_paths);
    while (g_hash_table_iter_next (&iter, &key, &value)) {
        info = value;
        ret += g_hash_table_size(info->paths);
    }

    return ret;
}