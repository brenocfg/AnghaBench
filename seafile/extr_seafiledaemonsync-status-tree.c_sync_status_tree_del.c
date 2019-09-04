#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  guint ;
struct TYPE_3__ {int /*<<< orphan*/  worktree; int /*<<< orphan*/ * root; } ;
typedef  TYPE_1__ SyncStatusTree ;
typedef  int /*<<< orphan*/  SyncStatusDir ;

/* Variables and functions */
 int /*<<< orphan*/  delete_recursive (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strfreev (char**) ; 
 char** g_strsplit (char const*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_strv_length (char**) ; 

void
sync_status_tree_del (SyncStatusTree *tree,
                      const char *path)
{
    char **dnames = NULL;
    guint n;
    SyncStatusDir *dir = tree->root;

    dnames = g_strsplit (path, "/", 0);
    if (!dnames)
        return;
    n = g_strv_length (dnames);

    delete_recursive (dir, dnames, n, 0, tree->worktree);

    g_strfreev (dnames);
}