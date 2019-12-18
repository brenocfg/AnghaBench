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
typedef  char const* gpointer ;
struct TYPE_3__ {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  info_hash; int /*<<< orphan*/  handle_hash; } ;
typedef  TYPE_1__ SeafWTMonitorPriv ;

/* Variables and functions */
 int /*<<< orphan*/  CloseHandle (char const*) ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int handle_rm_repo (SeafWTMonitorPriv *priv, const char *repo_id, gpointer handle)
{
    pthread_mutex_lock (&priv->hash_lock);
    g_hash_table_remove (priv->handle_hash, repo_id);
    g_hash_table_remove (priv->info_hash, handle);
    pthread_mutex_unlock (&priv->hash_lock);

    /* `aux' can't be freed here. Once we we close the dir_handle, its
     *  outstanding io would cause GetQueuedCompletionStatus() to return some
     *  information in aux->buf. If we free it here, it would cause seg fault.
     *  It will be freed in the completion code of GetQueuedCompletionStatus().
     */
    CloseHandle (handle);

    return 0;
}