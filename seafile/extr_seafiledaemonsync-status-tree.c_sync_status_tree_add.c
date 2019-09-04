#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t guint ;
struct TYPE_10__ {int /*<<< orphan*/  dirents; } ;
struct TYPE_9__ {TYPE_3__* subdir; int /*<<< orphan*/  mode; } ;
struct TYPE_8__ {char* worktree; TYPE_3__* root; } ;
typedef  TYPE_1__ SyncStatusTree ;
typedef  TYPE_2__ SyncStatusDirent ;
typedef  TYPE_3__ SyncStatusDir ;
typedef  int /*<<< orphan*/  GString ;

/* Variables and functions */
 int S_IFDIR ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 TYPE_2__* g_hash_table_lookup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_strdup (char*) ; 
 int /*<<< orphan*/  g_strfreev (char**) ; 
 int /*<<< orphan*/  g_string_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  g_string_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_string_new (char*) ; 
 char** g_strsplit (char const*,char*,int /*<<< orphan*/ ) ; 
 size_t g_strv_length (char**) ; 
 TYPE_2__* sync_status_dirent_new (char*,int) ; 

void
sync_status_tree_add (SyncStatusTree *tree,
                      const char *path,
                      int mode)
{
    char **dnames = NULL;
    guint n, i;
    char *dname;
    SyncStatusDir *dir = tree->root;
    SyncStatusDirent *dirent;
    GString *buf;

    dnames = g_strsplit (path, "/", 0);
    if (!dnames)
        return;
    n = g_strv_length (dnames);

    buf = g_string_new ("");
    g_string_append (buf, tree->worktree);

    for (i = 0; i < n; i++) {
        dname = dnames[i];
        dirent = g_hash_table_lookup (dir->dirents, dname);
        g_string_append (buf, "/");
        g_string_append (buf, dname);
        if (dirent) {
            if (S_ISDIR(dirent->mode)) {
                if (i == (n-1)) {
                    goto out;
                } else {
                    dir = dirent->subdir;
                }
            } else {
                goto out;
            }
        } else {
            if (i == (n-1)) {
                dirent = sync_status_dirent_new (dname, mode);
                g_hash_table_insert (dir->dirents, g_strdup(dname), dirent);
            } else {
                dirent = sync_status_dirent_new (dname, S_IFDIR);
                g_hash_table_insert (dir->dirents, g_strdup(dname), dirent);
                dir = dirent->subdir;
            }
#ifdef WIN32
            seaf_sync_manager_add_refresh_path (seaf->sync_mgr, buf->str);
#endif
        }
    }

out:
    g_string_free (buf, TRUE);
    g_strfreev (dnames);
}