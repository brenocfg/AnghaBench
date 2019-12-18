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
typedef  scalar_t__ uint32_t ;
struct msg {int /*<<< orphan*/  mlen; int /*<<< orphan*/  pos; int /*<<< orphan*/  mhdr; } ;
struct mbuf {scalar_t__ end; scalar_t__ last; int /*<<< orphan*/  pos; } ;
struct context {int dummy; } ;
struct conn {struct msg* (* recv_next ) (struct context*,struct conn*,int) ;} ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ rstatus_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ NC_EAGAIN ; 
 scalar_t__ NC_ENOMEM ; 
 scalar_t__ NC_ERROR ; 
 scalar_t__ NC_OK ; 
 struct mbuf* STAILQ_LAST (int /*<<< orphan*/ *,struct mbuf*,int /*<<< orphan*/ ) ; 
 scalar_t__ conn_recv (struct conn*,scalar_t__,size_t) ; 
 scalar_t__ mbuf_full (struct mbuf*) ; 
 struct mbuf* mbuf_get () ; 
 int /*<<< orphan*/  mbuf_insert (int /*<<< orphan*/ *,struct mbuf*) ; 
 size_t mbuf_size (struct mbuf*) ; 
 scalar_t__ msg_parse (struct context*,struct conn*,struct msg*) ; 
 int /*<<< orphan*/  next ; 
 struct msg* stub1 (struct context*,struct conn*,int) ; 

__attribute__((used)) static rstatus_t
msg_recv_chain(struct context *ctx, struct conn *conn, struct msg *msg)
{
    rstatus_t status;
    struct msg *nmsg;
    struct mbuf *mbuf;
    size_t msize;
    ssize_t n;

    mbuf = STAILQ_LAST(&msg->mhdr, mbuf, next);
    if (mbuf == NULL || mbuf_full(mbuf)) {
        mbuf = mbuf_get();
        if (mbuf == NULL) {
            return NC_ENOMEM;
        }
        mbuf_insert(&msg->mhdr, mbuf);
        msg->pos = mbuf->pos;
    }
    ASSERT(mbuf->end - mbuf->last > 0);

    msize = mbuf_size(mbuf);

    n = conn_recv(conn, mbuf->last, msize);
    if (n < 0) {
        if (n == NC_EAGAIN) {
            return NC_OK;
        }
        return NC_ERROR;
    }

    ASSERT((mbuf->last + n) <= mbuf->end);
    mbuf->last += n;
    msg->mlen += (uint32_t)n;

    for (;;) {
        status = msg_parse(ctx, conn, msg);
        if (status != NC_OK) {
            return status;
        }

        /* get next message to parse */
        nmsg = conn->recv_next(ctx, conn, false);
        if (nmsg == NULL || nmsg == msg) {
            /* no more data to parse */
            break;
        }

        msg = nmsg;
    }

    return NC_OK;
}