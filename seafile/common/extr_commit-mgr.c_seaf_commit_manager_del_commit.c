#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  commit_cache; } ;
typedef  TYPE_2__ SeafCommitManager ;

/* Variables and functions */
 int /*<<< orphan*/  commit ; 
 int /*<<< orphan*/  delete_commit (TYPE_2__*,char const*,int,char const*) ; 
 int /*<<< orphan*/  g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  g_return_if_fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_commit_from_cache (TYPE_2__*,int /*<<< orphan*/ ) ; 

void
seaf_commit_manager_del_commit (SeafCommitManager *mgr,
                                const char *repo_id,
                                int version,
                                const char *id)
{
    g_return_if_fail (id != NULL);

#if 0
    commit = g_hash_table_lookup(mgr->priv->commit_cache, id);
    if (!commit)
        goto delete;

    /*
     * Catch ref count bug here. We have bug in commit ref, the
     * following assert can't pass. TODO: fix the commit ref bug
     */
    /* g_assert (commit->ref <= 1); */
    remove_commit_from_cache (mgr, commit);

delete:
#endif

    delete_commit (mgr, repo_id, version, id);
}