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
typedef  size_t guint ;
struct TYPE_8__ {int /*<<< orphan*/  dirents; } ;
struct TYPE_7__ {TYPE_3__* subdir; int /*<<< orphan*/  mode; } ;
struct TYPE_6__ {TYPE_3__* root; } ;
typedef  TYPE_1__ SyncStatusTree ;
typedef  TYPE_2__ SyncStatusDirent ;
typedef  TYPE_3__ SyncStatusDir ;

/* Variables and functions */
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 TYPE_2__* g_hash_table_lookup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  g_strfreev (char**) ; 
 char** g_strsplit (char const*,char*,int /*<<< orphan*/ ) ; 
 size_t g_strv_length (char**) ; 

int
sync_status_tree_exists (SyncStatusTree *tree,
                         const char *path)
{
    char **dnames = NULL;
    guint n, i;
    char *dname;
    SyncStatusDir *dir = tree->root;
    SyncStatusDirent *dirent;
    int ret = 0;

    dnames = g_strsplit (path, "/", 0);
    if (!dnames)
        return ret;
    n = g_strv_length (dnames);

    for (i = 0; i < n; i++) {
        dname = dnames[i];
        dirent = g_hash_table_lookup (dir->dirents, dname);
        if (dirent) {
            if (S_ISDIR(dirent->mode)) {
                if (i == (n-1)) {
                    ret = 1;
                    goto out;
                } else {
                    dir = dirent->subdir;
                }
            } else {
                if (i == (n-1)) {
                    ret = 1;
                    goto out;
                } else {
                    goto out;
                }
            }
        } else {
            goto out;
        }
    }

out:
    g_strfreev (dnames);
    return ret;
}