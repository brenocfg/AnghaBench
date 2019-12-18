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
struct msg {int /*<<< orphan*/  request; struct conn* owner; } ;
struct context {int dummy; } ;
struct conn {struct msg* rmsg; int /*<<< orphan*/  proxy; int /*<<< orphan*/  client; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ rsp_filter (struct context*,struct conn*,struct msg*) ; 
 int /*<<< orphan*/  rsp_forward (struct context*,struct conn*,struct msg*) ; 

void
rsp_recv_done(struct context *ctx, struct conn *conn, struct msg *msg,
              struct msg *nmsg)
{
    ASSERT(!conn->client && !conn->proxy);
    ASSERT(msg != NULL && conn->rmsg == msg);
    ASSERT(!msg->request);
    ASSERT(msg->owner == conn);
    ASSERT(nmsg == NULL || !nmsg->request);

    /* enqueue next message (response), if any */
    conn->rmsg = nmsg;

    if (rsp_filter(ctx, conn, msg)) {
        return;
    }

    rsp_forward(ctx, conn, msg);
}