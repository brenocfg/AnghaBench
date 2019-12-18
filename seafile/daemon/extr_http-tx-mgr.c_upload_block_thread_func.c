#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* gpointer ;
struct TYPE_8__ {int /*<<< orphan*/  finished_tasks; int /*<<< orphan*/  cpool; TYPE_1__* http_task; } ;
struct TYPE_7__ {int result; int /*<<< orphan*/  block_size; int /*<<< orphan*/  block_id; } ;
struct TYPE_6__ {int /*<<< orphan*/  error; int /*<<< orphan*/  host; } ;
typedef  TYPE_1__ HttpTxTask ;
typedef  int /*<<< orphan*/  Connection ;
typedef  TYPE_2__ BlockUploadTask ;
typedef  TYPE_3__ BlockUploadData ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_ERROR_ID_NOT_ENOUGH_MEMORY ; 
 int /*<<< orphan*/ * connection_pool_get_connection (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  connection_pool_return_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_async_queue_push (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int send_block (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
upload_block_thread_func (gpointer data, gpointer user_data)
{
    BlockUploadTask *task = data;
    BlockUploadData *tx_data = user_data;
    HttpTxTask *http_task = tx_data->http_task;
    Connection *conn;
    int ret = 0;

    conn = connection_pool_get_connection (tx_data->cpool);
    if (!conn) {
        seaf_warning ("Failed to get connection to host %s.\n", http_task->host);
        http_task->error = SYNC_ERROR_ID_NOT_ENOUGH_MEMORY;
        ret = -1;
        goto out;
    }

    ret = send_block (http_task, conn, task->block_id, &task->block_size);

    connection_pool_return_connection (tx_data->cpool, conn);

out:
    task->result = ret;
    g_async_queue_push (tx_data->finished_tasks, task);
}