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
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  commit_cache; } ;
typedef  TYPE_2__ SeafCommitManager ;
typedef  int /*<<< orphan*/  SeafCommit ;

/* Variables and functions */
 int /*<<< orphan*/ * g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/ * load_commit (TYPE_2__*,char const*,int,char const*) ; 
 int /*<<< orphan*/  seaf_commit_ref (int /*<<< orphan*/ *) ; 

SeafCommit* 
seaf_commit_manager_get_commit (SeafCommitManager *mgr,
                                const char *repo_id,
                                int version,
                                const char *id)
{
    SeafCommit *commit;

#if 0
    commit = g_hash_table_lookup (mgr->priv->commit_cache, id);
    if (commit != NULL) {
        seaf_commit_ref (commit);
        return commit;
    }
#endif

    commit = load_commit (mgr, repo_id, version, id);
    if (!commit)
        return NULL;

    /* add_commit_to_cache (mgr, commit); */

    return commit;
}