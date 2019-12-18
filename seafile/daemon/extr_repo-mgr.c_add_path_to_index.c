#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  options ;
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_19__ {int /*<<< orphan*/  changeset; int /*<<< orphan*/  is_repo_ro; int /*<<< orphan*/ * fset; int /*<<< orphan*/  startup_scan; } ;
struct TYPE_18__ {char* data; struct TYPE_18__* next; } ;
struct TYPE_17__ {int /*<<< orphan*/  worktree; int /*<<< orphan*/  email; int /*<<< orphan*/  version; int /*<<< orphan*/  id; int /*<<< orphan*/  changeset; int /*<<< orphan*/  is_readonly; int /*<<< orphan*/  name; } ;
struct TYPE_16__ {int /*<<< orphan*/  st_mode; } ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  TYPE_1__ SeafStat ;
typedef  TYPE_2__ SeafRepo ;
typedef  int /*<<< orphan*/  LockedFileSet ;
typedef  int /*<<< orphan*/  GQueue ;
typedef  TYPE_3__ GList ;
typedef  TYPE_4__ AddOptions ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_INDEX_ERROR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  add_recursive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct index_state*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **,TYPE_4__*) ; 
 scalar_t__ check_full_path_ignore (int /*<<< orphan*/ ,char const*,TYPE_3__*) ; 
 scalar_t__ errno ; 
 char* g_build_filename (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 TYPE_3__* g_list_prepend (TYPE_3__*,int /*<<< orphan*/ ) ; 
 char* g_strconcat (char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_strdup (char const*) ; 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  remove_deleted (struct index_state*,int /*<<< orphan*/ ,char*,TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_debug (char*,char const*) ; 
 scalar_t__ seaf_stat (char*,TYPE_1__*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  send_file_sync_error_notification (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strcmp (char*,char const*) ; 
 int /*<<< orphan*/  strerror (scalar_t__) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
add_path_to_index (SeafRepo *repo, struct index_state *istate,
                   SeafileCrypt *crypt, const char *path, GList *ignore_list,
                   GList **scanned_dirs, gint64 *total_size, GQueue **remain_files,
                   LockedFileSet *fset)
{
    char *full_path;
    SeafStat st;
    AddOptions options;

    /* When a repo is initially added, a SCAN_DIR event will be created
     * for the worktree root "".
     */
    if (path[0] == 0) {
        remove_deleted (istate, repo->worktree, "", ignore_list, fset,
                        repo->id, repo->is_readonly, repo->changeset);

        memset (&options, 0, sizeof(options));
        options.fset = fset;
        options.is_repo_ro = repo->is_readonly;
        options.startup_scan = TRUE;
        options.changeset = repo->changeset;

        add_recursive (repo->id, repo->version, repo->email, istate,
                       repo->worktree, path,
                       crypt, FALSE, ignore_list,
                       total_size, remain_files, &options);

        return 0;
    }

    /* If we've recursively scanned the parent directory, don't need to scan
     * any files under it any more.
     */
    GList *ptr;
    char *dir, *full_dir;
    for (ptr = *scanned_dirs; ptr; ptr = ptr->next) {
        dir = ptr->data;
        /* exact match */
        if (strcmp (dir, path) == 0) {
            seaf_debug ("%s has been scanned before, skip adding.\n", path);
            return 0;
        }

        /* prefix match. */
        full_dir = g_strconcat (dir, "/", NULL);
        if (strncmp (full_dir, path, strlen(full_dir)) == 0) {
            g_free (full_dir);
            seaf_debug ("%s has been scanned before, skip adding.\n", path);
            return 0;
        }
        g_free (full_dir);
    }

    if (check_full_path_ignore (repo->worktree, path, ignore_list))
        return 0;

    full_path = g_build_filename (repo->worktree, path, NULL);

    if (seaf_stat (full_path, &st) < 0) {
        if (errno != ENOENT)
            send_file_sync_error_notification (repo->id, repo->name, path,
                                               SYNC_ERROR_ID_INDEX_ERROR);
        seaf_warning ("Failed to stat %s: %s.\n", path, strerror(errno));
        g_free (full_path);
        return -1;
    }

    if (S_ISDIR(st.st_mode))
        *scanned_dirs = g_list_prepend (*scanned_dirs, g_strdup(path));

    memset (&options, 0, sizeof(options));
    options.fset = fset;
    options.is_repo_ro = repo->is_readonly;
    options.changeset = repo->changeset;

    /* Add is always recursive */
    add_recursive (repo->id, repo->version, repo->email, istate, repo->worktree, path,
                   crypt, FALSE, ignore_list, total_size, remain_files, &options);

    g_free (full_path);
    return 0;
}