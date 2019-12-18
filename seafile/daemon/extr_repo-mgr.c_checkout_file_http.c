#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ sec; } ;
struct cache_entry {int /*<<< orphan*/  ce_flags; TYPE_1__ ce_mtime; } ;
typedef  int gboolean ;
struct TYPE_19__ {int /*<<< orphan*/  filelock_mgr; int /*<<< orphan*/  fs_mgr; } ;
struct TYPE_18__ {char* name; int /*<<< orphan*/  mtime; int /*<<< orphan*/  mode; int /*<<< orphan*/  sha1; } ;
struct TYPE_17__ {char* repo_id; int repo_version; TYPE_3__* http_task; int /*<<< orphan*/ * crypt; } ;
struct TYPE_16__ {int no_checkout; int force_conflict; int /*<<< orphan*/  path; int /*<<< orphan*/  new_ce; TYPE_6__* de; struct cache_entry* ce; } ;
struct TYPE_15__ {int /*<<< orphan*/  is_clone; int /*<<< orphan*/  email; } ;
struct TYPE_14__ {scalar_t__ st_mtime; int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  TYPE_2__ SeafStat ;
typedef  int /*<<< orphan*/  LockedFileSet ;
typedef  TYPE_3__ HttpTxTask ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  TYPE_4__ FileTxTask ;
typedef  TYPE_5__ FileTxData ;
typedef  TYPE_6__ DiffEntry ;

/* Variables and functions */
 int /*<<< orphan*/  CE_REMOVE ; 
 int FALSE ; 
 int FETCH_CHECKOUT_FAILED ; 
 int FETCH_CHECKOUT_SUCCESS ; 
 int /*<<< orphan*/  LOCKED_OP_UPDATE ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_CONFLICT ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_FILE_LOCKED_BY_APP ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 scalar_t__ check_path_conflict (char*,char**) ; 
 int /*<<< orphan*/  cleanup_file_blocks_http (TYPE_3__*,char*) ; 
 scalar_t__ do_check_file_locked (char*,char const*,int) ; 
 int /*<<< orphan*/  fill_stat_cache_info (struct cache_entry*,TYPE_2__*) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  locked_file_set_add_update (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  locked_file_set_lookup (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rawdata_to_hex (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_8__* seaf ; 
 int seaf_filelock_manager_is_file_locked (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  seaf_filelock_manager_lock_wt_file (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  seaf_filelock_manager_unlock_wt_file (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ seaf_fs_manager_checkout_file (int /*<<< orphan*/ ,char*,int,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,char const*,int,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_message (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ seaf_stat (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_file_sync_error_notification (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ should_ignore_on_checkout (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
checkout_file_http (FileTxData *data,
                    FileTxTask *file_task,
                    const char *worktree,
                    GHashTable *conflict_hash,
                    GHashTable *no_conflict_hash,
                    const char *conflict_head_id,
                    LockedFileSet *fset)
{
    char *repo_id = data->repo_id;
    int repo_version = data->repo_version;
    struct cache_entry *ce = file_task->ce;
    DiffEntry *de = file_task->de;
    SeafileCrypt *crypt = data->crypt;
    gboolean no_checkout = file_task->no_checkout;
    gboolean force_conflict = file_task->force_conflict;
    HttpTxTask *http_task = data->http_task;
    gboolean path_exists;
    gboolean case_conflict = FALSE;
    SeafStat st;
    char file_id[41];
    gboolean locked_on_server = FALSE;

    if (no_checkout)
        return FETCH_CHECKOUT_SUCCESS;

    if (should_ignore_on_checkout (de->name, NULL))
        return FETCH_CHECKOUT_SUCCESS;

    rawdata_to_hex (de->sha1, file_id, 20);

    locked_on_server = seaf_filelock_manager_is_file_locked (seaf->filelock_mgr,
                                                             repo_id, de->name);

#if defined WIN32 || defined __APPLE__
    if (do_check_file_locked (de->name, worktree, locked_on_server)) {
        if (!locked_file_set_lookup (fset, de->name))
            send_file_sync_error_notification (repo_id, NULL, de->name,
                                               SYNC_ERROR_ID_FILE_LOCKED_BY_APP);

        locked_file_set_add_update (fset, de->name, LOCKED_OP_UPDATE,
                                    ce->ce_mtime.sec, file_id);
        /* Stay in syncing status if the file is locked. */

        return FETCH_CHECKOUT_SUCCESS;
    }
#endif

    path_exists = (seaf_stat (file_task->path, &st) == 0);

    /* The worktree file may have been changed when we're downloading the blocks. */
    if (!file_task->new_ce &&
        path_exists && S_ISREG(st.st_mode) &&
        !force_conflict) {
        if (st.st_mtime != ce->ce_mtime.sec) {
            seaf_message ("File %s is updated by user. "
                          "Will checkout to conflict file later.\n", file_task->path);
            force_conflict = TRUE;
        }
    }

    /* Temporarily unlock the file if it's locked on server, so that the client
     * itself can write to it. 
     */
    if (locked_on_server)
        seaf_filelock_manager_unlock_wt_file (seaf->filelock_mgr,
                                              repo_id, de->name);

    /* then checkout the file. */
    gboolean conflicted = FALSE;
    if (seaf_fs_manager_checkout_file (seaf->fs_mgr,
                                       repo_id,
                                       repo_version,
                                       file_id,
                                       file_task->path,
                                       de->mode,
                                       de->mtime,
                                       crypt,
                                       de->name,
                                       conflict_head_id,
                                       force_conflict,
                                       &conflicted,
                                       http_task->email) < 0) {
        seaf_warning ("Failed to checkout file %s.\n", file_task->path);

        if (seaf_filelock_manager_is_file_locked (seaf->filelock_mgr,
                                                  repo_id, de->name))
            seaf_filelock_manager_lock_wt_file (seaf->filelock_mgr,
                                                repo_id, de->name);

        return FETCH_CHECKOUT_FAILED;
    }

    if (locked_on_server)
        seaf_filelock_manager_lock_wt_file (seaf->filelock_mgr,
                                            repo_id, de->name);

    cleanup_file_blocks_http (http_task, file_id);

    if (conflicted) {
        send_file_sync_error_notification (repo_id, NULL, de->name, SYNC_ERROR_ID_CONFLICT);
    } else if (!http_task->is_clone) {
        char *orig_path = NULL;
        if (check_path_conflict (de->name, &orig_path))
            send_file_sync_error_notification (repo_id, NULL, orig_path, SYNC_ERROR_ID_CONFLICT);
        g_free (orig_path);
    }

    /* If case conflict, this file will be checked out to another path.
     * Remove the current entry, otherwise it won't be removed later
     * since it's timestamp is 0.
     */
    if (case_conflict)
        ce->ce_flags |= CE_REMOVE;

    /* finally fill cache_entry info */
    /* Only update index if we checked out the file without any error
     * or conflicts. The ctime of the entry will remain 0 if error.
     */
    seaf_stat (file_task->path, &st);
    fill_stat_cache_info (ce, &st);

    return FETCH_CHECKOUT_SUCCESS;
}