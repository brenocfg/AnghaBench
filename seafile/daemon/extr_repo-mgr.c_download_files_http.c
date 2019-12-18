#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct index_state {int dummy; } ;
struct TYPE_17__ {int /*<<< orphan*/  sec; } ;
struct cache_entry {int ce_flags; scalar_t__ ce_size; int /*<<< orphan*/  ce_mode; scalar_t__ modifier; int /*<<< orphan*/  sha1; TYPE_1__ ce_mtime; } ;
typedef  scalar_t__ gint64 ;
typedef  int /*<<< orphan*/  data ;
struct TYPE_23__ {int /*<<< orphan*/  sync_mgr; } ;
struct TYPE_22__ {scalar_t__ status; char const* sha1; scalar_t__ size; int /*<<< orphan*/  name; int /*<<< orphan*/  mode; int /*<<< orphan*/  modifier; int /*<<< orphan*/  mtime; } ;
struct TYPE_21__ {int repo_version; int /*<<< orphan*/ * finished_tasks; int /*<<< orphan*/  conflict_head_id; TYPE_2__* http_task; int /*<<< orphan*/ * crypt; int /*<<< orphan*/  repo_id; } ;
struct TYPE_20__ {int result; struct cache_entry* ce; scalar_t__ new_ce; TYPE_6__* de; } ;
struct TYPE_19__ {TYPE_6__* data; struct TYPE_19__* next; } ;
struct TYPE_18__ {int /*<<< orphan*/  is_clone; int /*<<< orphan*/  all_stop; int /*<<< orphan*/  repo_name; } ;
typedef  int /*<<< orphan*/  SyncStatus ;
typedef  int /*<<< orphan*/  SeafileCrypt ;
typedef  int /*<<< orphan*/  LockedFileSet ;
typedef  TYPE_2__ HttpTxTask ;
typedef  int /*<<< orphan*/  GThreadPool ;
typedef  TYPE_3__ GList ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  int /*<<< orphan*/  GDestroyNotify ;
typedef  int /*<<< orphan*/  GAsyncQueue ;
typedef  TYPE_4__ FileTxTask ;
typedef  TYPE_5__ FileTxData ;
typedef  TYPE_6__ DiffEntry ;

