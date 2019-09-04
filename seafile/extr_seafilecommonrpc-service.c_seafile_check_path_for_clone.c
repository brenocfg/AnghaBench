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
struct TYPE_2__ {int /*<<< orphan*/  clone_mgr; } ;
typedef  int /*<<< orphan*/  GError ;

/* Variables and functions */
 TYPE_1__* seaf ; 
 int /*<<< orphan*/  seaf_clone_manager_check_worktree_path (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ **) ; 

int
seafile_check_path_for_clone (const char *path, GError **error)
{
    if (!seaf_clone_manager_check_worktree_path(seaf->clone_mgr, path, error)) {
        return -1;
    }

    return 0;
}