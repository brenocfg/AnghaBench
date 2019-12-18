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
struct stat {int /*<<< orphan*/  st_mode; } ;
struct cache_entry {int dummy; } ;
typedef  scalar_t__ gboolean ;
struct TYPE_8__ {int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_7__ {scalar_t__ changeset; scalar_t__ startup_scan; int /*<<< orphan*/  is_repo_ro; } ;
struct TYPE_6__ {int /*<<< orphan*/ ** remain_files; int /*<<< orphan*/  istate; int /*<<< orphan*/  repo_id; TYPE_2__* options; int /*<<< orphan*/  total_size; int /*<<< orphan*/  crypt; int /*<<< orphan*/  modifier; int /*<<< orphan*/  version; int /*<<< orphan*/  ignore_list; int /*<<< orphan*/  worktree; } ;
typedef  scalar_t__ SyncStatus ;
typedef  struct stat SeafStat ;
typedef  int /*<<< orphan*/  GDir ;
typedef  TYPE_1__ AddParams ;
typedef  TYPE_2__ AddOptions ;

/* Variables and functions */
 int /*<<< orphan*/  DIFF_STATUS_DIR_ADDED ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  G_NORMALIZE_NFC ; 
 int /*<<< orphan*/  PATH_SEPERATOR ; 
 scalar_t__ SYNC_STATUS_ERROR ; 
 scalar_t__ SYNC_STATUS_IGNORED ; 
 scalar_t__ SYNC_STATUS_SYNCED ; 
 scalar_t__ SYNC_STATUS_SYNCING ; 
 int /*<<< orphan*/  S_IFDIR ; 
 int /*<<< orphan*/  S_IFREG ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int add_empty_dir_to_index (int /*<<< orphan*/ ,char const*,struct stat*) ; 
 int /*<<< orphan*/  add_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char*,struct stat*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,TYPE_2__*) ; 
 int /*<<< orphan*/  add_to_changeset (scalar_t__,int /*<<< orphan*/ ,unsigned char*,struct stat*,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 char* g_build_filename (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 char* g_build_path (int /*<<< orphan*/ ,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 char* g_dir_read_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_queue_push_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 char* g_utf8_normalize (char const*,int,int /*<<< orphan*/ ) ; 
 struct cache_entry* index_name_exists (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_path_writable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 TYPE_3__* seaf ; 
 int /*<<< orphan*/  seaf_sync_manager_update_active_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ should_ignore (char const*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static int
add_dir_recursive (const char *path, const char *full_path, SeafStat *st,
                   AddParams *params, gboolean ignored)
{
    AddOptions *options = params->options;
    GDir *dir;
    const char *dname;
    char *subpath, *full_subpath;
    int n, total;
    gboolean is_writable = TRUE;
    struct stat sub_st;

    dir = g_dir_open (full_path, 0, NULL);
    if (!dir) {
        seaf_warning ("Failed to open dir %s: %s.\n", full_path, strerror(errno));

        seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                              params->repo_id,
                                              path,
                                              S_IFDIR,
                                              SYNC_STATUS_ERROR);

        return 0;
    }

    n = 0;
    total = 0;
    while ((dname = g_dir_read_name(dir)) != NULL) {
        ++total;

#ifdef __APPLE__
        char *norm_dname = g_utf8_normalize (dname, -1, G_NORMALIZE_NFC);
        subpath = g_build_path (PATH_SEPERATOR, path, norm_dname, NULL);
        g_free (norm_dname);
#else
        subpath = g_build_path (PATH_SEPERATOR, path, dname, NULL);
#endif
        full_subpath = g_build_filename (params->worktree, subpath, NULL);

        if (stat (full_subpath, &sub_st) < 0) {
            seaf_warning ("Failed to stat %s: %s.\n", full_subpath, strerror(errno));
            g_free (subpath);
            g_free (full_subpath);
            continue;
        }

        if (ignored || should_ignore(full_path, dname, params->ignore_list)) {
            if (options && options->startup_scan) {
                if (S_ISDIR(sub_st.st_mode))
                    add_dir_recursive (subpath, full_subpath, &sub_st, params, TRUE);
                else
                    seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                                          params->repo_id,
                                                          subpath,
                                                          S_IFREG,
                                                          SYNC_STATUS_IGNORED);
            }
            g_free (subpath);
            g_free (full_subpath);
            continue;
        }

        ++n;

        if (S_ISDIR(sub_st.st_mode))
            add_dir_recursive (subpath, full_subpath, &sub_st, params, FALSE);
        else if (S_ISREG(sub_st.st_mode))
            add_file (params->repo_id,
                      params->version,
                      params->modifier,
                      params->istate,
                      subpath,
                      full_subpath,
                      &sub_st,
                      params->crypt,
                      params->total_size,
                      params->remain_files,
                      params->options);

        g_free (subpath);
        g_free (full_subpath);
    }
    g_dir_close (dir);

    if (ignored) {
        seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                              params->repo_id,
                                              path,
                                              S_IFDIR,
                                              SYNC_STATUS_IGNORED);
        return 0;
    }

    if (options)
        is_writable = is_path_writable(params->repo_id,
                                       options->is_repo_ro, path);

    /* Update active path status for empty dir */
    if (options && options->startup_scan && total == 0) {
        SyncStatus status;
        struct cache_entry *ce = index_name_exists (params->istate, path,
                                                    strlen(path), 0);
        if (!ce)
            status = SYNC_STATUS_SYNCING;
        else
            status = SYNC_STATUS_SYNCED;


        if (status == SYNC_STATUS_SYNCED || is_writable)
            seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                                  params->repo_id,
                                                  path,
                                                  S_IFDIR,
                                                  status);
    }

    if (n == 0 && path[0] != 0 && is_writable) {
        if (!params->remain_files || *(params->remain_files) == NULL) {
            int rc = add_empty_dir_to_index (params->istate, path, st);
            if (rc == 1 && options && options->changeset) {
                unsigned char allzero[20] = {0};
                add_to_changeset (options->changeset,
                                  DIFF_STATUS_DIR_ADDED,
                                  allzero,
                                  st,
                                  NULL,
                                  path,
                                  NULL);
            }
        } else
            g_queue_push_tail (*(params->remain_files), g_strdup(path));
    }

    return 0;
}