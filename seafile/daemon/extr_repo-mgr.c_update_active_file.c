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
struct index_state {int dummy; } ;
struct cache_entry {int dummy; } ;
typedef  scalar_t__ gboolean ;
struct TYPE_5__ {int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_4__ {int /*<<< orphan*/  id; int /*<<< orphan*/  is_readonly; } ;
typedef  scalar_t__ SyncStatus ;
typedef  int /*<<< orphan*/  SeafStat ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 scalar_t__ SYNC_STATUS_IGNORED ; 
 scalar_t__ SYNC_STATUS_SYNCED ; 
 scalar_t__ SYNC_STATUS_SYNCING ; 
 int /*<<< orphan*/  S_IFREG ; 
 scalar_t__ ie_match_stat (struct cache_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct cache_entry* index_name_exists (struct index_state*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_path_writable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_sync_manager_delete_active_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_sync_manager_update_active_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static void
update_active_file (SeafRepo *repo,
                    const char *path,
                    SeafStat *st,
                    struct index_state *istate,
                    gboolean ignored)
{
    if (ignored) {
        seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                              repo->id,
                                              path,
                                              S_IFREG,
                                              SYNC_STATUS_IGNORED);
    } else {
        SyncStatus status;
        gboolean is_writable;

        struct cache_entry *ce = index_name_exists(istate, path, strlen(path), 0);
        if (!ce || ie_match_stat(ce, st, 0) != 0)
            status = SYNC_STATUS_SYNCING;
        else
            status = SYNC_STATUS_SYNCED;

        is_writable = is_path_writable (repo->id, repo->is_readonly, path);

        if (!is_writable && status == SYNC_STATUS_SYNCING)
            seaf_sync_manager_delete_active_path (seaf->sync_mgr,
                                                  repo->id,
                                                  path);
        else
            seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                                  repo->id,
                                                  path,
                                                  S_IFREG,
                                                  status);
    }
}