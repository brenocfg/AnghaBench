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
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  queue; } ;
typedef  TYPE_1__ ConnectionPool ;
typedef  int /*<<< orphan*/  Connection ;

/* Variables and functions */
 int /*<<< orphan*/ * connection_new () ; 
 int /*<<< orphan*/ * g_queue_pop_head (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static Connection *
connection_pool_get_connection (ConnectionPool *pool)
{
    Connection *conn = NULL;

    pthread_mutex_lock (&pool->lock);
    conn = g_queue_pop_head (pool->queue);
    if (!conn) {
        conn = connection_new ();
    }
    pthread_mutex_unlock (&pool->lock);

    return conn;
}