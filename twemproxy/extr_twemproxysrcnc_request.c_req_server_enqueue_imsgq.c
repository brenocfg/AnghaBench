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
struct msg {int request; int /*<<< orphan*/  mlen; int /*<<< orphan*/  noreply; } ;
struct context {int dummy; } ;
struct conn {int /*<<< orphan*/  owner; int /*<<< orphan*/  imsg_q; int /*<<< orphan*/  proxy; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_queue ; 
 int /*<<< orphan*/  in_queue_bytes ; 
 int /*<<< orphan*/  msg_tmo_insert (struct msg*,struct conn*) ; 
 int /*<<< orphan*/  s_tqe ; 
 int /*<<< orphan*/  stats_server_incr (struct context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_server_incr_by (struct context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
req_server_enqueue_imsgq(struct context *ctx, struct conn *conn, struct msg *msg)
{
    ASSERT(msg->request);
    ASSERT(!conn->client && !conn->proxy);

    /*
     * timeout clock starts ticking the instant the message is enqueued into
     * the server in_q; the clock continues to tick until it either expires
     * or the message is dequeued from the server out_q
     *
     * noreply request are free from timeouts because client is not intrested
     * in the response anyway!
     */
    if (!msg->noreply) {
        msg_tmo_insert(msg, conn);
    }

    TAILQ_INSERT_TAIL(&conn->imsg_q, msg, s_tqe);

    stats_server_incr(ctx, conn->owner, in_queue);
    stats_server_incr_by(ctx, conn->owner, in_queue_bytes, msg->mlen);
}