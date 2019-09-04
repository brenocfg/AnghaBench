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
struct TYPE_4__ {int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ SeafRepo ;
typedef  int /*<<< orphan*/  SeafBranch ;

/* Variables and functions */
 scalar_t__ save_branch_repo_map (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_head_common (TYPE_1__*,int /*<<< orphan*/ *) ; 

int
seaf_repo_set_head (SeafRepo *repo, SeafBranch *branch)
{
    if (save_branch_repo_map (repo->manager, branch) < 0)
        return -1;
    set_head_common (repo, branch);
    return 0;
}