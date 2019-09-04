#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* worktree; int /*<<< orphan*/  rename_info; int /*<<< orphan*/  mapping; int /*<<< orphan*/  status; } ;
typedef  TYPE_1__ RepoWatchInfo ;

/* Variables and functions */
 int /*<<< orphan*/  free_mapping (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_rename_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (TYPE_1__*) ; 
 int /*<<< orphan*/  wt_status_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
free_repo_watch_info (RepoWatchInfo *info)
{
    wt_status_unref (info->status);
    free_mapping (info->mapping);
    free_rename_info (info->rename_info);
    g_free (info->worktree);
    g_free (info);
}