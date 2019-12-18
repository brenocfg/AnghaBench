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
typedef  int /*<<< orphan*/  uint32_t ;
struct msg {int done; struct conn* owner; int /*<<< orphan*/  (* pre_coalesce ) (struct msg*) ;struct msg* peer; scalar_t__ request; int /*<<< orphan*/  mlen; } ;
struct context {int /*<<< orphan*/  evb; } ;
struct conn {int /*<<< orphan*/  owner; int /*<<< orphan*/  err; int /*<<< orphan*/  omsg_q; int /*<<< orphan*/  proxy; scalar_t__ client; int /*<<< orphan*/  (* dequeue_outq ) (struct context*,struct conn*,struct msg*) ;} ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ NC_OK ; 
 struct msg* TAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  errno ; 
 scalar_t__ event_add_out (int /*<<< orphan*/ ,struct conn*) ; 
 scalar_t__ req_done (struct conn*,struct msg*) ; 
 int /*<<< orphan*/  rsp_forward_stats (struct context*,int /*<<< orphan*/ ,struct msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_ok (struct context*,struct conn*) ; 
 int /*<<< orphan*/  stub1 (struct context*,struct conn*,struct msg*) ; 
 int /*<<< orphan*/  stub2 (struct msg*) ; 

__attribute__((used)) static void
rsp_forward(struct context *ctx, struct conn *s_conn, struct msg *msg)
{
    rstatus_t status;
    struct msg *pmsg;
    struct conn *c_conn;
    uint32_t msgsize;

    ASSERT(!s_conn->client && !s_conn->proxy);
    msgsize = msg->mlen;

    /* response from server implies that server is ok and heartbeating */
    server_ok(ctx, s_conn);

    /* dequeue peer message (request) from server */
    pmsg = TAILQ_FIRST(&s_conn->omsg_q);
    ASSERT(pmsg != NULL && pmsg->peer == NULL);
    ASSERT(pmsg->request && !pmsg->done);

    s_conn->dequeue_outq(ctx, s_conn, pmsg);
    pmsg->done = 1;

    /* establish msg <-> pmsg (response <-> request) link */
    pmsg->peer = msg;
    msg->peer = pmsg;

    msg->pre_coalesce(msg);

    c_conn = pmsg->owner;
    ASSERT(c_conn->client && !c_conn->proxy);

    if (req_done(c_conn, TAILQ_FIRST(&c_conn->omsg_q))) {
        status = event_add_out(ctx->evb, c_conn);
        if (status != NC_OK) {
            c_conn->err = errno;
        }
    }

    rsp_forward_stats(ctx, s_conn->owner, msg, msgsize);
}