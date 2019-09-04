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
typedef  scalar_t__ uint64_t ;
struct msg {scalar_t__ frag_id; scalar_t__ err; struct msg* peer; scalar_t__ request; struct conn* owner; } ;
struct context {int dummy; } ;
struct conn {int /*<<< orphan*/  redis; int /*<<< orphan*/  (* dequeue_outq ) (struct context*,struct conn*,struct msg*) ;int /*<<< orphan*/  proxy; scalar_t__ client; } ;
typedef  scalar_t__ err_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 struct msg* TAILQ_NEXT (struct msg*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  c_tqe ; 
 struct msg* msg_get_error (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ req_error (struct conn*,struct msg*) ; 
 int /*<<< orphan*/  req_put (struct msg*) ; 
 int /*<<< orphan*/  rsp_put (struct msg*) ; 
 int /*<<< orphan*/  stub1 (struct context*,struct conn*,struct msg*) ; 

__attribute__((used)) static struct msg *
rsp_make_error(struct context *ctx, struct conn *conn, struct msg *msg)
{
    struct msg *pmsg;        /* peer message (response) */
    struct msg *cmsg, *nmsg; /* current and next message (request) */
    uint64_t id;
    err_t err;

    ASSERT(conn->client && !conn->proxy);
    ASSERT(msg->request && req_error(conn, msg));
    ASSERT(msg->owner == conn);

    id = msg->frag_id;
    if (id != 0) {
        for (err = 0, cmsg = TAILQ_NEXT(msg, c_tqe);
             cmsg != NULL && cmsg->frag_id == id;
             cmsg = nmsg) {
            nmsg = TAILQ_NEXT(cmsg, c_tqe);

            /* dequeue request (error fragment) from client outq */
            conn->dequeue_outq(ctx, conn, cmsg);
            if (err == 0 && cmsg->err != 0) {
                err = cmsg->err;
            }

            req_put(cmsg);
        }
    } else {
        err = msg->err;
    }

    pmsg = msg->peer;
    if (pmsg != NULL) {
        ASSERT(!pmsg->request && pmsg->peer == msg);
        msg->peer = NULL;
        pmsg->peer = NULL;
        rsp_put(pmsg);
    }

    return msg_get_error(conn->redis, err);
}