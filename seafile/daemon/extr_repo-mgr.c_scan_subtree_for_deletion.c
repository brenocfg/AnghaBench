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
struct index_state {int dummy; } ;
typedef  int /*<<< orphan*/  gboolean ;
typedef  int /*<<< orphan*/  LockedFileSet ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  ChangeSet ;

/* Variables and functions */

__attribute__((used)) static void
scan_subtree_for_deletion (const char *repo_id,
                           struct index_state *istate,
                           const char *worktree,
                           const char *path,
                           GList *ignore_list,
                           LockedFileSet *fset,
                           gboolean is_readonly,
                           GList **scanned_dirs,
                           ChangeSet *changeset)
{
}