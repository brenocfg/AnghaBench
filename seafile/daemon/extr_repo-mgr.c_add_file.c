#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
struct cache_entry {int /*<<< orphan*/  sha1; } ;
typedef  scalar_t__ gint64 ;
typedef  scalar_t__ gboolean ;
struct TYPE_14__ {int /*<<< orphan*/  sync_mgr; int /*<<< orphan*/  filelock_mgr; } ;
struct TYPE_13__ {scalar_t__ changeset; scalar_t__ fset; scalar_t__ startup_scan; int /*<<< orphan*/  is_repo_ro; } ;
struct TYPE_12__ {scalar_t__ old_mtime; int /*<<< orphan*/  operation; } ;
struct TYPE_11__ {scalar_t__ st_mtime; scalar_t__ st_size; } ;
typedef  scalar_t__ SyncStatus ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  TYPE_1__ SeafStat ;
typedef  TYPE_2__ LockedFile ;
typedef  int /*<<< orphan*/  GQueue ;
typedef  TYPE_3__ AddOptions ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_STATUS_ADDED ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  LOCKED_OP_DELETE ; 
 int /*<<< orphan*/  LOCKED_OP_UPDATE ; 
 scalar_t__ MAX_COMMIT_SIZE ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_INDEX_ERROR ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_UPDATE_TO_READ_ONLY_REPO ; 
 scalar_t__ SYNC_STATUS_ERROR ; 
 scalar_t__ SYNC_STATUS_SYNCED ; 
 scalar_t__ SYNC_STATUS_SYNCING ; 
 int /*<<< orphan*/  S_IFREG ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  add_to_changeset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int add_to_index (char const*,int,struct index_state*,char const*,char const*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,scalar_t__*) ; 
 int /*<<< orphan*/ * g_queue_new () ; 
 int /*<<< orphan*/  g_queue_push_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 scalar_t__ ie_match_stat (struct cache_entry*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  index_cb ; 
 struct cache_entry* index_name_exists (struct index_state*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_path_writable (char const*,int /*<<< orphan*/ ,char const*) ; 
 TYPE_2__* locked_file_set_lookup (scalar_t__,char const*) ; 
 int /*<<< orphan*/  locked_file_set_remove (scalar_t__,char const*,scalar_t__) ; 
 TYPE_4__* seaf ; 
 scalar_t__ seaf_filelock_manager_is_file_locked (int /*<<< orphan*/ ,char const*,char const*) ; 
 int /*<<< orphan*/  seaf_sync_manager_update_active_path (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  send_file_sync_error_notification (char const*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
add_file (const char *repo_id,
          int version,
          const char *modifier,
          struct index_state *istate, 
          const char *path,
          const char *full_path,
          SeafStat *st,
          SeafileCrypt *crypt,
          gint64 *total_size,
          GQueue **remain_files,
          AddOptions *options)
{
    gboolean added = FALSE;
    int ret = 0;
    gboolean is_writable = TRUE, is_locked = FALSE;
    struct cache_entry *ce;

    if (options)
        is_writable = is_path_writable(repo_id,
                                       options->is_repo_ro, path);

    is_locked = seaf_filelock_manager_is_file_locked (seaf->filelock_mgr,
                                                      repo_id, path);
    if (is_locked && options && !(options->startup_scan)) {
        /* send_sync_error_notification (repo_id, NULL, path, */
        /*                               SYNC_ERROR_ID_FILE_LOCKED); */
    }

    if (options && options->startup_scan) {
        SyncStatus status;

        ce = index_name_exists (istate, path, strlen(path), 0);
        if (!ce || ie_match_stat(ce, st, 0) != 0)
            status = SYNC_STATUS_SYNCING;
        else
            status = SYNC_STATUS_SYNCED;

        /* Don't set "syncing" status for read-only path. */
        if (status == SYNC_STATUS_SYNCED || (is_writable && !is_locked))
            seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                                  repo_id,
                                                  path,
                                                  S_IFREG,
                                                  status);
        /* send an error notification for read-only repo when modifying a file. */
        if (status == SYNC_STATUS_SYNCING && !is_writable)
            send_file_sync_error_notification (repo_id, NULL, path,
                                               SYNC_ERROR_ID_UPDATE_TO_READ_ONLY_REPO);
    }

    if (!is_writable || is_locked)
        return ret;

#if defined WIN32 || defined __APPLE__
    if (options && options->fset) {
        LockedFile *file = locked_file_set_lookup (options->fset, path);
        if (file) {
            if (strcmp (file->operation, LOCKED_OP_DELETE) == 0) {
                /* Only remove the lock record if the file is changed. */
                if (st->st_mtime == file->old_mtime) {
                    return ret;
                }
                locked_file_set_remove (options->fset, path, FALSE);
            } else if (strcmp (file->operation, LOCKED_OP_UPDATE) == 0) {
                return ret;
            }
        }
    }
#endif

    if (!remain_files) {
        ret = add_to_index (repo_id, version, istate, path, full_path,
                            st, 0, crypt, index_cb, modifier, &added);
        if (!added) {
            /* If the contents of the file doesn't change, move it to
               synced status.
            */
            seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                                  repo_id,
                                                  path,
                                                  S_IFREG,
                                                  SYNC_STATUS_SYNCED);
        } else {
            if (total_size)
                *total_size += (gint64)(st->st_size);
            if (options && options->changeset) {
                /* ce may be updated. */
                ce = index_name_exists (istate, path, strlen(path), 0);
                add_to_changeset (options->changeset,
                                  DIFF_STATUS_ADDED,
                                  ce->sha1,
                                  st,
                                  modifier,
                                  path,
                                  NULL);
            }
        }
    } else if (*remain_files == NULL) {
        ret = add_to_index (repo_id, version, istate, path, full_path,
                            st, 0, crypt, index_cb, modifier, &added);
        if (added) {
            *total_size += (gint64)(st->st_size);
            if (*total_size >= MAX_COMMIT_SIZE)
                *remain_files = g_queue_new ();
        } else {
            seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                                  repo_id,
                                                  path,
                                                  S_IFREG,
                                                  SYNC_STATUS_SYNCED);
        }
        if (added && options && options->changeset) {
            /* ce may be updated. */
            ce = index_name_exists (istate, path, strlen(path), 0);
            add_to_changeset (options->changeset,
                              DIFF_STATUS_ADDED,
                              ce->sha1,
                              st,
                              modifier,
                              path,
                              NULL);
        }
    } else {
        *total_size += (gint64)(st->st_size);
        g_queue_push_tail (*remain_files, g_strdup(path));
    }

    if (ret < 0) {
        seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                              repo_id,
                                              path,
                                              S_IFREG,
                                              SYNC_STATUS_ERROR);
        send_file_sync_error_notification (repo_id, NULL, path,
                                           SYNC_ERROR_ID_INDEX_ERROR);
    }

    return ret;
}