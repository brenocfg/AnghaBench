#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_6__ {scalar_t__ state; } ;
struct TYPE_5__ {int /*<<< orphan*/  tasks; } ;
typedef  TYPE_1__ SeafCloneManager ;
typedef  TYPE_2__ CloneTask ;

/* Variables and functions */
 scalar_t__ CLONE_STATE_CANCELED ; 
 scalar_t__ CLONE_STATE_DONE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static gboolean
is_duplicate_task (SeafCloneManager *mgr, const char *repo_id)
{
    CloneTask *task = g_hash_table_lookup (mgr->tasks, repo_id);
    if (task != NULL &&
        task->state != CLONE_STATE_DONE &&
        task->state != CLONE_STATE_CANCELED)
        return TRUE;
    return FALSE;
}