#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gint ;
struct TYPE_8__ {TYPE_1__* sync_mgr; int /*<<< orphan*/  block_mgr; } ;
struct TYPE_7__ {scalar_t__ state; int /*<<< orphan*/  tx_bytes; int /*<<< orphan*/  error; int /*<<< orphan*/  repo_id; scalar_t__ all_stop; } ;
struct TYPE_6__ {int /*<<< orphan*/  block_id; int /*<<< orphan*/  block; TYPE_3__* task; } ;
struct TYPE_5__ {scalar_t__ download_limit; int /*<<< orphan*/  recv_bytes; } ;
typedef  TYPE_2__ SendBlockData ;
typedef  TYPE_3__ HttpTxTask ;

/* Variables and functions */
 scalar_t__ HTTP_TASK_STATE_CANCELED ; 
 int /*<<< orphan*/  SYNC_ERROR_ID_WRITE_LOCAL_DATA ; 
 int /*<<< orphan*/  g_atomic_int_add (int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ g_atomic_int_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_usleep (int) ; 
 TYPE_4__* seaf ; 
 size_t seaf_block_manager_write_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,size_t) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static size_t
get_block_callback (void *ptr, size_t size, size_t nmemb, void *userp)
{
    size_t realsize = size *nmemb;
    SendBlockData *data = userp;
    HttpTxTask *task = data->task;
    size_t n;

    if (task->state == HTTP_TASK_STATE_CANCELED || task->all_stop)
        return 0;

    n = seaf_block_manager_write_block (seaf->block_mgr,
                                        data->block,
                                        ptr, realsize);
    if (n < realsize) {
        seaf_warning ("Failed to write block %s in repo %.8s.\n",
                      data->block_id, task->repo_id);
        task->error = SYNC_ERROR_ID_WRITE_LOCAL_DATA;
        return n;
    }

    /* Update global transferred bytes. */
    g_atomic_int_add (&(seaf->sync_mgr->recv_bytes), n);

    /* Update transferred bytes for this task */
    g_atomic_int_add (&task->tx_bytes, n);

    /* If uploaded bytes exceeds the limit, wait until the counter
     * is reset. We check the counter every 100 milliseconds, so we
     * can waste up to 100 milliseconds without sending data after
     * the counter is reset.
     */
    while (1) {
        gint sent = g_atomic_int_get(&(seaf->sync_mgr->recv_bytes));
        if (seaf->sync_mgr->download_limit > 0 &&
            sent > seaf->sync_mgr->download_limit)
            /* 100 milliseconds */
            g_usleep (100000);
        else
            break;
    }

    return n;
}