#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  curl; scalar_t__ release; } ;
struct TYPE_8__ {scalar_t__ err_cnt; int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ ConnectionPool ;
typedef  TYPE_2__ Connection ;

/* Variables and functions */
 scalar_t__ CLEAR_POOL_ERR_CNT ; 
 int /*<<< orphan*/  connection_free (TYPE_2__*) ; 
 int /*<<< orphan*/  connection_pool_clear (TYPE_1__*) ; 
 int /*<<< orphan*/  curl_easy_reset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_queue_push_tail (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
connection_pool_return_connection (ConnectionPool *pool, Connection *conn)
{
    if (!conn)
        return;

    if (conn->release) {
        connection_free (conn);

        pthread_mutex_lock (&pool->lock);
        if (++pool->err_cnt >= CLEAR_POOL_ERR_CNT) {
            connection_pool_clear (pool);
        }
        pthread_mutex_unlock (&pool->lock);

        return;
    }

    curl_easy_reset (conn->curl);

    /* Reset error count when one connection succeeded. */
    pthread_mutex_lock (&pool->lock);
    pool->err_cnt = 0;
    g_queue_push_tail (pool->queue, conn);
    pthread_mutex_unlock (&pool->lock);
}