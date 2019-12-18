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
struct conn {int redis; int client; int /*<<< orphan*/  (* ref ) (struct conn*,void*) ;int /*<<< orphan*/ * swallow_msg; int /*<<< orphan*/ * post_connect; int /*<<< orphan*/  dequeue_outq; int /*<<< orphan*/  enqueue_outq; int /*<<< orphan*/ * dequeue_inq; int /*<<< orphan*/ * enqueue_inq; int /*<<< orphan*/  unref; int /*<<< orphan*/  active; int /*<<< orphan*/  close; int /*<<< orphan*/  send_done; int /*<<< orphan*/  send_next; void* send; int /*<<< orphan*/  recv_done; int /*<<< orphan*/  recv_next; void* recv; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_VVERB ; 
 struct conn* _conn_get () ; 
 int /*<<< orphan*/  client_active ; 
 int /*<<< orphan*/  client_close ; 
 int /*<<< orphan*/  client_ref (struct conn*,void*) ; 
 int /*<<< orphan*/  client_unref ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,struct conn*,int) ; 
 int /*<<< orphan*/ * memcache_post_connect ; 
 int /*<<< orphan*/ * memcache_swallow_msg ; 
 void* msg_recv ; 
 void* msg_send ; 
 int /*<<< orphan*/  ncurr_cconn ; 
 int /*<<< orphan*/ * redis_post_connect ; 
 int /*<<< orphan*/ * redis_swallow_msg ; 
 int /*<<< orphan*/  req_client_dequeue_omsgq ; 
 int /*<<< orphan*/  req_client_enqueue_omsgq ; 
 int /*<<< orphan*/  req_recv_done ; 
 int /*<<< orphan*/  req_recv_next ; 
 int /*<<< orphan*/  req_send_done ; 
 int /*<<< orphan*/  req_send_next ; 
 int /*<<< orphan*/ * req_server_dequeue_imsgq ; 
 int /*<<< orphan*/  req_server_dequeue_omsgq ; 
 int /*<<< orphan*/ * req_server_enqueue_imsgq ; 
 int /*<<< orphan*/  req_server_enqueue_omsgq ; 
 int /*<<< orphan*/  rsp_recv_done ; 
 int /*<<< orphan*/  rsp_recv_next ; 
 int /*<<< orphan*/  rsp_send_done ; 
 int /*<<< orphan*/  rsp_send_next ; 
 int /*<<< orphan*/  server_active ; 
 int /*<<< orphan*/  server_close ; 
 int /*<<< orphan*/  server_ref (struct conn*,void*) ; 
 int /*<<< orphan*/  server_unref ; 
 int /*<<< orphan*/  stub1 (struct conn*,void*) ; 

struct conn *
conn_get(void *owner, bool client, bool redis)
{
    struct conn *conn;

    conn = _conn_get();
    if (conn == NULL) {
        return NULL;
    }

    /* connection either handles redis or memcache messages */
    conn->redis = redis ? 1 : 0;

    conn->client = client ? 1 : 0;

    if (conn->client) {
        /*
         * client receives a request, possibly parsing it, and sends a
         * response downstream.
         */
        conn->recv = msg_recv;
        conn->recv_next = req_recv_next;
        conn->recv_done = req_recv_done;

        conn->send = msg_send;
        conn->send_next = rsp_send_next;
        conn->send_done = rsp_send_done;

        conn->close = client_close;
        conn->active = client_active;

        conn->ref = client_ref;
        conn->unref = client_unref;

        conn->enqueue_inq = NULL;
        conn->dequeue_inq = NULL;
        conn->enqueue_outq = req_client_enqueue_omsgq;
        conn->dequeue_outq = req_client_dequeue_omsgq;
        conn->post_connect = NULL;
        conn->swallow_msg = NULL;

        ncurr_cconn++;
    } else {
        /*
         * server receives a response, possibly parsing it, and sends a
         * request upstream.
         */
        conn->recv = msg_recv;
        conn->recv_next = rsp_recv_next;
        conn->recv_done = rsp_recv_done;

        conn->send = msg_send;
        conn->send_next = req_send_next;
        conn->send_done = req_send_done;

        conn->close = server_close;
        conn->active = server_active;

        conn->ref = server_ref;
        conn->unref = server_unref;

        conn->enqueue_inq = req_server_enqueue_imsgq;
        conn->dequeue_inq = req_server_dequeue_imsgq;
        conn->enqueue_outq = req_server_enqueue_omsgq;
        conn->dequeue_outq = req_server_dequeue_omsgq;
        if (redis) {
          conn->post_connect = redis_post_connect;
          conn->swallow_msg = redis_swallow_msg;
        } else {
          conn->post_connect = memcache_post_connect;
          conn->swallow_msg = memcache_swallow_msg;
        }
    }

    conn->ref(conn, owner);
    log_debug(LOG_VVERB, "get conn %p client %d", conn, conn->client);

    return conn;
}