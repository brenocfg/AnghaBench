#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct SyncStatusTree {struct SyncStatusTree* worktree; int /*<<< orphan*/  root; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_free (struct SyncStatusTree*) ; 
 int /*<<< orphan*/  sync_status_dir_free (int /*<<< orphan*/ ) ; 

void
sync_status_tree_free (struct SyncStatusTree *tree)
{
    if (!tree)
        return;

#ifdef WIN32
    /* refresh_recursive (tree->worktree, tree->root); */
#endif
    /* Free the tree recursively. */
    sync_status_dir_free (tree->root);

    g_free (tree->worktree);
    g_free (tree);
}