/* Variables and functions */
 int ADD_CACHE_OK_TO_ADD ; 
 int ADD_CACHE_OK_TO_REPLACE ; 
 int CE_REMOVE ; 
 int /*<<< orphan*/  DEFAULT_DOWNLOAD_THREADS ; 
 scalar_t__ DIFF_STATUS_ADDED ; 
 scalar_t__ DIFF_STATUS_DIR_ADDED ; 
 scalar_t__ DIFF_STATUS_MODIFIED ; 
 int /*<<< orphan*/  FALSE ; 
 int FETCH_CHECKOUT_CANCELED ; 
 int FETCH_CHECKOUT_FAILED ; 
 int FETCH_CHECKOUT_SUCCESS ; 
 int FETCH_CHECKOUT_TRANSFER_ERROR ; 
 int /*<<< orphan*/  SYNC_STATUS_ERROR ; 
 int /*<<< orphan*/  SYNC_STATUS_SYNCED ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ UPDATE_CACHE_SIZE_LIMIT ; 
 int /*<<< orphan*/  add_index_entry (struct index_state*,struct cache_entry*,int) ; 
 int /*<<< orphan*/  cache_entry_free (struct cache_entry*) ; 
 int checkout_file_http (TYPE_5__*,TYPE_4__*,char const*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  create_ce_mode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fetch_file_thread_func ; 
 scalar_t__ file_tx_task_free ; 
 int /*<<< orphan*/ * g_async_queue_new () ; 
 TYPE_4__* g_async_queue_pop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_async_queue_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_free (scalar_t__) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (scalar_t__),int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_hash_table_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ g_hash_table_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 
 scalar_t__ g_strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_thread_pool_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * g_thread_pool_new (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  handle_dir_added_de (char const*,int /*<<< orphan*/ ,char const*,struct index_state*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rawdata_to_hex (char const*,char*,int) ; 
 int schedule_file_fetch (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,char const*,struct index_state*,TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_7__* seaf ; 
 int /*<<< orphan*/  seaf_sync_manager_update_active_path (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_index (struct index_state*,char const*) ; 

__attribute__((used)) static int
download_files_http (const char *repo_id,
                     int repo_version,
                     const char *worktree,
                     struct index_state *istate,
                     const char *index_path,
                     SeafileCrypt *crypt,
                     HttpTxTask *http_task,
                     GList *results,
                     GHashTable *conflict_hash,
                     GHashTable *no_conflict_hash,
                     const char *conflict_head_id,
                     LockedFileSet *fset)
{
    struct cache_entry *ce;
    DiffEntry *de;
    gint64 checkout_size = 0;
    GThreadPool *tpool;
    GAsyncQueue *finished_tasks;
    GHashTable *pending_tasks;
    GList *ptr;
    FileTxTask *task;
    int ret = FETCH_CHECKOUT_SUCCESS;

    finished_tasks = g_async_queue_new ();

    FileTxData data;
    memset (&data, 0, sizeof(data));
    memcpy (data.repo_id, repo_id, 36);
    data.repo_version = repo_version;
    data.crypt = crypt;
    data.http_task = http_task;
    memcpy (data.conflict_head_id, conflict_head_id, 40);
    data.finished_tasks = finished_tasks;

    tpool = g_thread_pool_new (fetch_file_thread_func, &data,
                               DEFAULT_DOWNLOAD_THREADS, FALSE, NULL);

    pending_tasks = g_hash_table_new_full (g_str_hash, g_str_equal,
                                           g_free, (GDestroyNotify)file_tx_task_free);

    for (ptr = results; ptr != NULL; ptr = ptr->next) {
        de = ptr->data;

        if (de->status == DIFF_STATUS_DIR_ADDED) {
            handle_dir_added_de (repo_id, http_task->repo_name, worktree, istate, de,
                                 conflict_hash, no_conflict_hash);
        } else if (de->status == DIFF_STATUS_ADDED ||
                   de->status == DIFF_STATUS_MODIFIED) {
            if (FETCH_CHECKOUT_FAILED == schedule_file_fetch (tpool,
                                                              repo_id,
                                                              http_task->repo_name,
                                                              worktree,
                                                              istate,
                                                              de,
                                                              pending_tasks,
                                                              conflict_hash,
                                                              no_conflict_hash))
                continue;
        }
    }

    /* If there is no file need to be downloaded, return immediately. */
    if (g_hash_table_size(pending_tasks) == 0) {
        if (results != NULL)
            update_index (istate, index_path);
        goto out;
    }

    char file_id[41];
    while ((task = g_async_queue_pop (finished_tasks)) != NULL) {
        ce = task->ce;
        de = task->de;

        rawdata_to_hex (de->sha1, file_id, 20);
        /* seaf_message ("Finished downloading file %s for repo %s\n", */
        /*               de->name, repo_id); */

        if (task->result == FETCH_CHECKOUT_CANCELED ||
            task->result == FETCH_CHECKOUT_TRANSFER_ERROR) {
            ret = task->result;
            if (task->new_ce)
                cache_entry_free (task->ce);
            http_task->all_stop = TRUE;
            goto out;
        }

        int rc = checkout_file_http (&data, task, worktree,
                                     conflict_hash, no_conflict_hash,
                                     conflict_head_id, fset);

        if (!http_task->is_clone) {
            SyncStatus status;
            if (rc == FETCH_CHECKOUT_FAILED)
                status = SYNC_STATUS_ERROR;
            else
                status = SYNC_STATUS_SYNCED;
            seaf_sync_manager_update_active_path (seaf->sync_mgr,
                                                  repo_id,
                                                  de->name,
                                                  de->mode,
                                                  status);
        }

        if (task->new_ce) {
            if (!(ce->ce_flags & CE_REMOVE)) {
                add_index_entry (istate, task->ce,
                                 (ADD_CACHE_OK_TO_ADD|ADD_CACHE_OK_TO_REPLACE));
            }
        } else {
            ce->ce_mtime.sec = de->mtime;
            ce->ce_size = de->size;
            memcpy (ce->sha1, de->sha1, 20);
            if (ce->modifier) g_free (ce->modifier);
            ce->modifier = g_strdup(de->modifier);
            ce->ce_mode = create_ce_mode (de->mode);
        }

        g_hash_table_remove (pending_tasks, de->name);

        if (g_hash_table_size (pending_tasks) == 0)
            break;

        /* Save index file to disk after checking out some size of files.
         * This way we don't need to re-compare too many files if this
         * checkout is interrupted.
         */
        checkout_size += ce->ce_size;
        if (checkout_size >= UPDATE_CACHE_SIZE_LIMIT) {
            update_index (istate, index_path);
            checkout_size = 0;
        }
    }

    update_index (istate, index_path);

out:
    /* Wait until all threads exit.
     * This is necessary when the download is canceled or encountered error.
     */
    g_thread_pool_free (tpool, TRUE, TRUE);

    /* Free all pending file task structs. */
    g_hash_table_destroy (pending_tasks);

    g_async_queue_unref (finished_tasks);

    return ret;
}