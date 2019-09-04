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
struct msg {scalar_t__ pos; scalar_t__ mlen; int /*<<< orphan*/  mhdr; int /*<<< orphan*/  request; int /*<<< orphan*/  owner; } ;
struct mbuf {scalar_t__ last; scalar_t__ pos; } ;
struct context {int dummy; } ;
struct conn {int /*<<< orphan*/  (* recv_done ) (struct context*,struct conn*,struct msg*,struct msg*) ;int /*<<< orphan*/  redis; } ;
typedef  int /*<<< orphan*/  rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  NC_ENOMEM ; 
 int /*<<< orphan*/  NC_OK ; 
 struct mbuf* STAILQ_LAST (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_insert (int /*<<< orphan*/ *,struct mbuf*) ; 
 scalar_t__ mbuf_length (struct mbuf*) ; 
 int /*<<< orphan*/  mbuf_put (struct mbuf*) ; 
 struct mbuf* mbuf_split (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct msg* msg_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next ; 
 int /*<<< orphan*/  stub1 (struct context*,struct conn*,struct msg*,struct msg*) ; 
 int /*<<< orphan*/  stub2 (struct context*,struct conn*,struct msg*,struct msg*) ; 

__attribute__((used)) static rstatus_t
msg_parsed(struct context *ctx, struct conn *conn, struct msg *msg)
{
    struct msg *nmsg;
    struct mbuf *mbuf, *nbuf;

    mbuf = STAILQ_LAST(&msg->mhdr, mbuf, next);
    if (msg->pos == mbuf->last) {
        /* no more data to parse */
        conn->recv_done(ctx, conn, msg, NULL);
        return NC_OK;
    }

    /*
     * Input mbuf has un-parsed data. Split mbuf of the current message msg
     * into (mbuf, nbuf), where mbuf is the portion of the message that has
     * been parsed and nbuf is the portion of the message that is un-parsed.
     * Parse nbuf as a new message nmsg in the next iteration.
     */
    nbuf = mbuf_split(&msg->mhdr, msg->pos, NULL, NULL);
    if (nbuf == NULL) {
        return NC_ENOMEM;
    }

    nmsg = msg_get(msg->owner, msg->request, conn->redis);
    if (nmsg == NULL) {
        mbuf_put(nbuf);
        return NC_ENOMEM;
    }
    mbuf_insert(&nmsg->mhdr, nbuf);
    nmsg->pos = nbuf->pos;

    /* update length of current (msg) and new message (nmsg) */
    nmsg->mlen = mbuf_length(nbuf);
    msg->mlen -= nmsg->mlen;

    conn->recv_done(ctx, conn, msg, nmsg);

    return NC_OK;
}