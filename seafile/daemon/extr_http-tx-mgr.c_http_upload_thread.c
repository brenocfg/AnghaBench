#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  gint64 ;
struct TYPE_23__ {scalar_t__ state; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  host; int /*<<< orphan*/  n_blocks; int /*<<< orphan*/  use_fileserver_port; void* error; int /*<<< orphan*/  head; } ;
struct TYPE_22__ {int /*<<< orphan*/  commit_id; } ;
struct TYPE_21__ {int /*<<< orphan*/ * priv; } ;
struct TYPE_20__ {int /*<<< orphan*/  branch_mgr; TYPE_1__* http_tx_mgr; } ;
typedef  TYPE_2__ SeafBranch ;
typedef  TYPE_3__ HttpTxTask ;
typedef  int /*<<< orphan*/  HttpTxPriv ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  GHashTable ;
typedef  int /*<<< orphan*/  ConnectionPool ;
typedef  int /*<<< orphan*/  Connection ;

/* Variables and functions */
 int /*<<< orphan*/  HTTP_TASK_RT_STATE_BLOCK ; 
 int /*<<< orphan*/  HTTP_TASK_RT_STATE_CHECK ; 
 int /*<<< orphan*/  HTTP_TASK_RT_STATE_COMMIT ; 
 int /*<<< orphan*/  HTTP_TASK_RT_STATE_FS ; 
 int /*<<< orphan*/  HTTP_TASK_RT_STATE_UPDATE_BRANCH ; 
 scalar_t__ HTTP_TASK_STATE_CANCELED ; 
 void* SYNC_ERROR_ID_LOCAL_DATA_CORRUPT ; 
 void* SYNC_ERROR_ID_NOT_ENOUGH_MEMORY ; 
 scalar_t__ calculate_block_list (TYPE_3__*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * calculate_send_fs_object_list (TYPE_3__*) ; 
 scalar_t__ calculate_upload_size_delta_and_active_paths (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ check_permission (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ check_quota (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * connection_pool_get_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connection_pool_return_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_connection_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_free (char*) ; 
 int /*<<< orphan*/  g_hash_table_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_hash_table_foreach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/ * g_hash_table_new_full (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (char*),int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_list_length (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_str_equal ; 
 int /*<<< orphan*/  g_str_hash ; 
 char* g_strdup_printf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ multi_threaded_send_blocks (TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_12__* seaf ; 
 TYPE_2__* seaf_branch_manager_get_branch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  seaf_branch_unref (TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ,...) ; 
 scalar_t__ send_commit_object (TYPE_3__*,int /*<<< orphan*/ *) ; 
 scalar_t__ send_fs_objects (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  set_path_status_synced ; 
 int /*<<< orphan*/  set_path_status_syncing ; 
 int /*<<< orphan*/  string_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transition_state (TYPE_3__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ update_branch (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_master_branch (TYPE_3__*) ; 
 scalar_t__ upload_check_id_list_segment (TYPE_3__*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void *
http_upload_thread (void *vdata)
{
    HttpTxTask *task = vdata;
    HttpTxPriv *priv = seaf->http_tx_mgr->priv;
    ConnectionPool *pool;
    Connection *conn = NULL;
    char *url = NULL;
    GList *send_fs_list = NULL, *needed_fs_list = NULL;
    GList *block_list = NULL, *needed_block_list = NULL;
    GHashTable *active_paths = NULL;

    SeafBranch *local = seaf_branch_manager_get_branch (seaf->branch_mgr,
                                                        task->repo_id, "local");
    if (!local) {
        seaf_warning ("Failed to get branch local of repo %.8s.\n", task->repo_id);
        task->error = SYNC_ERROR_ID_LOCAL_DATA_CORRUPT;
        return NULL;
    }
    memcpy (task->head, local->commit_id, 40);
    seaf_branch_unref (local);

    pool = find_connection_pool (priv, task->host);
    if (!pool) {
        seaf_warning ("Failed to create connection pool for host %s.\n", task->host);
        task->error = SYNC_ERROR_ID_NOT_ENOUGH_MEMORY;
        goto out;
    }

    conn = connection_pool_get_connection (pool);
    if (!conn) {
        seaf_warning ("Failed to get connection to host %s.\n", task->host);
        task->error = SYNC_ERROR_ID_NOT_ENOUGH_MEMORY;
        goto out;
    }

    /* seaf_message ("Upload with HTTP sync protocol version %d.\n", */
    /*               task->protocol_version); */

    transition_state (task, task->state, HTTP_TASK_RT_STATE_CHECK);

    gint64 delta = 0;
    active_paths = g_hash_table_new_full (g_str_hash, g_str_equal, g_free, NULL);

    if (calculate_upload_size_delta_and_active_paths (task, &delta, active_paths) < 0) {
        seaf_warning ("Failed to calculate upload size delta for repo %s.\n",
                      task->repo_id);
        task->error = SYNC_ERROR_ID_LOCAL_DATA_CORRUPT;
        goto out;
    }

    g_hash_table_foreach (active_paths, set_path_status_syncing, task);

    if (check_permission (task, conn) < 0) {
        seaf_warning ("Upload permission denied for repo %.8s on server %s.\n",
                      task->repo_id, task->host);
        goto out;
    }

    if (check_quota (task, conn, delta) < 0) {
        seaf_warning ("Not enough quota for repo %.8s on server %s.\n",
                      task->repo_id, task->host);
        goto out;
    }

    if (task->state == HTTP_TASK_STATE_CANCELED)
        goto out;

    transition_state (task, task->state, HTTP_TASK_RT_STATE_COMMIT);

    if (send_commit_object (task, conn) < 0) {
        seaf_warning ("Failed to send head commit for repo %.8s.\n", task->repo_id);
        goto out;
    }

    if (task->state == HTTP_TASK_STATE_CANCELED)
        goto out;

    transition_state (task, task->state, HTTP_TASK_RT_STATE_FS);

    send_fs_list = calculate_send_fs_object_list (task);
    if (!send_fs_list) {
        seaf_warning ("Failed to calculate fs object list for repo %.8s.\n",
                      task->repo_id);
        task->error = SYNC_ERROR_ID_LOCAL_DATA_CORRUPT;
        goto out;
    }

    if (!task->use_fileserver_port)
        url = g_strdup_printf ("%s/seafhttp/repo/%s/check-fs/",
                               task->host, task->repo_id);
    else
        url = g_strdup_printf ("%s/repo/%s/check-fs/",
                               task->host, task->repo_id);

    while (send_fs_list != NULL) {
        if (upload_check_id_list_segment (task, conn, url,
                                          &send_fs_list, &needed_fs_list) < 0) {
            seaf_warning ("Failed to check fs list for repo %.8s.\n", task->repo_id);
            goto out;
        }

        if (task->state == HTTP_TASK_STATE_CANCELED)
            goto out;
    }
    g_free (url);
    url = NULL;

    while (needed_fs_list != NULL) {
        if (send_fs_objects (task, conn, &needed_fs_list) < 0) {
            seaf_warning ("Failed to send fs objects for repo %.8s.\n", task->repo_id);
            goto out;
        }

        if (task->state == HTTP_TASK_STATE_CANCELED)
            goto out;
    }

    transition_state (task, task->state, HTTP_TASK_RT_STATE_BLOCK);

    if (calculate_block_list (task, &block_list) < 0) {
        seaf_warning ("Failed to calculate block list for repo %.8s.\n",
                      task->repo_id);
        task->error = SYNC_ERROR_ID_LOCAL_DATA_CORRUPT;
        goto out;
    }

    if (!task->use_fileserver_port)
        url = g_strdup_printf ("%s/seafhttp/repo/%s/check-blocks/",
                               task->host, task->repo_id);
    else
        url = g_strdup_printf ("%s/repo/%s/check-blocks/",
                               task->host, task->repo_id);

    while (block_list != NULL) {
        if (upload_check_id_list_segment (task, conn, url,
                                          &block_list, &needed_block_list) < 0) {
            seaf_warning ("Failed to check block list for repo %.8s.\n",
                          task->repo_id);
            goto out;
        }

        if (task->state == HTTP_TASK_STATE_CANCELED)
            goto out;
    }
    g_free (url);
    url = NULL;

    task->n_blocks = g_list_length (needed_block_list);

    seaf_debug ("%d blocks to send for %s:%s.\n",
                task->n_blocks, task->host, task->repo_id);

    if (multi_threaded_send_blocks(task, needed_block_list) < 0 ||
        task->state == HTTP_TASK_STATE_CANCELED)
        goto out;

    transition_state (task, task->state, HTTP_TASK_RT_STATE_UPDATE_BRANCH);

    if (update_branch (task, conn) < 0) {
        seaf_warning ("Failed to update branch of repo %.8s.\n", task->repo_id);
        goto out;
    }

    /* After successful upload, the cached 'master' branch should be updated to
     * the head commit of 'local' branch.
     */
    update_master_branch (task);

    if (active_paths != NULL)
        g_hash_table_foreach (active_paths, set_path_status_synced, task);

out:
    string_list_free (send_fs_list);
    string_list_free (needed_fs_list);
    string_list_free (block_list);
    string_list_free (needed_block_list);

    if (active_paths)
        g_hash_table_destroy (active_paths);

    g_free (url);

    connection_pool_return_connection (pool, conn);

    return vdata;
}