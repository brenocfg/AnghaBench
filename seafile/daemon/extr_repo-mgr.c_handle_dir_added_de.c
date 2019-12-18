#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sec; } ;
struct cache_entry {int ce_flags; TYPE_1__ ce_mtime; } ;
typedef  scalar_t__ gboolean ;
struct TYPE_8__ {int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_7__ {int /*<<< orphan*/  mtime; int /*<<< orphan*/  mode; int /*<<< orphan*/  name; } ;
typedef  scalar_t__ IgnoreReason ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  TYPE_2__ DiffEntry ;

/* Variables and functions */
 int ADD_CACHE_OK_TO_ADD ; 
 int ADD_CACHE_OK_TO_REPLACE ; 
 int CE_REMOVE ; 
 scalar_t__ FALSE ; 
 scalar_t__ IGNORE_REASON_END_SPACE_PERIOD ; 
 scalar_t__ IGNORE_REASON_INVALID_CHARACTER ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_PATH_END_SPACE_PERIOD ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_PATH_INVALID_CHARACTER ; 
 int /*<<< orphan*/  SYNC_STATUS_SYNCED ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  add_index_entry (struct index_state*,struct cache_entry*,int) ; 
 struct cache_entry* cache_entry_from_diff_entry (TYPE_2__*) ; 
 int /*<<< orphan*/  checkout_empty_dir (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct cache_entry*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct cache_entry* index_name_exists (struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_sync_manager_update_active_path (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_file_sync_error_notification (char const*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ should_ignore_on_checkout (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_dir_added_de (const char *repo_id,
                     const char *repo_name,
                     const char *worktree,
                     struct index_state *istate,
                     DiffEntry *de,
                     GHashTable *conflict_hash,
                     GHashTable *no_conflict_hash)
{
    seaf_debug ("Checkout empty dir %s.\n", de->name);

    struct cache_entry *ce;
    gboolean add_ce = FALSE;

    ce = index_name_exists (istate, de->name, strlen(de->name), 0);
    if (!ce) {
        ce = cache_entry_from_diff_entry (de);
        add_ce = TRUE;
    }

    IgnoreReason reason;
    if (should_ignore_on_checkout (de->name, &reason)) {
        seaf_message ("Path %s is invalid on Windows, skip checkout\n",
                      de->name);
        if (reason == IGNORE_REASON_END_SPACE_PERIOD)
            send_file_sync_error_notification (repo_id, repo_name, de->name,
                                               SYNC_ERROR_ID_PATH_END_SPACE_PERIOD);
        else if (reason == IGNORE_REASON_INVALID_CHARACTER)
            send_file_sync_error_notification (repo_id, repo_name, de->name,
                                               SYNC_ERROR_ID_PATH_INVALID_CHARACTER);
        goto update_index;
    }

    checkout_empty_dir (worktree,
                        de->name,
                        de->mtime,
                        ce,
                        conflict_hash,
                        no_conflict_hash);

    seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                          repo_id,
                                          de->name,
                                          de->mode,
                                          SYNC_STATUS_SYNCED);

update_index:
    if (add_ce) {
        if (!(ce->ce_flags & CE_REMOVE)) {
            add_index_entry (istate, ce,
                             (ADD_CACHE_OK_TO_ADD|ADD_CACHE_OK_TO_REPLACE));
        }
    } else
        ce->ce_mtime.sec = de->mtime;
}