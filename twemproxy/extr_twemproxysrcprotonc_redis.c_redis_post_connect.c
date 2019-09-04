#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  data; } ;
struct server_pool {int redis_db; TYPE_1__ name; } ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;
struct server {TYPE_2__ name; struct server_pool* owner; } ;
struct msg {int swallow; int /*<<< orphan*/ * owner; int /*<<< orphan*/  result; int /*<<< orphan*/  type; } ;
struct context {int dummy; } ;
struct conn {int redis; scalar_t__ connected; int /*<<< orphan*/  client; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  LOG_NOTICE ; 
 int /*<<< orphan*/  MSG_PARSE_OK ; 
 int /*<<< orphan*/  MSG_REQ_REDIS_SELECT ; 
 scalar_t__ NC_OK ; 
 scalar_t__ log10 (int) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct msg* msg_get (struct conn*,int,int) ; 
 scalar_t__ msg_prepend_format (struct msg*,char*,int,int) ; 
 int /*<<< orphan*/  msg_put (struct msg*) ; 
 int /*<<< orphan*/  msg_send (struct context*,struct conn*) ; 
 int /*<<< orphan*/  req_server_enqueue_imsgq_head (struct context*,struct conn*,struct msg*) ; 

void
redis_post_connect(struct context *ctx, struct conn *conn, struct server *server)
{
    rstatus_t status;
    struct server_pool *pool = server->owner;
    struct msg *msg;
    int digits;

    ASSERT(!conn->client && conn->connected);
    ASSERT(conn->redis);

    /*
     * By default, every connection to redis uses the database DB 0. You
     * can select a different one on a per-connection basis by sending
     * a request 'SELECT <redis_db>', where <redis_db> is the configured
     * on a per pool basis in the configuration
     */
    if (pool->redis_db <= 0) {
        return;
    }

    /*
     * Create a fake client message and add it to the pipeline. We force this
     * message to be head of queue as it might already contain a command
     * that triggered the connect.
     */
    msg = msg_get(conn, true, conn->redis);
    if (msg == NULL) {
        return;
    }

    digits = (pool->redis_db >= 10) ? (int)log10(pool->redis_db) + 1 : 1;
    status = msg_prepend_format(msg, "*2\r\n$6\r\nSELECT\r\n$%d\r\n%d\r\n", digits, pool->redis_db);
    if (status != NC_OK) {
        msg_put(msg);
        return;
    }
    msg->type = MSG_REQ_REDIS_SELECT;
    msg->result = MSG_PARSE_OK;
    msg->swallow = 1;
    msg->owner = NULL;

    /* enqueue as head and send */
    req_server_enqueue_imsgq_head(ctx, conn, msg);
    msg_send(ctx, conn);

    log_debug(LOG_NOTICE, "sent 'SELECT %d' to %s | %s", pool->redis_db,
              pool->name.data, server->name.data);
}