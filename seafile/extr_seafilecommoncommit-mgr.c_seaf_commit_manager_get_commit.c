#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SeafCommitManager ;
typedef  int /*<<< orphan*/  SeafCommit ;

/* Variables and functions */
 int /*<<< orphan*/ * load_commit (int /*<<< orphan*/ *,char const*,int,char const*) ; 

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