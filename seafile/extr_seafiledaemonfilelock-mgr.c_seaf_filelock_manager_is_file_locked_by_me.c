#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int gboolean ;
struct TYPE_7__ {scalar_t__ locked_by_me; } ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/ * repo_locked_files; } ;
typedef  TYPE_2__ SeafFilelockManager ;
typedef  TYPE_3__ LockInfo ;
typedef  int /*<<< orphan*/  GHashTable ;

/* Variables and functions */
 int FALSE ; 
 void* g_hash_table_lookup (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

gboolean
seaf_filelock_manager_is_file_locked_by_me (SeafFilelockManager *mgr,
                                            const char *repo_id,
                                            const char *path)
{
    gboolean ret;

    pthread_mutex_lock (&mgr->priv->hash_lock);

    GHashTable *locks = g_hash_table_lookup (mgr->priv->repo_locked_files, repo_id);
    if (!locks) {
        pthread_mutex_unlock (&mgr->priv->hash_lock);
        return FALSE;
    }

    LockInfo *info = g_hash_table_lookup (locks, path);
    if (!info) {
        pthread_mutex_unlock (&mgr->priv->hash_lock);
        return FALSE;
    }
    ret = (info->locked_by_me > 0);

    pthread_mutex_unlock (&mgr->priv->hash_lock);
    return ret;
}