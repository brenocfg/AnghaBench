#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct stat {int /*<<< orphan*/  st_mode; } ;
struct index_state {int dummy; } ;
struct cache_entry {int dummy; } ;
typedef  scalar_t__ gboolean ;
struct TYPE_9__ {int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_8__ {int /*<<< orphan*/  message; } ;
struct TYPE_7__ {int /*<<< orphan*/  id; int /*<<< orphan*/  is_readonly; int /*<<< orphan*/  worktree; } ;
typedef  int /*<<< orphan*/  SyncStatus ;
typedef  TYPE_1__ SeafRepo ;
typedef  int /*<<< orphan*/  GList ;
typedef  TYPE_2__ GError ;
typedef  int /*<<< orphan*/  GDir ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  G_NORMALIZE_NFC ; 
 int /*<<< orphan*/  SYNC_STATUS_IGNORED ; 
 int /*<<< orphan*/  SYNC_STATUS_SYNCED ; 
 int /*<<< orphan*/  SYNC_STATUS_SYNCING ; 
 int /*<<< orphan*/  S_IFDIR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  errno ; 
 char* g_build_filename (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_dir_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_dir_open (char*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 char* g_dir_read_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strconcat (char const*,char*,char*,int /*<<< orphan*/ *) ; 
 char* g_utf8_normalize (char const*,int,int /*<<< orphan*/ ) ; 
 struct cache_entry* index_name_exists (struct index_state*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_path_writable (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 TYPE_5__* seaf ; 
 int /*<<< orphan*/  seaf_sync_manager_update_active_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ should_ignore (char*,char*,int /*<<< orphan*/ *) ; 
 scalar_t__ stat (char*,struct stat*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  update_active_file (TYPE_1__*,char*,struct stat*,struct index_state*,scalar_t__) ; 

__attribute__((used)) static void
update_active_path_recursive (SeafRepo *repo,
                              const char *path,
                              struct index_state *istate,
                              GList *ignore_list,
                              gboolean ignored)
{
    GDir *dir;
    GError *error = NULL;
    const char *name;
    char *dname;
    char *full_path, *full_sub_path, *sub_path;
    struct stat st;
    gboolean ignore_sub;

    full_path = g_build_filename(repo->worktree, path, NULL);

    dir = g_dir_open (full_path, 0, &error);
    if (!dir) {
        seaf_warning ("Failed to open dir %s: %s.\n", full_path, error->message);
        g_free (full_path);
        return;
    }

    int n = 0;
    while ((name = g_dir_read_name(dir)) != NULL) {
        ++n;

        dname = g_utf8_normalize (name, -1, G_NORMALIZE_NFC);
        sub_path = g_strconcat (path, "/", dname, NULL);
        full_sub_path = g_strconcat (full_path, "/", dname, NULL);

        ignore_sub = FALSE;
        if (ignored || should_ignore(full_path, dname, ignore_list))
            ignore_sub = TRUE;

        if (stat (full_sub_path, &st) < 0) {
            seaf_warning ("Failed to stat %s: %s.\n", full_sub_path, strerror(errno));
            g_free (dname);
            g_free (sub_path);
            g_free (full_sub_path);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            update_active_path_recursive (repo, sub_path, istate, ignore_list,
                                          ignore_sub);
        } else if (S_ISREG(st.st_mode)) {
            update_active_file (repo, sub_path, &st, istate,
                                ignore_sub);
        }

        g_free (dname);
        g_free (sub_path);
        g_free (full_sub_path);
    }

    g_dir_close (dir);

    g_free (full_path);

    /* Don't set sync status for read-only paths, since changes to read-only
     * files are ignored.
     */
    if (!is_path_writable (repo->id, repo->is_readonly, path))
        return;

    if (n == 0 && path[0] != 0) {
        if (ignored) {
            seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                                  repo->id,
                                                  path,
                                                  S_IFDIR,
                                                  SYNC_STATUS_IGNORED);
        } else {
            /* There is no need to update an empty dir. */
            SyncStatus status;
            struct cache_entry *ce = index_name_exists(istate, path, strlen(path), 0);
            if (!ce)
                status = SYNC_STATUS_SYNCING;
            else
                status = SYNC_STATUS_SYNCED;
            seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                                  repo->id,
                                                  path,
                                                  S_IFDIR,
                                                  status);
        }
    }
}