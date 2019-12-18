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
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_4__ {int /*<<< orphan*/  conflict; scalar_t__ new_merge; scalar_t__ second_parent_id; } ;
typedef  TYPE_1__ SeafCommit ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  seaf_commit_ref (TYPE_1__*) ; 

__attribute__((used)) static gboolean
find_meaningful_commit (SeafCommit *commit, void *data, gboolean *stop)
{
    SeafCommit **p_head = data;

    if (commit->second_parent_id && commit->new_merge && !commit->conflict)
        return TRUE;

    *stop = TRUE;
    seaf_commit_ref (commit);
    *p_head = commit;
    return TRUE;
}