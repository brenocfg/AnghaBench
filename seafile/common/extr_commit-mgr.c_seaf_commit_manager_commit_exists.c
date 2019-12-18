#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gboolean ;
struct TYPE_5__ {int /*<<< orphan*/  obj_store; TYPE_1__* priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  commit_cache; } ;
typedef  TYPE_2__ SeafCommitManager ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * commit ; 
 int /*<<< orphan*/ * g_hash_table_lookup (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_obj_store_obj_exists (int /*<<< orphan*/ ,char const*,int,char const*) ; 

gboolean
seaf_commit_manager_commit_exists (SeafCommitManager *mgr,
                                   const char *repo_id,
                                   int version,
                                   const char *id)
{
#if 0
    commit = g_hash_table_lookup (mgr->priv->commit_cache, id);
    if (commit != NULL)
        return TRUE;
#endif

    return seaf_obj_store_obj_exists (mgr->obj_store, repo_id, version, id);
}