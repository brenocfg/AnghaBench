#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  options ;
typedef  int /*<<< orphan*/  gint64 ;
typedef  scalar_t__ gboolean ;
struct TYPE_9__ {int /*<<< orphan*/  new_path; int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ WTEvent ;
struct TYPE_12__ {int /*<<< orphan*/  filelock_mgr; int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_11__ {int /*<<< orphan*/  changeset; int /*<<< orphan*/  is_repo_ro; int /*<<< orphan*/ * fset; } ;
struct TYPE_10__ {int /*<<< orphan*/  worktree; int /*<<< orphan*/  email; int /*<<< orphan*/  version; int /*<<< orphan*/  id; int /*<<< orphan*/  changeset; int /*<<< orphan*/  is_readonly; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  TYPE_2__ SeafRepo ;
typedef  int /*<<< orphan*/  LockedFileSet ;
typedef  int /*<<< orphan*/  GList ;
typedef  TYPE_3__ AddOptions ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_STATUS_DELETED ; 
 int /*<<< orphan*/  DIFF_STATUS_RENAMED ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  add_recursive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  add_to_changeset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ check_full_path_ignore (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ check_locked_file_before_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ignore_xlsx_update (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_path_writable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_seafile_backup_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remove_from_changeset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_from_index_with_prefix (struct index_state*,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  rename_index_entries (struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_subtree_for_deletion (int /*<<< orphan*/ ,struct index_state*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 TYPE_4__* seaf ; 
 int /*<<< orphan*/  seaf_debug (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ seaf_filelock_manager_is_file_locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_sync_manager_delete_active_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  try_add_empty_parent_dir_entry_from_wt (int /*<<< orphan*/ ,struct index_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
handle_rename (SeafRepo *repo, struct index_state *istate,
               SeafileCrypt *crypt, GList *ignore_list,
               LockedFileSet *fset,
               WTEvent *event, GList **scanned_del_dirs,
               gint64 *total_size)
{
    gboolean not_found, src_ignored, dst_ignored;

    seaf_sync_manager_delete_active_path (seaf->sync_mgr, repo->id, event->path);

    if (!is_path_writable(repo->id,
                          repo->is_readonly, event->path) ||
        !is_path_writable(repo->id,
                          repo->is_readonly, event->new_path)) {
        seaf_debug ("Rename: %s or %s is not writable, ignore.\n",
                    event->path, event->new_path);
        return;
    }

    if (seaf_filelock_manager_is_file_locked (seaf->filelock_mgr,
                                              repo->id, event->path)) {
        seaf_debug ("Rename: %s is locked on server, ignore.\n", event->path);
        /* send_sync_error_notification (repo->id, NULL, event->path, */
        /*                               SYNC_ERROR_ID_FILE_LOCKED); */
        return;
    }

    if (seaf_filelock_manager_is_file_locked (seaf->filelock_mgr,
                                              repo->id, event->new_path)) {
        seaf_debug ("Rename: %s is locked on server, ignore.\n", event->new_path);
        /* send_sync_error_notification (repo->id, NULL, event->new_path, */
        /*                               SYNC_ERROR_ID_FILE_LOCKED); */
        return;
    }

    src_ignored = check_full_path_ignore(repo->worktree, event->path, ignore_list);
    dst_ignored = check_full_path_ignore(repo->worktree, event->new_path, ignore_list);

    /* If the destination path is ignored, just remove the source path. */
    if (dst_ignored) {
        if (!src_ignored &&
            !is_seafile_backup_file (event->new_path) &&
            check_locked_file_before_remove (fset, event->path)) {
            not_found = FALSE;
            remove_from_index_with_prefix (istate, event->path, &not_found);
            if (not_found)
                scan_subtree_for_deletion (repo->id,
                                           istate,
                                           repo->worktree, event->path,
                                           ignore_list, fset,
                                           repo->is_readonly,
                                           scanned_del_dirs,
                                           repo->changeset);

            remove_from_changeset (repo->changeset,
                                   DIFF_STATUS_DELETED,
                                   event->path,
                                   FALSE,
                                   NULL);
        }
        return;
    }

    /* Now the destination path is not ignored. */

    if (!src_ignored && !ignore_xlsx_update (event->path, event->new_path) &&
        check_locked_file_before_remove (fset, event->path)) {
        not_found = FALSE;
        rename_index_entries (istate, event->path, event->new_path, &not_found,
                              NULL, NULL);
        if (not_found)
            scan_subtree_for_deletion (repo->id,
                                       istate,
                                       repo->worktree, event->path,
                                       ignore_list, fset,
                                       repo->is_readonly,
                                       scanned_del_dirs,
                                       repo->changeset);

        /* Moving files out of a dir may make it empty. */
        try_add_empty_parent_dir_entry_from_wt (repo->worktree,
                                                istate,
                                                ignore_list,
                                                event->path);

        add_to_changeset (repo->changeset,
                          DIFF_STATUS_RENAMED,
                          NULL,
                          NULL,
                          NULL,
                          event->path,
                          event->new_path);
    }

    AddOptions options;
    memset (&options, 0, sizeof(options));
    options.fset = fset;
    options.is_repo_ro = repo->is_readonly;
    options.changeset = repo->changeset;

    /* We should always scan the destination to compare with the renamed
     * index entries. For example, in the following case:
     * 1. file a.txt is updated;
     * 2. a.txt is moved to test/a.txt;
     * If the two operations are executed in a batch, the updated content
     * of a.txt won't be committed if we don't scan the destination, because
     * when we process the update event, a.txt is already not in its original
     * place.
     */
    add_recursive (repo->id, repo->version, repo->email,
                   istate, repo->worktree, event->new_path,
                   crypt, FALSE, ignore_list,
                   total_size, NULL, &options);
}