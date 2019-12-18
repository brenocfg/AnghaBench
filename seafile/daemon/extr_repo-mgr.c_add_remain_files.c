#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
struct cache_entry {unsigned char* sha1; } ;
typedef  scalar_t__ gint64 ;
typedef  scalar_t__ gboolean ;
struct TYPE_11__ {int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_10__ {int /*<<< orphan*/  changeset; int /*<<< orphan*/  id; int /*<<< orphan*/ * email; int /*<<< orphan*/  version; int /*<<< orphan*/  worktree; } ;
struct TYPE_9__ {int /*<<< orphan*/  st_mode; scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  TYPE_1__ SeafStat ;
typedef  TYPE_2__ SeafRepo ;
typedef  int /*<<< orphan*/  GQueue ;
typedef  int /*<<< orphan*/  GList ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_STATUS_ADDED ; 
 int /*<<< orphan*/  DIFF_STATUS_DIR_ADDED ; 
 scalar_t__ FALSE ; 
 scalar_t__ MAX_COMMIT_SIZE ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_INDEX_ERROR ; 
 int /*<<< orphan*/  SYNC_STATUS_ERROR ; 
 int /*<<< orphan*/  SYNC_STATUS_SYNCED ; 
 int /*<<< orphan*/  S_IFREG ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int add_empty_dir_to_index (struct index_state*,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  add_to_changeset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned char*,TYPE_1__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int add_to_index (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct index_state*,char*,char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  errno ; 
 char* g_build_filename (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_queue_pop_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  index_cb ; 
 struct cache_entry* index_name_exists (struct index_state*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_empty_dir (char*,int /*<<< orphan*/ *) ; 
 TYPE_4__* seaf ; 
 scalar_t__ seaf_stat (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  seaf_sync_manager_update_active_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_file_sync_error_notification (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static int
add_remain_files (SeafRepo *repo, struct index_state *istate,
                  SeafileCrypt *crypt, GQueue *remain_files,
                  GList *ignore_list, gint64 *total_size)
{
    char *path;
    char *full_path;
    SeafStat st;
    struct cache_entry *ce;

    while ((path = g_queue_pop_head (remain_files)) != NULL) {
        full_path = g_build_filename (repo->worktree, path, NULL);
        if (seaf_stat (full_path, &st) < 0) {
            seaf_warning ("Failed to stat %s: %s.\n", full_path, strerror(errno));
            g_free (path);
            g_free (full_path);
            continue;
        }

        if (S_ISREG(st.st_mode)) {
            gboolean added = FALSE;
            int ret = 0;
            ret = add_to_index (repo->id, repo->version, istate, path, full_path,
                                &st, 0, crypt, index_cb, repo->email, &added);
            if (added) {
                ce = index_name_exists (istate, path, strlen(path), 0);
                add_to_changeset (repo->changeset,
                                  DIFF_STATUS_ADDED,
                                  ce->sha1,
                                  &st,
                                  repo->email,
                                  path,
                                  NULL);

                *total_size += (gint64)(st.st_size);
                if (*total_size >= MAX_COMMIT_SIZE) {
                    g_free (path);
                    g_free (full_path);
                    break;
                }
            } else {
                seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                                      repo->id,
                                                      path,
                                                      S_IFREG,
                                                      SYNC_STATUS_SYNCED);
            }
            if (ret < 0) {
                seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                                      repo->id,
                                                      path,
                                                      S_IFREG,
                                                      SYNC_STATUS_ERROR);
                send_file_sync_error_notification (repo->id, NULL, path,
                                                   SYNC_ERROR_ID_INDEX_ERROR);
            }
        } else if (S_ISDIR(st.st_mode)) {
            if (is_empty_dir (full_path, ignore_list)) {
                int rc = add_empty_dir_to_index (istate, path, &st);
                if (rc == 1) {
                    unsigned char allzero[20] = {0};
                    add_to_changeset (repo->changeset,
                                      DIFF_STATUS_DIR_ADDED,
                                      allzero,
                                      &st,
                                      NULL,
                                      path,
                                      NULL);
                }
            }
        }
        g_free (path);
        g_free (full_path);
    }

    return 0;
}