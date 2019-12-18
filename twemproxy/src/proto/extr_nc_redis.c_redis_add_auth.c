#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  data; int /*<<< orphan*/  len; } ;
struct server_pool {TYPE_1__ redis_auth; } ;
struct msg {int swallow; } ;
struct context {int dummy; } ;
struct conn {int authenticated; int /*<<< orphan*/  (* enqueue_inq ) (struct context*,struct conn*,struct msg*) ;int /*<<< orphan*/  err; int /*<<< orphan*/  redis; struct server_pool* owner; int /*<<< orphan*/  proxy; int /*<<< orphan*/  client; } ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ NC_ENOMEM ; 
 scalar_t__ NC_OK ; 
 int /*<<< orphan*/  conn_authenticated (struct conn*) ; 
 int /*<<< orphan*/  errno ; 
 struct msg* msg_get (struct conn*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ msg_prepend_format (struct msg*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_put (struct msg*) ; 
 int /*<<< orphan*/  stub1 (struct context*,struct conn*,struct msg*) ; 

rstatus_t
redis_add_auth(struct context *ctx, struct conn *c_conn, struct conn *s_conn)
{
    rstatus_t status;
    struct msg *msg;
    struct server_pool *pool;

    ASSERT(!s_conn->client && !s_conn->proxy);
    ASSERT(!conn_authenticated(s_conn));

    pool = c_conn->owner;

    msg = msg_get(c_conn, true, c_conn->redis);
    if (msg == NULL) {
        c_conn->err = errno;
        return NC_ENOMEM;
    }

    status = msg_prepend_format(msg, "*2\r\n$4\r\nAUTH\r\n$%d\r\n%s\r\n",
                                pool->redis_auth.len, pool->redis_auth.data);
    if (status != NC_OK) {
        msg_put(msg);
        return status;
    }

    msg->swallow = 1;
    s_conn->enqueue_inq(ctx, s_conn, msg);
    s_conn->authenticated = 1;

    return NC_OK;
}