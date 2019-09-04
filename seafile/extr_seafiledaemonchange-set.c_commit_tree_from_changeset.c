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
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_3__ {int /*<<< orphan*/  tree_root; int /*<<< orphan*/  repo_id; } ;
typedef  TYPE_1__ ChangeSet ;

/* Variables and functions */
 char* commit_tree_recursive (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

char *
commit_tree_from_changeset (ChangeSet *changeset)
{
    gint64 mtime;
    char *root_id = commit_tree_recursive (changeset->repo_id,
                                           changeset->tree_root,
                                           &mtime);

    return root_id;
}