#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wchar_t ;
typedef  TYPE_1__* gpointer ;
struct TYPE_10__ {int /*<<< orphan*/  hash_lock; int /*<<< orphan*/  info_hash; int /*<<< orphan*/  handle_hash; } ;
struct TYPE_9__ {int /*<<< orphan*/  status; } ;
typedef  TYPE_2__ SeafWTMonitorPriv ;
typedef  TYPE_1__ RepoWatchInfo ;
typedef  int /*<<< orphan*/ * HANDLE ;

/* Variables and functions */
 int /*<<< orphan*/  WT_EVENT_SCAN_DIR ; 
 int /*<<< orphan*/  add_event_to_queue (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_1__* create_repo_watch_info (char const*,char const*) ; 
 int /*<<< orphan*/  g_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_insert (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* g_strdup (char const*) ; 
 int /*<<< orphan*/ * get_handle_of_path (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*) ; 
 int /*<<< orphan*/ * wchar_from_utf8 (char const*) ; 

__attribute__((used)) static HANDLE add_watch (SeafWTMonitorPriv *priv,
                         const char *repo_id,
                         const char *worktree)
{
    HANDLE dir_handle = NULL;
    wchar_t *path = NULL;
    RepoWatchInfo *info;

    /* worktree is in utf8, need to convert to wchar in win32 */
    path = wchar_from_utf8 (worktree);

    dir_handle = get_handle_of_path (path);
    if (!dir_handle) {
        seaf_warning ("failed to open handle for worktree "
                      "of repo  %s\n", repo_id);
        g_free (path);
        return NULL;
    }
    g_free (path);

    pthread_mutex_lock (&priv->hash_lock);
    g_hash_table_insert (priv->handle_hash,
                         g_strdup(repo_id), (gpointer)dir_handle);

    info = create_repo_watch_info (repo_id, worktree);
    g_hash_table_insert (priv->info_hash, (gpointer)dir_handle, info);
    pthread_mutex_unlock (&priv->hash_lock);

    add_event_to_queue (info->status, WT_EVENT_SCAN_DIR, "", NULL);

    return dir_handle;
}