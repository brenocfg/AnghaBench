#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  fs_mgr; TYPE_1__* http_tx_mgr; } ;
struct TYPE_11__ {scalar_t__ state; void* error; int /*<<< orphan*/  host; int /*<<< orphan*/  repo_id; int /*<<< orphan*/  repo_version; } ;
struct TYPE_10__ {int n_blocks; char** blk_sha1s; } ;
struct TYPE_9__ {int /*<<< orphan*/ * priv; } ;
typedef  TYPE_2__ Seafile ;
typedef  TYPE_3__ HttpTxTask ;
typedef  int /*<<< orphan*/  HttpTxPriv ;
typedef  int /*<<< orphan*/  ConnectionPool ;
typedef  int /*<<< orphan*/  Connection ;

/* Variables and functions */
 scalar_t__ HTTP_TASK_STATE_CANCELED ; 
 void* SYNC_ERROR_ID_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/ * connection_pool_get_connection (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  connection_pool_return_connection (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * find_connection_pool (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int get_block (TYPE_3__*,int /*<<< orphan*/ *,char*) ; 
 TYPE_6__* seaf ; 
 TYPE_2__* seaf_fs_manager_get_seafile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  seaf_warning (char*,char const*,...) ; 
 int /*<<< orphan*/  seafile_unref (TYPE_2__*) ; 

int
http_tx_task_download_file_blocks (HttpTxTask *task, const char *file_id)
{
    Seafile *file;
    HttpTxPriv *priv = seaf->http_tx_mgr->priv;
    ConnectionPool *pool;
    Connection *conn;
    int ret = 0;

    file = seaf_fs_manager_get_seafile (seaf->fs_mgr,
                                        task->repo_id,
                                        task->repo_version,
                                        file_id);
    if (!file) {
        seaf_warning ("Failed to find seafile object %s in repo %.8s.\n",
                      file_id, task->repo_id);
        return -1;
    }

    pool = find_connection_pool (priv, task->host);
    if (!pool) {
        seaf_warning ("Failed to create connection pool for host %s.\n", task->host);
        task->error = SYNC_ERROR_ID_NOT_ENOUGH_MEMORY;
        seafile_unref (file);
        return -1;
    }

    conn = connection_pool_get_connection (pool);
    if (!conn) {
        seaf_warning ("Failed to get connection to host %s.\n", task->host);
        task->error = SYNC_ERROR_ID_NOT_ENOUGH_MEMORY;
        seafile_unref (file);
        return -1;
    }

    int i;
    char *block_id;
    for (i = 0; i < file->n_blocks; ++i) {
        block_id = file->blk_sha1s[i];
        ret = get_block (task, conn, block_id);
        if (ret < 0 || task->state == HTTP_TASK_STATE_CANCELED)
            break;
    }

    connection_pool_return_connection (pool, conn);

    seafile_unref (file);

    return ret;
}