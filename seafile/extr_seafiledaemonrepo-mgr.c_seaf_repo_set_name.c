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
struct TYPE_4__ {char* name; int /*<<< orphan*/  id; } ;
typedef  TYPE_1__ SeafRepo ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  g_free (char*) ; 
 char* g_strdup (char const*) ; 
 scalar_t__ need_to_sync_worktree_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_repo_worktree_name (TYPE_1__*,char const*,int /*<<< orphan*/ ) ; 

void
seaf_repo_set_name (SeafRepo *repo, const char *new_name)
{
    char *old_name = repo->name;
    repo->name = g_strdup(new_name);
    g_free (old_name);

    if (need_to_sync_worktree_name (repo->id))
        update_repo_worktree_name (repo, new_name, TRUE);
}