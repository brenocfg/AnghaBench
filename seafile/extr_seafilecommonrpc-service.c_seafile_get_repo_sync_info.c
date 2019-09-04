#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_4__ {int /*<<< orphan*/  need_merge; int /*<<< orphan*/  need_upload; int /*<<< orphan*/  need_fetch; int /*<<< orphan*/  deleted_on_relay; int /*<<< orphan*/  head_commit; int /*<<< orphan*/  repo_id; } ;
typedef  TYPE_1__ SyncInfo ;
typedef  int /*<<< orphan*/  SeafileSyncInfo ;
typedef  int /*<<< orphan*/  GObject ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 int /*<<< orphan*/  SEAFILE_TYPE_SYNC_INFO ; 
 int /*<<< orphan*/ * g_object_new (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_3__* seaf ; 
 TYPE_1__* seaf_sync_manager_get_sync_info (int /*<<< orphan*/ ,char const*) ; 

GObject *
seafile_get_repo_sync_info (const char *repo_id, GError **error)
{
    SyncInfo *info;

    info = seaf_sync_manager_get_sync_info (seaf->sync_mgr, repo_id);
    if (!info)
        return NULL;

    SeafileSyncInfo *sinfo;
    sinfo = g_object_new (SEAFILE_TYPE_SYNC_INFO,
                          "repo_id", info->repo_id,
                          "head_commit", info->head_commit,
                          "deleted_on_relay", info->deleted_on_relay,
                          "need_fetch", info->need_fetch,
                          "need_upload", info->need_upload,
                          "need_merge", info->need_merge,
                          /* "last_sync_time", info->last_sync_time,  */
                          NULL);

    return (GObject *)sinfo;
}