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
struct msg {int request; int /*<<< orphan*/  mlen; } ;
struct context {int dummy; } ;
struct conn {int /*<<< orphan*/  owner; int /*<<< orphan*/  omsg_q; int /*<<< orphan*/  proxy; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  TAILQ_INSERT_TAIL (int /*<<< orphan*/ *,struct msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  out_queue ; 
 int /*<<< orphan*/  out_queue_bytes ; 
 int /*<<< orphan*/  s_tqe ; 
 int /*<<< orphan*/  stats_server_incr (struct context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_server_incr_by (struct context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
req_server_enqueue_omsgq(struct context *ctx, struct conn *conn, struct msg *msg)
{
    ASSERT(msg->request);
    ASSERT(!conn->client && !conn->proxy);

    TAILQ_INSERT_TAIL(&conn->omsg_q, msg, s_tqe);

    stats_server_incr(ctx, conn->owner, out_queue);
    stats_server_incr_by(ctx, conn->owner, out_queue_bytes, msg->mlen);
}