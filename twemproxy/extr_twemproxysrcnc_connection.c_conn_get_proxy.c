#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct server_pool {int /*<<< orphan*/  redis; } ;
struct conn {int proxy; int /*<<< orphan*/  (* ref ) (struct conn*,void*) ;int /*<<< orphan*/ * dequeue_outq; int /*<<< orphan*/ * enqueue_outq; int /*<<< orphan*/ * dequeue_inq; int /*<<< orphan*/ * enqueue_inq; int /*<<< orphan*/  unref; int /*<<< orphan*/ * active; int /*<<< orphan*/  close; int /*<<< orphan*/ * send_done; int /*<<< orphan*/ * send_next; int /*<<< orphan*/ * send; int /*<<< orphan*/ * recv_done; int /*<<< orphan*/ * recv_next; int /*<<< orphan*/  recv; int /*<<< orphan*/  redis; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_VVERB ; 
 struct conn* _conn_get () ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,struct conn*,int) ; 
 int /*<<< orphan*/  proxy_close ; 
 int /*<<< orphan*/  proxy_recv ; 
 int /*<<< orphan*/  proxy_ref (struct conn*,void*) ; 
 int /*<<< orphan*/  proxy_unref ; 
 int /*<<< orphan*/  stub1 (struct conn*,void*) ; 

struct conn *
conn_get_proxy(void *owner)
{
    struct server_pool *pool = owner;
    struct conn *conn;

    conn = _conn_get();
    if (conn == NULL) {
        return NULL;
    }

    conn->redis = pool->redis;

    conn->proxy = 1;

    conn->recv = proxy_recv;
    conn->recv_next = NULL;
    conn->recv_done = NULL;

    conn->send = NULL;
    conn->send_next = NULL;
    conn->send_done = NULL;

    conn->close = proxy_close;
    conn->active = NULL;

    conn->ref = proxy_ref;
    conn->unref = proxy_unref;

    conn->enqueue_inq = NULL;
    conn->dequeue_inq = NULL;
    conn->enqueue_outq = NULL;
    conn->dequeue_outq = NULL;

    conn->ref(conn, owner);

    log_debug(LOG_VVERB, "get conn %p proxy %d", conn, conn->proxy);

    return conn;
}