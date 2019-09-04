#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int gboolean ;
struct TYPE_2__ {int /*<<< orphan*/  repo_mgr; } ;

/* Variables and functions */
 int /*<<< orphan*/  REPO_SYNC_WORKTREE_NAME ; 
 int /*<<< orphan*/  g_free (char*) ; 
 scalar_t__ g_strcmp0 (char*,char*) ; 
 TYPE_1__* seaf ; 
 char* seaf_repo_manager_get_repo_property (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static gboolean
need_to_sync_worktree_name (const char *repo_id)
{
    char *need_sync_wt_name = seaf_repo_manager_get_repo_property (seaf->repo_mgr,
                                                                   repo_id,
                                                                   REPO_SYNC_WORKTREE_NAME);
    gboolean ret = (g_strcmp0(need_sync_wt_name, "true") == 0);
    g_free (need_sync_wt_name);
    return ret;
}