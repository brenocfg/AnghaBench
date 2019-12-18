#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  repo_mgr; TYPE_1__* http_tx_mgr; } ;
struct TYPE_12__ {scalar_t__ state; void* error; int /*<<< orphan*/  head; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  host; } ;
struct TYPE_11__ {int /*<<< orphan*/ * priv; } ;
typedef  TYPE_2__ HttpTxTask ;
typedef  int /*<<< orphan*/  HttpTxPriv ;
typedef  int /*<<< orphan*/  GList ;
typedef  int /*<<< orphan*/  ConnectionPool ;
typedef  int /*<<< orphan*/  Connection ;

/* Variables and functions */
#define  FETCH_CHECKOUT_CANCELED 132 
#define  FETCH_CHECKOUT_FAILED 131 
#define  FETCH_CHECKOUT_LOCKED 130 
#define  FETCH_CHECKOUT_SUCCESS 129 
#define  FETCH_CHECKOUT_TRANSFER_ERROR 128 
 int /*<<< orphan*/  HTTP_TASK_RT_STATE_BLOCK ; 
 int /*<<< orphan*/  HTTP_TASK_RT_STATE_CHECK ; 
 int /*<<< orphan*/  HTTP_TASK_RT_STATE_COMMIT ; 
 int /*<<< orphan*/  HTTP_TASK_RT_STATE_FS ; 
 scalar_t__ HTTP_TASK_STATE_CANCELED ; 
 int /*<<< orphan*/  REPO_PROP_DOWNLOAD_HEAD ; 
 void* SYNC_ERROR_ID_FILE_LOCKED_BY_APP ; 
 void* SYNC_ERROR_ID_NOT_ENOUGH_MEMORY ; 
 void* SYNC_ERROR_ID_WRITE_LOCAL_DATA ; 
 scalar_t__ check_permission (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * connection_pool_get_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connection_pool_return_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_connection_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ get_commit_object (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ get_fs_objects (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ get_needed_fs_id_list (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 TYPE_6__* seaf ; 
 int seaf_repo_fetch_and_checkout (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_repo_manager_set_repo_property (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  string_list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  transition_state (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_local_repo (TYPE_2__*) ; 

__attribute__((used)) static void *
http_download_thread (void *vdata)
{
    HttpTxTask *task = vdata;
    HttpTxPriv *priv = seaf->http_tx_mgr->priv;
    ConnectionPool *pool;
    Connection *conn = NULL;
    GList *fs_id_list = NULL;

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

    /* seaf_message ("Download with HTTP sync protocol version %d.\n", */
    /*               task->protocol_version); */

    transition_state (task, task->state, HTTP_TASK_RT_STATE_CHECK);

    if (check_permission (task, conn) < 0) {
        seaf_warning ("Download permission denied for repo %.8s on server %s.\n",
                      task->repo_id, task->host);
        goto out;
    }

    if (task->state == HTTP_TASK_STATE_CANCELED)
        goto out;

    transition_state (task, task->state, HTTP_TASK_RT_STATE_COMMIT);

    if (get_commit_object (task, conn) < 0) {
        seaf_warning ("Failed to get server head commit for repo %.8s on server %s.\n",
                      task->repo_id, task->host);
        goto out;
    }

    if (task->state == HTTP_TASK_STATE_CANCELED)
        goto out;

    transition_state (task, task->state, HTTP_TASK_RT_STATE_FS);

    if (get_needed_fs_id_list (task, conn, &fs_id_list) < 0) {
        seaf_warning ("Failed to get fs id list for repo %.8s on server %s.\n",
                      task->repo_id, task->host);
        goto out;
    }

    if (task->state == HTTP_TASK_STATE_CANCELED)
        goto out;

    while (fs_id_list != NULL) {
        if (get_fs_objects (task, conn, &fs_id_list) < 0) {
            seaf_warning ("Failed to get fs objects for repo %.8s on server %s.\n",
                          task->repo_id, task->host);
            goto out;
        }

        if (task->state == HTTP_TASK_STATE_CANCELED)
            goto out;
    }

    transition_state (task, task->state, HTTP_TASK_RT_STATE_BLOCK);

    /* Record download head commit id, so that we can resume download
     * if this download is interrupted.
     */
    seaf_repo_manager_set_repo_property (seaf->repo_mgr,
                                         task->repo_id,
                                         REPO_PROP_DOWNLOAD_HEAD,
                                         task->head);

    int rc = seaf_repo_fetch_and_checkout (task, task->head);
    switch (rc) {
    case FETCH_CHECKOUT_SUCCESS:
        break;
    case FETCH_CHECKOUT_CANCELED:
        goto out;
    case FETCH_CHECKOUT_FAILED:
        task->error = SYNC_ERROR_ID_WRITE_LOCAL_DATA;
        goto out;
    case FETCH_CHECKOUT_TRANSFER_ERROR:
        goto out;
    case FETCH_CHECKOUT_LOCKED:
        task->error = SYNC_ERROR_ID_FILE_LOCKED_BY_APP;
        goto out;
    }

    update_local_repo (task);

out:
    connection_pool_return_connection (pool, conn);
    string_list_free (fs_id_list);
    return vdata;
}